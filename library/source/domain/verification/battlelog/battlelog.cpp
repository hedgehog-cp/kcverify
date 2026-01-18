#include "kcv/domain/verification/battlelog/battlelog.hpp"

// std
#include <concepts>
#include <cstdint>
#include <fstream>
#include <ostream>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

// kcv
#include "domain/verification/battlelog/process_kcsapi.hpp"
#include "kcv/core/json/read_json.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/battlelog/battlelog_io.hpp"
#include "kcv/domain/verification/entity/adapter/from_eoen.hpp"
#include "kcv/domain/verification/entity/fleet.hpp"
#include "kcv/external/eoen/database/kancolle_api/api_files.hpp"
#include "kcv/external/eoen/database/sortie/sortie_record.hpp"
#include "kcv/external/kcsapi/api_get_member/ship_deck/response.hpp"
#include "kcv/external/kcsapi/api_req_battle_midnight/battle/response.hpp"
#include "kcv/external/kcsapi/api_req_battle_midnight/sp_midnight/response.hpp"
#include "kcv/external/kcsapi/api_req_combined_battle/battle_water/response.hpp"
#include "kcv/external/kcsapi/api_req_combined_battle/battleresult/response.hpp"
#include "kcv/external/kcsapi/api_req_combined_battle/each_battle_water/response.hpp"
#include "kcv/external/kcsapi/api_req_combined_battle/ec_battle/response.hpp"
#include "kcv/external/kcsapi/api_req_combined_battle/ec_midnight_battle/response.hpp"
#include "kcv/external/kcsapi/api_req_combined_battle/ld_airbattle/response.hpp"
#include "kcv/external/kcsapi/api_req_combined_battle/midnight_battle/response.hpp"
#include "kcv/external/kcsapi/api_req_map/next/response.hpp"
#include "kcv/external/kcsapi/api_req_map/start/request.hpp"
#include "kcv/external/kcsapi/api_req_map/start/response.hpp"
#include "kcv/external/kcsapi/api_req_map/start_air_base/request.hpp"
#include "kcv/external/kcsapi/api_req_map/start_air_base/response.hpp"
#include "kcv/external/kcsapi/api_req_sortie/battle/response.hpp"
#include "kcv/external/kcsapi/api_req_sortie/battleresult/response.hpp"
#include "kcv/external/kcsapi/api_req_sortie/ld_airbattle/response.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_ship.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcv/external/kcsapi/extensions/to_string.hpp"
#include "kcv/external/kcsapi/types/enum/air_hit_type.hpp"
#include "kcv/external/kcsapi/types/enum/day_attack_kind.hpp"
#include "kcv/external/kcsapi/types/enum/fleet_flag.hpp"
#include "kcv/external/kcsapi/types/enum/night_attack_kind.hpp"
#include "kcv/std_ext/exception.hpp"
#include "kcv/std_ext/formatter.hpp"
#include "kcv/std_ext/utility.hpp"

namespace kcv {
namespace {
namespace impl {

/// @brief 74式ENのAPIファイルを出撃APIに解析する.
/// @param dst 出力先の出撃API.
/// @param src 入力元の74式ENAPIファイル.
/// @details 候補型のいずれかの型でデフォルト初期化してから出撃APIを読み込むため, 呼び出し側の初期化に注意.
void parse_api_file(kcv::sortie_api& dst, const kcv::eoen::database::kancolle_api::api_files& src) {
    const auto& name    = src.name;
    const auto& type    = src.api_file_type;
    const auto& content = src.content;

    using std::literals::string_view_literals::operator""sv;
    using file_type = kcv::eoen::database::kancolle_api::api_file_type;

    if (name == "api_get_member/ship_deck"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_battle_midnight/battle"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_battle_midnight/sp_midnight"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::sp_midnight::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_combined_battle/battle_water"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::battle_water::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_combined_battle/battleresult"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::battleresult::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_combined_battle/each_battle_water"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::each_battle_water::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_combined_battle/ec_battle"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ec_battle::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_combined_battle/ec_midnight_battle"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ec_midnight_battle::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_combined_battle/ld_airbattle"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ld_airbattle::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_combined_battle/midnight_battle"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::midnight_battle::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_map/next"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_map/start"sv and type == file_type::request) {
        using T = kcv::kcsapi::api_req_map::start::request;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_map/start"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_map/start_air_base"sv and type == file_type::request) {
        using T = kcv::kcsapi::api_req_map::start_air_base::request;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_map/start_air_base"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start_air_base::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_sortie/battle"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_sortie/battleresult"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_sortie/goback_port"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::goback_port::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_sortie/ld_airbattle"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::ld_airbattle::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    std::ofstream{"execlog.json"} << content << std::endl;
    throw kcv::exception{
        std::format(
            "failed to parse api file. "
            "[id = {}, api_file_type = {}, name = {}, time_stamp = {}, version = {}, sortie_record_id = {}], "
            "see execlog.json.",
            src.id, std::to_underlying(src.api_file_type), src.name, src.time_stamp, src.version, src.sortie_record_id
        ),
    };
}
}  // namespace impl
}  // namespace
}  // namespace kcv

void kcv::generate_battlelog(
    kcv::battlelogs_t& battlelogs,
    const kcv::eoen::database::sortie::sortie_record& sortie_record,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) {
    /// @brief `battlelogs`に書き込む基礎となる現在値あるいはキャッシュ値.
    /// 各`kcv::process_kcsapi`にて更新しながら`battlelogs`の末尾にコピー追加する.
    auto current             = kcv::battlelog{};
    current.girls_fleet_data = kcv::fleet_data_from_eoen(sortie_record.fleet_data, api_mst_ship, api_mst_slotitem);

    /// @brief 出撃APIにF5やその他何らかのエラーがある場合にtrueを設定して返る.
    bool error = false;

    for (auto api = kcv::sortie_api{}; const auto& api_file : sortie_record.api_files) {
        kcv::impl::parse_api_file(api, api_file);

        std::visit(
            [&](const auto& api) {
                kcv::process_kcsapi(battlelogs, current, api, api_mst_ship, api_mst_slotitem, error);
            },
            api
        );

        if (error) {
            break;
        }
    }
}

namespace kcv {
namespace {
namespace impl {

/// @brief 出撃艦隊を取得する(赤仮用 艦名1~6).
auto get_girls_fleet(const kcv::battlelog& data) -> const kcv::fleet& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.girls_fleet_data.fleets().at(data.attacker_fleet).value();

        case kcv::kcsapi::fleet_flag::enemy:
            return data.girls_fleet_data.fleets().at(data.defender_fleet).value();
    }

    kcv::throw_unrachable(data.attacker_side);
}

/// @brief 砲撃種別を整数にする.
auto to_integer(const decltype(kcv::battlelog::attack_kind)& v) -> std::integral auto {
    using result_t = std::common_type_t<
        std::underlying_type_t<kcv::kcsapi::day_attack_kind>,   //
        std::underlying_type_t<kcv::kcsapi::night_attack_kind>  //
        >;

    return std::visit(
        kcv::overloaded{
            [] [[noreturn]] (std::monostate) static -> result_t { throw kcv::exception{}; },
            [](kcv::kcsapi::day_attack_kind v) static -> result_t { return std::to_underlying(v); },
            [](kcv::kcsapi::night_attack_kind v) static -> result_t { return std::to_underlying(v); },
        },
        v
    );
}

/// @brief クリティカルを整数にする.
auto to_integer(const decltype(kcv::battlelog::clitical)& v) -> std::integral auto {
    using result_t = std::common_type_t<
        std::int32_t,                                      //
        std::underlying_type_t<kcv::kcsapi::air_hit_type>  //
        >;

    return std::visit(
        kcv::overloaded{
            [](std::int32_t v) static -> result_t { return v; },
            [](kcv::kcsapi::air_hit_type v) static -> result_t { return std::to_underlying(v); },
        },
        v
    );
}

void write_akakari_attacker(const kcv::battlelog& data, std::ostream& os);
void write_akakari_defender(const kcv::battlelog& data, std::ostream& os);

void write_akakari_header(std::ostream& os) {
    os << "海域,"
          "マス,"
          //   "出撃,"
          //   "ランク,"
          //   "敵艦隊,"
          //   "提督レベル,"
          "自陣形,"
          "敵陣形,"
          //   "自索敵,"
          //   "敵索敵,"
          //   "制空権,"
          "会敵,"
          //   "自触接,"
          //   "敵触接,"
          //   "自照明弾,"
          //   "敵照明弾,"
          //   "戦闘種別,"
          "艦名1,艦名2,艦名3,艦名4,艦名5,艦名6,"
          //   "開始,"
          "攻撃艦,"
          //   "砲撃種別,"
          //   "砲撃回数,"
          "表示装備1,表示装備2,表示装備3,"
          //   "クリティカル,"
          "ダメージ,"
          // "かばう,"
          //   "攻撃艦.編成順,"
          //   "攻撃艦.ID,"
          //   "攻撃艦.名前,"
          //   "攻撃艦.種別,"
          //   "攻撃艦.疲労,"
          //   "攻撃艦.戦闘後疲労,"
          //   "攻撃艦.残耐久,"
          //   "攻撃艦.最大耐久,"
          //   "攻撃艦.損傷,"
          //   "攻撃艦.残燃料,"
          //   "攻撃艦.戦闘後残燃料,"
          //   "攻撃艦.最大燃料,"
          //   "攻撃艦.残弾薬,"
          //   "攻撃艦.戦闘後残弾薬,"
          //   "攻撃艦.最大弾薬,"
          //   "攻撃艦.Lv,"
          //   "攻撃艦.速力,"
          //   "攻撃艦.火力,"
          //   "攻撃艦.雷装,"
          //   "攻撃艦.対空,"
          //   "攻撃艦.装甲,"
          //   "攻撃艦.回避,"
          //   "攻撃艦.対潜,"
          //   "攻撃艦.索敵,"
          //   "攻撃艦.運,"
          //   "攻撃艦.射程,"
          //   "攻撃艦.装備1.名前,攻撃艦.装備1.改修,攻撃艦.装備1.熟練度,攻撃艦.装備1.搭載数,攻撃艦.装備1.戦闘後搭載数,"
          //   "攻撃艦.装備2.名前,攻撃艦.装備2.改修,攻撃艦.装備2.熟練度,攻撃艦.装備2.搭載数,攻撃艦.装備2.戦闘後搭載数,"
          //   "攻撃艦.装備3.名前,攻撃艦.装備3.改修,攻撃艦.装備3.熟練度,攻撃艦.装備3.搭載数,攻撃艦.装備3.戦闘後搭載数,"
          //   "攻撃艦.装備4.名前,攻撃艦.装備4.改修,攻撃艦.装備4.熟練度,攻撃艦.装備4.搭載数,攻撃艦.装備4.戦闘後搭載数,"
          //   "攻撃艦.装備5.名前,攻撃艦.装備5.改修,攻撃艦.装備5.熟練度,攻撃艦.装備5.搭載数,攻撃艦.装備5.戦闘後搭載数,"
          //   "攻撃艦.装備6.名前,攻撃艦.装備6.改修,攻撃艦.装備6.熟練度,攻撃艦.装備6.搭載数,攻撃艦.装備6.戦闘後搭載数,"
          //   "防御艦.編成順,"
          //   "防御艦.ID,"
          //   "防御艦.名前,"
          //   "防御艦.種別,"
          //   "防御艦.疲労,"
          //   "防御艦.戦闘後疲労,"
          //   "防御艦.残耐久,"
          //   "防御艦.最大耐久,"
          //   "防御艦.損傷,"
          //   "防御艦.残燃料,"
          //   "防御艦.戦闘後残燃料,"
          //   "防御艦.最大燃料,"
          //   "防御艦.残弾薬,"
          //   "防御艦.戦闘後残弾薬,"
          //   "防御艦.最大弾薬,"
          //   "防御艦.Lv,"
          //   "防御艦.速力,"
          //   "防御艦.火力,"
          //   "防御艦.雷装,"
          //   "防御艦.対空,"
          //   "防御艦.装甲,"
          //   "防御艦.回避,"
          //   "防御艦.対潜,"
          //   "防御艦.索敵,"
          //   "防御艦.運,"
          //   "防御艦.射程,"
          //   "防御艦.装備1.名前,防御艦.装備1.改修,防御艦.装備1.熟練度,防御艦.装備1.搭載数,防御艦.装備1.戦闘後搭載数,"
          //   "防御艦.装備2.名前,防御艦.装備2.改修,防御艦.装備2.熟練度,防御艦.装備2.搭載数,防御艦.装備2.戦闘後搭載数,"
          //   "防御艦.装備3.名前,防御艦.装備3.改修,防御艦.装備3.熟練度,防御艦.装備3.搭載数,防御艦.装備3.戦闘後搭載数,"
          //   "防御艦.装備4.名前,防御艦.装備4.改修,防御艦.装備4.熟練度,防御艦.装備4.搭載数,防御艦.装備4.戦闘後搭載数,"
          //   "防御艦.装備5.名前,防御艦.装備5.改修,防御艦.装備5.熟練度,防御艦.装備5.搭載数,防御艦.装備5.戦闘後搭載数,"
          //   "防御艦.装備6.名前,防御艦.装備6.改修,防御艦.装備6.熟練度,防御艦.装備6.搭載数,防御艦.装備6.戦闘後搭載数"
          //   "艦隊種類,"
          //   "敵艦隊種類,"
          //   "自探照灯.位置,"
          //   "自探照灯.装備,"
          //   "敵探照灯.位置,"
          //   "敵探照灯.装備,"
          //   "装甲破砕"
          "\n";
}

void write_akakari_row(const kcv::battlelog& data, std::ostream& os) {
    // 海域,マス.
    std::print(os, "{},{},{},", data.world, data.map, data.cell);
    // 自陣形.
    std::print(os, "{},", kcv::to_string(kcv::get_attacker_formation(data)));
    // 敵陣形.
    std::print(os, "{},", kcv::to_string(kcv::get_defender_formation(data)));
    // 会敵.
    std::print(os, "{},", kcv::to_string(data.engagement));
    // 艦名1,艦名2,艦名3,艦名4,艦名5,艦名6.
    for (const auto& girls = kcv::impl::get_girls_fleet(data).ships(); auto i : std::ranges::views::iota(0uz, 6uz)) {
        if (i < girls.size()) {
            std::print(os, "{},", girls.at(i).mst().api_name);
        } else {
            std::print(os, ",");
        }
    }
    // 攻撃艦.
    std::print(os, "{},", kcv::to_string(data.attacker_side));
    // 砲撃種別.
    std::print(os, "{}", kcv::impl::to_integer(data.attack_kind));
    // 表示装備.
    for (auto i : std::ranges::views::iota(0uz, 3uz)) {
        if (i < data.display_equipments.size()) {
            /// XXX: 赤仮は装備名で出力する.
            std::print(os, "{},", std::to_underlying(data.display_equipments.at(i)));
        } else {
            std::print(os, ",");
        }
    }
    // クリティカル.
    std::print(os, "{}", kcv::impl::to_integer(data.clitical));
    // ダメージ.
    std::print(os, "{},", data.damage);
    // かばう.
    std::print(os, "{}", +data.is_protected);
    // 攻撃艦.
    // kcv::impl::write_akakari_attacker(data, os);
    // 防御艦.
    // kcv::impl::write_akakari_defender(data, os);

    os << '\n';
}

}  // namespace impl
}  // namespace
}  // namespace kcv

void kcv::write_akakari(const kcv::battlelogs_t& battlelogs, const std::filesystem::path& fname) {
    auto os = std::ofstream{fname};

    kcv::impl::write_akakari_header(os);

    for (const auto& data : battlelogs) {
        kcv::impl::write_akakari_row(data, os);
    }
}