// std
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <limits>
#include <optional>
#include <print>
#include <ranges>
#include <stacktrace>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

// kcv
#include "kcv/core/constants/ship_attributes.hpp"
#include "kcv/core/context_data.hpp"
#include "kcv/core/json/read_json.hpp"
#include "kcv/core/numeric/interval.hpp"
#include "kcv/core/numeric/interval/basic_interval.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/battlelog/battlelog_io.hpp"
#include "kcv/domain/verification/damage_formula/damage_formula.hpp"
#include "kcv/domain/verification/damage_formula/damage_formula_verification.hpp"
#include "kcv/domain/verification/damage_formula/inverse_formula.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"
#include "kcv/external/eoen/database/sortie/sortie_record.hpp"
#include "kcv/external/kcsapi/extensions/damage_state.hpp"
#include "kcv/std_ext/exception.hpp"
#include "kcv/std_ext/formatter.hpp"

/// @brief 処理対象の戦闘ログならばtrueを返す.
/// @param data 戦闘ログ1件.
/// @todo 条件を記述した設定ファイルを読み込んで, あるいはコマンドラインから条件を読み込んで, 条件の変更に対して再コンパイルを不要にする.
bool macthes_battlelog(const kcv::battlelog& data);

/// @brief ダメージ式を検証する.
/// @param ctx マスタを含む背景情報.
/// @param battlelogs 検証対象の全戦闘ログ.
void verify_damage_formula(const kcv::context_data& ctx, const kcv::battlelogs_t& battlelogs);

int main() try {
    std::set_terminate([]() static -> void { std::println(stderr, "fatal error: {}", std::stacktrace{}); });

    // マスタおよび背景情報を読み込む.
    auto ctx = kcv::context_data{};
    ctx.api_mst_ship("./assets/kcsapi/api_start2/api_mst_ship.json");
    ctx.api_mst_slotitem("./assets/kcsapi/api_start2/api_mst_slotitem.json");
    ctx.destination("./assets/eoen/destination.json");
    ctx.fit_bonuses("./assets/eoen/fit_bonuses.json");
    ctx.map_bonus("./assets/kc3kai/bonus/7-4.json");
    ctx.map_bonus("./assets/kc3kai/bonus/7-5.json");

    // 赤仮ライクの戦闘ログへと74式ENの出撃詳細を変換する.
    auto battlelogs = kcv::battlelogs_t{};
    battlelogs.reserve(500uz);
    for (const auto& file : std::filesystem::directory_iterator{"./data"}) {
        if (file.is_regular_file()) {
            auto sortie_records = std::vector<kcv::eoen::database::sortie::sortie_record>{};
            kcv::read_json(sortie_records, file.path());
            for (const auto& sortie_record : sortie_records) {
                kcv::generate_battlelog(battlelogs, sortie_record, ctx.api_mst_ship(), ctx.api_mst_slotitem());
            }
        }
    }
    std::println("戦闘ログ: {}", battlelogs.size());

    // 対象でないデータを削除する.
    std::erase_if(battlelogs, [](const auto& e) static -> bool { return not ::macthes_battlelog(e); });

    // 赤仮ライクの形式でCSVファイルに書き出す.
    kcv::write_akakari(battlelogs, ctx.api_mst_ship(), ctx.api_mst_slotitem(), "./out/battlelogs.csv");

    // ダメージ式を検証する.
    ::verify_damage_formula(ctx, battlelogs);
} catch (const std::exception& e) {
    // 捕捉した例外をフォーマットして標準エラー出力に出力するとともに, エラーとしてプログラムを終了する.
    kcv::print_exception(stderr, e);
    return EXIT_FAILURE;
}

bool macthes_battlelog(const kcv::battlelog& data) {
    // ダメージ0を除外.
    if (data.damage == 0) {
        return false;
    }

    // CL0を除外.
    if (std::get<std::int32_t>(data.clitical) == 0) {
        return false;
    }

    // 深海棲艦の攻撃を除外.
    if (data.attacker_side == kcv::kcsapi::fleet_flag::enemy) {
        return false;
    }

    // 対潜でない攻撃を除外.
    // static constexpr auto target_phases = std::to_array<kcv::phase>({
    //     kcv::phase::opening_atack,
    //     kcv::phase::raigeki,
    // });
    // if (not std::ranges::contains(target_phases, data.phase)) {
    //     return false;
    // }
    if (not kcv::is_submarine(kcv::get_defender(data).mst())) {
        return false;
    }

    // 連合艦隊からの攻撃を除外.
    // if (kcv::get_attacker_fleet_data(data).combined_flag() != 0) {
    //     return false;
    // }

    // 連合艦隊への攻撃を除外.
    // if (kcv::get_defender_fleet_data(data).combined_flag() != 0) {
    //     return false;
    // }

    // 期間限定海域を除外.
    if (data.world > 8) {
        return false;
    }

    // 中破を除外.
    // if (const auto& attacker = kcv::get_attacker(data);
    //     kcv::to_damage_state(attacker.hp(), attacker.maxhp()) == kcv::damage_state::medium) {
    //     return false;
    // }

    return true;
}

struct verify_damage_formula_result final {
    /// @brief ダメージ式.
    kcv::damage_formula damage_formula;

    /// @brief 逆算可能判定.
    bool is_invertible_damage_formula;

    /// @brief 逆算結果 攻撃力補正値.
    std::optional<kcv::inverse_attack_formula_result_t> inversed_attack_power_modifiers;

    /// @brief 逆算結果 防御力補正値.
    std::optional<kcv::inverse_defence_formula_result_t> inversed_defence_power_modifiers;

    /// @brief ダメージ.
    std::optional<kcv::number> damage;

    /// @brief 説明可能判定.
    bool is_explainable_damage;
};

/// @brief ダメージ式を標準出力に出力する.
void print_damage_formula(const std::vector<verify_damage_formula_result>& results) {
    for (const auto& result : results) {
        const auto& atk_mods = result.damage_formula.attack_power_formula().modifier_function().decompose();
        const auto& def_mods = result.damage_formula.defence_power_formula().modifier_function().decompose();

        // 基本攻撃力.
        const auto base_attack = result.damage_formula.attack_power_formula().base_value();
        std::print("基本攻撃力: {:.3f}, ", base_attack);

        // 第0種補正.
        // const auto& [a0, b0] = std::get<kcv::functions::f0>(atk_mods);
        // std::print("a0: {:.3f}, b0: {:.3f}, ", a0, b0);

        // 交戦形態補正.
        const auto& [a_engagement, _engagement] = std::get<kcv::functions::engagement>(atk_mods);
        std::print("交戦形態補正: {:.3f}, ", a_engagement);

        // 攻撃側陣形補正.
        const auto& [a_formation, _formation] = std::get<kcv::functions::formation>(atk_mods);
        std::print("攻撃側陣形補正: {:.3f}, ", a_formation);

        // 損傷状態補正.
        const auto& [a_damage_state, _damage_state] = std::get<kcv::functions::damage_state>(atk_mods);
        std::print("損傷状態補正: {:.3f}, ", a_damage_state);

        // 前対潜シナジー補正.
        const auto& [a_pre, _pre] = std::get<kcv::functions::pre_asw>(atk_mods);
        std::print("前対潜シナジー補正: {:.3f}, ", a_pre);

        // 後対潜シナジー補正.
        const auto& [a_post, _post] = std::get<kcv::functions::post_asw>(atk_mods);
        std::print("後対潜シナジー補正: {:.3f}, ", a_post);

        // 第14種補正
        // const auto& [a14, b14] = std::get<kcv::functions::f14>(atk_mods);
        // std::print("a14: {:.3f}, b14: {:.3f}, ", a14, b14);

        // 第3種補正.
        // const auto& [a3, b3] = std::get<kcv::functions::f3>(def_mods);
        // std::print("a3: {:.3f}, b3: {:.3f}, ", a3, b3);

        // 装甲減少補正.
        const auto& [_ap_depth, b_ap_depth] = std::get<kcv::functions::depth_charge_armor_break>(def_mods);
        std::print("装甲減少補正: {:.3f}, ", b_ap_depth);

        // 攻撃力.
        const auto& atk = result.damage_formula.attack_power();
        std::print("最終攻撃力: {:.3f}, ", atk);

        // 防御力.
        const auto& def = result.damage_formula.defence_power();
        std::print("最終防御力: {:.3f}, ", def);

        // ダメージ.
        const auto& dmg = result.damage;
        std::print("理論ダメージ: {}, ", dmg);

        std::println("");
    }
}

/// @brief 逆算した結果を要約して標準出力に出力する.
void print_summary(const kcv::battlelogs_t& battlelogs, const std::vector<verify_damage_formula_result>& results) {
    std::println("入力件数: {}", results.size());

    const auto inverse_target_num = std::ranges::count_if(results, [](const auto& e) static noexcept -> bool {  //
        return e.is_invertible_damage_formula;
    });
    std::println("逆算対象: {}", inverse_target_num);

    std::println("逆算不可能: {}", results.size() - inverse_target_num);

    const auto greater_than_observed_damage = std::ranges::count_if(
        std::ranges::views::zip(battlelogs, results),  //
        [](const auto& e) static -> bool {
            const auto& [battlelog, inversed] = e;
            return inversed.damage.has_value() and battlelog.damage < *inversed.damage;
        }
    );
    std::println("<理論最小値: {}", greater_than_observed_damage);

    const auto in = std::ranges::count_if(
        std::ranges::views::zip(battlelogs, results),  //
        [](const auto& e) static -> bool {
            const auto& [battlelog, inversed] = e;
            return inversed.damage.has_value() and kcv::in(battlelog.damage, *inversed.damage);
        }
    );
    std::println("範囲内: {}", in);

    const auto less_than_observed_damage = std::ranges::count_if(
        std::ranges::views::zip(battlelogs, results),  //
        [](const auto& e) static -> bool {
            const auto& [battlelog, inversed] = e;
            return inversed.damage.has_value() and battlelog.damage < *inversed.damage;
        }
    );
    std::println("理論最大値<: {}", less_than_observed_damage);

    const auto equal_to_min = std::ranges::count_if(
        std::ranges::views::zip(battlelogs, results),  //
        [](const auto& e) static -> bool {
            const auto& [battlelog, inversed] = e;
            return inversed.damage.has_value() and battlelog.damage == inversed.damage->lower();
        }
    );
    std::println("=理論最小値: {}", equal_to_min);

    const auto equal_to_max = std::ranges::count_if(
        std::ranges::views::zip(battlelogs, results),  //
        [](const auto& e) static -> bool {
            const auto& [battlelog, inversed] = e;
            return inversed.damage.has_value() and battlelog.damage == inversed.damage->upper();
        }
    );
    std::println("理論最大値=: {}", equal_to_max);

    const auto explainable_damage_num = std::ranges::count_if(results, [](const auto& e) static -> bool {  //
        return e.is_explainable_damage;
    });
    std::println("説明可能判定: {}", explainable_damage_num);
}

/// @brief 逆算結果のうち型Tのものを集計する.
/// @tparam T 強い型付けをした線形補正関数. Tは逆算結果の型のうち唯一のものでなければならない.
/// 例: T = kcv::functions::basic_liner<foo_tag>.
/// @param inversed_results 逆算結果.
/// @return 乗算補正値の最小値および上限, 加算補正値の最小値および上限.
template <typename T>
    requires kcv::functions::is_basic_liner_v<T>
auto aggregate_attack_power_modifier(const std::vector<verify_damage_formula_result>& inversed_results) {
    // 取り出す逆算結果の型.
    using inversed_modifier_t = std::optional<kcv::inverse_result<T>>;

    auto a_min = -std::numeric_limits<kcv::interval::base_type>::infinity();
    auto a_sup = +std::numeric_limits<kcv::interval::base_type>::infinity();
    auto b_min = -std::numeric_limits<kcv::interval::base_type>::infinity();
    auto b_sup = +std::numeric_limits<kcv::interval::base_type>::infinity();

    for (const auto& result : inversed_results) {
        if (result.inversed_attack_power_modifiers.has_value()) {
            // 逆算結果から型Tのものを取り出す.
            const auto& inversed_modifier = std::get<inversed_modifier_t>(*result.inversed_attack_power_modifiers);
            if (inversed_modifier.has_value()) {
                // 逆算した乗算補正値a, 加算補正値bそれぞれについて, 補正値の共通区間(積集合)を求める.
                // 最小値と上限との大小関係が逆算する場合があるため区間型を用いない.
                const auto& [a, b] = *inversed_modifier;
                if (a.has_value()) {
                    a_min = std::max(a->lower(), a_min);
                    a_sup = std::min(a->upper(), a_sup);
                }
                if (b.has_value()) {
                    b_min = std::max(b->lower(), b_min);
                    b_sup = std::min(b->upper(), b_sup);
                }
            }
        }
    }

    return std::make_tuple(a_min, a_sup, b_min, b_sup);
}

/// @brief 逆算した補正値を標準出力に出力する.
void print_modifier(const std::vector<verify_damage_formula_result>& results) {
    const auto& [a0_min, a0_sup, b0_min, b0_sup] = aggregate_attack_power_modifier<kcv::functions::f0>(results);
    std::println("第0種補正: {:.5f} ≦ a0 < {:.5f}, {:.5f} ≦ b0 < {:.5f}", a0_min, a0_sup, b0_min, b0_sup);

    const auto& [a14_min, a14_sup, b14_min, b14_sup] = aggregate_attack_power_modifier<kcv::functions::f14>(results);
    std::println("第14種補正: {:.5f} ≦ a14 < {:.5f}, {:.5f} ≦ b14 < {:.5f}", a14_min, a14_sup, b14_min, b14_sup);
}

void verify_damage_formula(const kcv::context_data& ctx, const kcv::battlelogs_t& battlelogs) {
    auto results = std::vector<verify_damage_formula_result>{};
    results.reserve(battlelogs.size());

    for (const auto& data : battlelogs) {
        // ダメージ式を立式.
        auto damage_formula = kcv::formulate_damage(ctx, data);

        // 逆算可能判定.
        const bool is_invertible_damage_formula = kcv::is_invertible_damage_formula(ctx, data);
        // 逆算.
        auto inv_atk_pow_mods = is_invertible_damage_formula
                                  ? std::make_optional(kcv::inverse_attack_power_formula(data.damage, damage_formula))
                                  : std::nullopt;
        auto inv_def_pow_mods = is_invertible_damage_formula
                                  ? std::make_optional(kcv::inverse_defence_power_formula(data.damage, damage_formula))
                                  : std::nullopt;

        // ダメージ式を評価.
        const auto damage = damage_formula.evaluate();
        // 理論範囲内判定.
        const bool is_theoretical_damage = damage.has_value() and kcv::in(data.damage, *damage);
        // 説明可能判定 (異常ダメージ検知).
        const bool is_explainable_damage = is_theoretical_damage or not is_invertible_damage_formula;

        results.push_back(
            verify_damage_formula_result{
                .damage_formula                   = std::move(damage_formula),
                .is_invertible_damage_formula     = is_invertible_damage_formula,
                .inversed_attack_power_modifiers  = std::move(inv_atk_pow_mods),
                .inversed_defence_power_modifiers = std::move(inv_def_pow_mods),
                .damage                           = damage,
                .is_explainable_damage            = is_explainable_damage,
            }
        );
    }

    assert(battlelogs.size() == results.size());

    // 逆算結果を表示.
    ::print_damage_formula(results);
    std::println("------------");
    ::print_summary(battlelogs, results);
    std::println("------------");
    ::print_modifier(results);
}