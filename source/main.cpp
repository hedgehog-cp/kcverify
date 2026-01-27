// std
#include <cassert>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <print>
#include <stacktrace>
#include <vector>

// kcv
#include "kcv/core/constants/ship_attributes.hpp"
#include "kcv/core/context_data.hpp"
#include "kcv/core/json/read_json.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/battlelog/battlelog_io.hpp"
#include "kcv/domain/verification/damage_formula/damage_formula_verification.hpp"
#include "kcv/external/eoen/database/sortie/sortie_record.hpp"
#include "kcv/std_ext/exception.hpp"
#include "kcv/std_ext/formatter.hpp"

/// @brief 処理対象の戦闘ログならばtrueを返す.
/// @param data 戦闘ログ1件.
/// @todo 条件を記述した設定ファイルを読み込んで, あるいはコマンドラインから条件を読み込んで, 条件の変更に対して再コンパイルを不要にする.
bool macthes_battlelog(const kcv::battlelog& data);

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
    kcv::verify_damage_formula(ctx, battlelogs);
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
    // if (data.attacker_side == kcv::kcsapi::fleet_flag::enemy) {
    //     return false;
    // }

    // 夜戦でない攻撃を除外.
    // static constexpr auto target_phases = std::to_array<kcv::phase>({
    //     kcv::phase::midnight,
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
