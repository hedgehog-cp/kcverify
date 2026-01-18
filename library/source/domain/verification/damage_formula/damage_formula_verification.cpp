#include "kcv/domain/verification/damage_formula/damage_formula_verification.hpp"

// std
#include <algorithm>
#include <cmath>
#include <optional>
#include <utility>
#include <variant>
#include <vector>

// kcv
#include "kcv/core/constants/equipment_attributes.hpp"
#include "kcv/core/constants/ship_attributes.hpp"
#include "kcv/core/context_data.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/damage_formula/damage_formula.hpp"
#include "kcv/domain/verification/damage_formula/inverse_formula.hpp"
#include "kcv/domain/verification/entity/ship.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcv/external/kcsapi/extensions/damage_state.hpp"
#include "kcv/external/kcsapi/extensions/utility.hpp"
#include "kcv/external/kcsapi/types/api_type.hpp"
#include "kcv/external/kcsapi/types/enum/air_hit_type.hpp"
#include "kcv/external/kcsapi/types/enum/category.hpp"
#include "kcv/external/kcsapi/types/enum/day_attack_kind.hpp"
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"
#include "kcv/external/kcsapi/types/enum/fleet_flag.hpp"
#include "kcv/external/kcsapi/types/enum/icon.hpp"
#include "kcv/external/kcsapi/types/enum/night_attack_kind.hpp"
#include "kcv/external/kcsapi/types/enum/stype.hpp"
#include "kcv/std_ext/utility.hpp"

namespace kcv {
namespace {
namespace impl {

auto explain_damage(
    const kcv::context_data& ctx,  //
    const kcv::battlelog& data     //
) -> kcv::explain_damage_result {
    // ダメージ式.
    auto damage_formula = kcv::formulate_damage(ctx, data);

    // 逆算可能判定.
    const bool is_invertible_damage_formula = kcv::is_invertible_damage_formula(ctx, data);

    // 説明可能判定.
    const bool explainable_damage = is_invertible_damage_formula;  //or kcv::is_theoretical_damage(ctx, data);

    // 逆算結果 攻撃力補正.
    auto inversed_atk_mods = is_invertible_damage_formula
                               ? std::make_optional(kcv::inverse_attack_power_formula(data.damage, damage_formula))
                               : std::nullopt;

    // 逆算結果 防御力補正.
    auto inversed_def_mods = is_invertible_damage_formula
                               ? std::make_optional(kcv::inverse_defence_power_formula(data.damage, damage_formula))
                               : std::nullopt;

    return kcv::explain_damage_result{
        .damage_formula               = std::move(damage_formula),
        .is_invertible_damage_formula = is_invertible_damage_formula,
        .explainable_damage           = explainable_damage,
        .inversed_attack_modifiers    = std::move(inversed_atk_mods),
        .inversed_defence_modifiers   = std::move(inversed_def_mods),
    };
}

}  // namespace impl
}  // namespace
}  // namespace kcv

auto kcv::explain_damage(
    const kcv::context_data& ctx,        //
    const kcv::battlelogs_t& battlelogs  //
) -> std::vector<kcv::explain_damage_result> {
    auto results = std::vector<kcv::explain_damage_result>{};

    for (const auto& data : battlelogs) {
        results.push_back(kcv::impl::explain_damage(ctx, data));
    }

    return results;
}

bool kcv::is_invertible_damage_formula(const kcv::context_data& ctx, const kcv::battlelog& data) {
    // ダメージが防御艦の残耐久を引数とする関数によって置換されるとき, 逆算しない.
    //   missのとき, 0または割合置換となる.
    //   割合置換の範囲内のとき, 疑わしきは逆算せず.
    //   致死置換の範囲内のとき, 疑わしきは逆算せず.
    // 夜襲CI種別を特定できないとき, 補正値を決定できないため逆算できない.
    // 戦爆連合急所弾のとき, 補正値が不明であるため逆算できない.
    // 敵空母戦闘後搭載数が不明のとき, 攻撃力を決定できないため逆算できない.
    return not kcv::is_miss(ctx, data)                                     // missでなく,
       and not kcv::is_scratch_damage(ctx, data)                           // 割合置換ダメージでなく,
       and not kcv::is_lethal_replacement_damage(ctx, data)                // 致死置換ダメージでなく,
       and not kcv::is_night_air_attack_ci_type_indeterminable(ctx, data)  // 夜襲CI種別を特定でき,
       and not kcv::is_fba_combined_critical_air_attack(ctx, data)         // 戦爆連合熟練急所弾でなく,
       and not kcv::is_undefined_slot_num_air_attack(ctx, data)            // 敵空母戦闘後搭載数が不明でなく,
        ;                                                                  // .
}

bool kcv::is_miss(const kcv::context_data& ctx, const kcv::battlelog& data) {
    return std::visit(
        kcv::overloaded{
            [](std::int32_t v) static noexcept -> bool { return v == 0; },
            [&data] [[noreturn]] (kcv::kcsapi::air_hit_type v) -> bool {
                // HACK:
                // 航空戦ではhit_or_missとなるため, missを判定できない.
                // とりあえず, hit_or_miss かつ ダメージ0 ならばmissと扱う.
                return v == kcv::kcsapi::air_hit_type::hit_or_miss and data.damage == 0;
            },
        },
        data.clitical
    );
}

bool kcv::is_scratch_damage(const kcv::context_data& ctx, const kcv::battlelog& data) {
    const auto hp  = kcv::get_defender(data).hp();
    const auto dmg = data.damage;

    return std::floor(hp * 0.06) <= dmg and dmg <= std::floor(hp * 0.06 + std::max(hp - 1, 0) * 0.08);
}

bool kcv::is_lethal_replacement_damage(const kcv::context_data& ctx, const kcv::battlelog& data) {
    return kcv::is_lethal_replaced_damage_on_normal_condition(ctx, data)  // 第1種致死置換.
        or kcv::is_lethal_replaced_damage_on_very_tired(ctx, data)        // 第2種致死置換.
        or kcv::is_lethal_replaced_damage_by_friendly_attack(ctx, data)   // 第3種致死置換.
        ;
}

namespace kcv {
namespace {
namespace impl {

/// @brief 戦闘開始時に大破しているかを検証する.
bool is_heavy_damaged_on_battle_start(const kcv::battlelog& data) noexcept {
    // スプレの実装では, 戦闘ログ(赤仮.csv)に戦闘開始時の残耐久が存在しないため, 常にtrueを返している.
    // ここでは, 戦闘中に耐久が回復しないことを前提に, 攻撃を受ける直前が中破以下の損傷であればfalseを返すように改善する.
    const auto& defender = kcv::get_defender(data);
    switch (kcv::to_damage_state(defender.hp(), defender.maxhp())) {
        case kcv::damage_state::healthy:
        case kcv::damage_state::light:
        case kcv::damage_state::medium:
            return false;

        default:;
            // TODO: 何らかの条件を追加する.
    }

    // 無理に逆算対象として意味のない結果を逆算を行うよりも, 逆算対象とせず逆算をスキップする制御パスに移す.
    return true;
}

/// @brief 防御艦が旗艦であるかを検証する.
bool is_defender_flagship(const kcv::battlelog& data) noexcept {
    return data.defender_ship == 0uz;
}

/// @brief 防御艦の艦隊が通常艦隊.
bool is_defender_single_fleet(const kcv::battlelog& data) {
    return kcv::get_defender_fleet_data(data).combined_flag() == 0;
}

/// @brief 防御艦が赤疲労であるかを検証する.
bool is_defender_very_tired(const kcv::battlelog& data) {
    return kcv::get_defender(data).condition() < 20;
}

/// @brief 防御艦の艦隊が通常艦隊.
bool is_defender_combined_fleet(const kcv::battlelog& data) {
    return kcv::get_defender_fleet_data(data).combined_flag() != 0;
}

/// @brief 防御艦が最後の1隻であるかを検証する.
bool is_defender_last_ship(const kcv::battlelog& data) {
    const auto& defender_fleet = kcv::get_defender_fleet(data);

    int count = 0;
    for (const auto& defender : defender_fleet.ships()) {
        if (defender.hp() > 0) {
            count++;
        }
    }

    return count == 1;
}

}  // namespace impl
}  // namespace
}  // namespace kcv

bool kcv::is_lethal_replaced_damage_on_normal_condition(const kcv::context_data& ctx, const kcv::battlelog& data) {
    // 防御側がプレイヤーのもとで, 次の条件a,b,cをいずれも満たさないとき, 第1種致死置換となる.
    //   a. 戦闘開始時に防御艦が大破 かつ 防御艦が旗艦でない.
    //   b. 防御艦の艦隊が通常艦隊 かつ 防御艦が赤疲労.
    //   c. ダメージ候補値 < 防御艦の残耐久.
    // よって, 次の条件を全て満たすとき, 第1種致死置換によってダメージ置換されたと判定する.
    //   防御側がプレイヤー.
    //   not a and not b.
    //   ダメージが第1種致死置換の範囲内.

    if (data.attacker_side == kcv::kcsapi::fleet_flag::enemy) {
        const bool a = kcv::impl::is_heavy_damaged_on_battle_start(data) and not kcv::impl::is_defender_flagship(data);
        const bool b = kcv::impl::is_defender_single_fleet(data) and kcv::impl::is_defender_very_tired(data);
        if (not a and not b) {
            const auto hp  = kcv::get_defender(data).hp();
            const auto dmg = data.damage;

            return std::floor(hp * 0.5) <= dmg and dmg <= std::floor(hp * 0.5 + std::max(hp - 1, 0) * 0.3);
        }
    }

    return false;
}

bool kcv::is_lethal_replaced_damage_on_very_tired(const kcv::context_data& ctx, const kcv::battlelog& data) {
    // 防御側がプレイヤーのもとで, 次の条件a,b,c,dをいずれも満たさないとき, 第2種致死置換となる.
    //   a. 戦闘開始時に防御艦が大破.
    //   b. 防御艦が旗艦.
    //   c. 防御艦の艦隊が連合艦隊 かつ 防御艦が赤疲労.
    //   d. ダメージ候補値 < 防御艦の残耐久.
    // よって, 次の条件を全て満たすとき, 第2種致死置換によってダメージ置換されたと判定する.
    //   防御側がプレイヤー.
    //   not a and not b and not c.
    //   ダメージが第2種致死置換に等しい.

    if (data.attacker_side == kcv::kcsapi::fleet_flag::enemy) {
        const bool a = kcv::impl::is_heavy_damaged_on_battle_start(data);
        const bool b = kcv::impl::is_defender_flagship(data);
        const bool c = kcv::impl::is_defender_combined_fleet(data) and kcv::impl::is_defender_very_tired(data);
        if (not a and not b and not c) {
            const auto hp  = kcv::get_defender(data).hp();
            const auto dmg = data.damage;

            return dmg == hp - 1;
        }
    }

    return false;
}

bool kcv::is_lethal_replaced_damage_by_friendly_attack(const kcv::context_data& ctx, const kcv::battlelog& data) {
    // 防御側が深海棲艦のもとで, 次の条件を全て満たすとき, 第3種致死置換となる.
    //   a. 友軍攻撃.
    //   b. 防御艦が最後の1隻.
    //   c. ダメージ候補値 >= 防御艦の残耐久.
    // よって, 以下の条件を全て満たすとき, 第3種致死置換によってダメージ置換されたと判定する.
    //   防御側が深海棲艦.
    //   a and b.
    //   ダメージがfloor(防御艦の残耐久/2)に等しい.

    if (data.attacker_side == kcv::kcsapi::fleet_flag::player) {
        const bool a = data.phase == kcv::phase::friendly;
        const bool b = kcv::impl::is_defender_last_ship(data);
        if (a and b) {
            const auto hp  = kcv::get_defender(data).hp();
            const auto dmg = data.damage;

            return dmg == static_cast<std::int32_t>(std::floor(hp / 2.0));
        }
    }

    return false;
}

namespace kcv {
namespace {
namespace impl {

/// @brief 攻撃が夜襲CIであるかを検証する.
bool is_night_air_attack_ci(const kcv::battlelog& data) {
    switch (data.phase) {
        case kcv::phase::opening_taisen:
        case kcv::phase::opening_atack:
        case kcv::phase::hougeki:
        case kcv::phase::raigeki:
            return false;

        case kcv::phase::midnight:
        case kcv::phase::friendly:
            return std::get<kcv::kcsapi::night_attack_kind>(data.attack_kind)
                != kcv::kcsapi::night_attack_kind::cutin_air_attack;
    }
}

}  // namespace impl
}  // namespace
}  // namespace kcv

bool kcv::is_night_air_attack_ci_type_indeterminable(const kcv::context_data& ctx, const kcv::battlelog& data) {
    // 夜襲CIでない.
    if (not kcv::impl::is_night_air_attack_ci(data)) {
        return false;
    }

    // HACK: マスタ検索失敗回避と表示装備が3つ揃っていることの検証とを兼ねている.
    if (data.display_equipments.size() != 3) {
        return false;
    }
    if (std::ranges::contains(data.display_equipments, kcv::kcsapi::invalid_equipment_id)) {
        return false;
    }

    const auto& mst0 = kcv::find_mst(ctx.api_mst_slotitem(), data.display_equipments.at(0));
    const auto& mst1 = kcv::find_mst(ctx.api_mst_slotitem(), data.display_equipments.at(1));
    const auto& mst2 = kcv::find_mst(ctx.api_mst_slotitem(), data.display_equipments.at(2));

    const bool is_foo = std::get<kcv::kcsapi::idx_type::icon>(mst0.api_type) == kcv::kcsapi::icon::night_fighter  //
                    and kcv::is_night_plane(mst1)                                                                 //
                    and kcv::is_night_plane(mst2);                                                                //

    const bool is_ffa = std::get<kcv::kcsapi::idx_type::icon>(mst0.api_type) == kcv::kcsapi::icon::night_fighter    //
                    and std::get<kcv::kcsapi::idx_type::icon>(mst1.api_type) == kcv::kcsapi::icon::night_fighter    //
                    and std::get<kcv::kcsapi::idx_type::icon>(mst0.api_type) == kcv::kcsapi::icon::night_attacker;  //

    return is_foo and is_ffa;
}

bool kcv::is_fba_combined_critical_air_attack(const kcv::context_data& ctx, const kcv::battlelog& data) {
    const auto is_fb_combined_air_attack = std::visit(
        kcv::overloaded{
            [](kcv::kcsapi::day_attack_kind v) static -> bool {
                return v == kcv::kcsapi::day_attack_kind::cutin_air_attack;
            },
            [](const auto&) static -> bool { return false; },
        },
        data.attack_kind
    );

    return is_fb_combined_air_attack and kcv::is_critical(data);
}

namespace kcv {
namespace {
namespace impl {

bool is_air_attack_in_hougeki(const kcv::context_data& ctx, const kcv::battlelog& data) {
    const auto& attacker = kcv::get_attacker(data);
    const auto& defender = kcv::get_defender(data);

    // 補給艦の航空攻撃の条件.
    // よく分からない.
    if (attacker.mst().api_stype == kcv::kcsapi::stype::ao) {
        const bool has_bomber   = kcv::has_equipment(attacker, kcv::kcsapi::category::carrier_based_bomber);
        const bool has_attacker = kcv::has_equipment(attacker, kcv::kcsapi::category::carrier_based_torpedo);
        if (has_bomber and has_attacker) {
            return false;
        }
    }

    // HACK: 関数の意味と意図がずれている.
    // 対潜では搭載数が攻撃力に影響しないため, 不明としない.
    if (kcv::is_submarine(defender.mst())) {
        return false;
    }

    // スプレの実装では対地を弾いているが詳細不明. 記述漏れか?
    // if (kcv::is_installation(defender.mst())) { return false; }

    // 航空攻撃.
    if (kcv::is_aircraft_carrier(attacker.mst())) {
        return true;
    }

    // 砲弾攻撃.
    return false;
}

bool can_night_operation(const kcv::battlelog& data) {
    const auto& attacker = kcv::get_attacker(data);

    if (kcv::to_damage_state(attacker.hp(), attacker.maxhp()) <= kcv::damage_state::light
        or attacker.mst().api_stype == kcv::kcsapi::stype::cvb) {
        if (kcv::is_night_operation_aircraft_carrier(attacker.mst())
            or kcv::has_equipment(attacker, kcv::is_night_operation_aviation_personnel)) {
            for (const auto& slot : attacker.eqslots()) {
                if (const auto& e = slot.equipment(); e.has_value()) {
                    if (kcv::is_night_plane(e->mst()) and slot.aircraft_current() > 0) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool is_air_attack_in_night(const kcv::context_data& ctx, const kcv::battlelog& data) {
    const auto& attacker = kcv::get_attacker(data);
    const auto& defender = kcv::get_defender(data);

    // HACK: 関数の意味と意図がずれている.
    // 対潜では搭載数が攻撃力に影響しないため, 不明としない.
    if (kcv::is_submarine(defender.mst())) {
        return false;
    }

    if (kcv::is_aircraft_carrier(attacker.mst()) or attacker.mst().api_stype == kcv::kcsapi::stype::ao) {
        if (can_night_operation(data)) {
            return true;
        }
    }

    // TODO: Arc Royalによるswordfish追撃判定.

    // 砲雷攻撃.
    return false;
}

bool is_air_attack(const kcv::context_data& ctx, const kcv::battlelog& data) {
    switch (data.phase) {
        case kcv::phase::opening_taisen:
        case kcv::phase::opening_atack:
            return false;

        case kcv::phase::hougeki:
            return is_air_attack_in_hougeki(ctx, data);

        case kcv::phase::raigeki:
            return false;

        case kcv::phase::midnight:
        case kcv::phase::friendly:
            return is_air_attack_in_night(ctx, data);
    }
}

}  // namespace impl
}  // namespace
}  // namespace kcv

bool kcv::is_undefined_slot_num_air_attack(const kcv::context_data& ctx, const kcv::battlelog& data) {
    // ある時期以降に追加された深海棲艦の各スロットの搭載数が不明であり攻撃力を計算できないためこれを検出する.
    // a. 深海棲艦による攻撃.
    // b. 航空攻撃.
    // c. 搭載数が不明.

    if (data.attacker_side != kcv::kcsapi::fleet_flag::enemy) {
        return false;
    }

    //{
    //    if (not kcv::impl::is_air_attack(ctx, data)) {
    //        return false;
    //    }
    //
    //    // とりあえず, 実際に搭載数が不明であるかを検証せず全部不明にする.
    //    return true;
    //}

    // 実装が不安であるため, とりあえず, 空母または補給艦であれば搭載数が不明とする.
    {
        const auto& attacker = kcv::get_attacker(data);
        if (kcv::is_aircraft_carrier(attacker.mst()) or attacker.mst().api_stype == kcv::kcsapi::stype::ao) {
            return true;
        }

        return false;
    }
}