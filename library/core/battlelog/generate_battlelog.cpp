#include "core/battlelog/generate_battlelog.hpp"

// std
#include <utility>
#include <variant>
#include <vector>

// kcv
#include "core/battlelog/battlelog.hpp"
#include "core/utility/read_json.hpp"
#include "extensions/exception.hpp"
#include "extensions/formatter.hpp"
#include "models/eoen/database/kancolle_api/api_files.hpp"
#include "models/eoen/database/sortie/sortie_record.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/kcsapi/api_get_member/ship_deck/response.hpp"
#include "models/kcsapi/api_req_battle_midnight/battle/response.hpp"
#include "models/kcsapi/api_req_map/next/response.hpp"
#include "models/kcsapi/api_req_map/start/request.hpp"
#include "models/kcsapi/api_req_map/start/response.hpp"
#include "models/kcsapi/api_req_sortie/battle/response.hpp"
#include "models/kcsapi/api_req_sortie/battleresult/response.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/svdata.hpp"

namespace {

using sortie_api = std::variant<
    std::monostate,
    kcv::kcsapi::api_req_map::start::request,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>>;

auto parse_api_files(const std::vector<kcv::eoen::database::kancolle_api::api_files>& src) -> std::vector<sortie_api> {
    auto apis = std::vector<sortie_api>{};
    apis.reserve(src.size());

    for (const auto& e : src) {
        const auto& type    = e.api_file_type;
        const auto& name    = e.name;
        const auto& content = e.content;

        // std::vectorの要素をapi構造体Tで初期化し(emplace_back),
        // その初期化された領域にTとしてapiを読み込む(read_json).
        using std::literals::string_view_literals::operator""sv;
        using file_type = kcv::eoen::database::kancolle_api::api_file_type;
        if (name == "api_req_map/start"sv and type == file_type::request) {
            using T   = kcv::kcsapi::api_req_map::start::request;
            auto& dst = std::get<T>(apis.emplace_back<T>({}));
            kcv::read_json(dst, content);
        } else if (name == "api_req_map/start"sv and type == file_type::response) {
            using T   = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>;
            auto& dst = std::get<T>(apis.emplace_back<T>({}));
            kcv::read_json(dst, content);
        } else if (name == "api_req_sortie/battle"sv and type == file_type::response) {
            using T   = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>;
            auto& dst = std::get<T>(apis.emplace_back<T>({}));
            kcv::read_json(dst, content);
        } else if (name == "api_req_battle_midnight/battle"sv and type == file_type::response) {
            using T   = kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>;
            auto& dst = std::get<T>(apis.emplace_back<T>({}));
            kcv::read_json(dst, content);
        } else if (name == "api_req_sortie/battleresult"sv and type == file_type::response) {
            using T   = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>;
            auto& dst = std::get<T>(apis.emplace_back<T>({}));
            kcv::read_json(dst, content);
        } else if (name == "api_get_member/ship_deck"sv and type == file_type::response) {
            using T   = kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>;
            auto& dst = std::get<T>(apis.emplace_back<T>({}));
            kcv::read_json(dst, content);
        } else if (name == "api_req_map/next"sv and type == file_type::response) {
            using T   = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>;
            auto& dst = std::get<T>(apis.emplace_back<T>({}));
            kcv::read_json(dst, content);
        } else {
            throw kcv::exception{
                std::format(
                    "id: {}, api_file_type: {}, name: {}, time_stamp: {}, version: {}, sortie_record_id: {}",  //
                    e.id, std::to_underlying(e.api_file_type), e.name, e.time_stamp, e.version, e.sortie_record_id
                ),
            };
        }
    }

    return apis;
}

template <typename T>
bool success(const kcv::kcsapi::svdata<T>& svdata) noexcept {
    return svdata.api_result == 1 and svdata.api_result_msg == std::string_view{"成功"};
}

[[noreturn]]
void process_api(
    [[maybe_unused]] const std::monostate&,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    std::unreachable();
}

void process_api(
    [[maybe_unused]] const kcv::kcsapi::api_req_map::start::request& start_request,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    //
}

void process_api(
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    //
}

void process_api(
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    if (not success(svdata)) {
        //
    }

    const auto& data = svdata.api_data;

    // 索敵
    data.api_search;

    // 基地航空隊噴式強襲
    data.api_air_base_injection;

    // 噴式強襲
    data.api_injection_kouku;

    // 基地航空隊航空戦
    data.api_air_base_attack;

    // 機動部隊航空友軍
    data.api_friendly_kouku;

    // 航空戦 制空権の決定を含む
    data.api_kouku;

    // 支援艦隊攻撃
    data.api_support_flag;
    data.api_support_info;

    // 先制対潜攻撃
    data.api_opening_taisen_flag;
    data.api_opening_taisen;

    // 開幕雷撃
    data.api_opening_flag;
    data.api_opening_atack;

    // 交戦形態の表示交戦形態自体は戦闘開始時に決まっている模様
    data.api_formation;

    // 砲雷撃戦判定
    data.api_hourai_flag;

    // 砲撃戦→砲撃戦2巡目
    data.api_hougeki1;
    data.api_hougeki2;
    data.api_hougeki3;

    // 雷撃戦→戦闘終了or夜戦突入判定
    data.api_raigeki;

    data.api_midnight_flag;

    // 友軍艦隊攻撃
    // 夜戦
}

void process_api(
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    //
}

void process_api(
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    //
}

void process_api(
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    //
}

void process_api(
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    //
}

using sortie_api = std::variant<
    std::monostate,
    kcv::kcsapi::api_req_map::start::request,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>>;

}  // namespace

auto kcv::generate_battlelog(
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    const kcv::eoen::database::sortie::sortie_record& sortie_record
) -> std::vector<kcv::battlelog> {
    auto battlelogs = std::vector<kcv::battlelog>{};

    const auto sortie_apis = parse_api_files(sortie_record.api_files);
    for (const auto& api : sortie_apis) {
        std::visit(
            [&](const auto& v) {
                process_api(v, api_mst_ship, api_mst_slotitem, fit_bonuses, sortie_record, battlelogs);
            },
            api
        );
    }

    return battlelogs;
}