#include "core/battlelog/sortie_api.hpp"

// std
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

auto kcv::parse_api_files(  //
    const std::vector<kcv::eoen::database::kancolle_api::api_files>& src
) -> std::vector<kcv::sortie_api> {
    auto dst = std::vector<kcv::sortie_api>{};
    dst.reserve(src.size());

    for (const auto& e : src) {
        const auto& type    = e.api_file_type;
        const auto& name    = e.name;
        const auto& content = e.content;

        // std::vectorの要素をapi構造体Tで初期化し(emplace_back),
        // その初期化された領域にTとしてapiを読み込む(read_json).
        using std::literals::string_view_literals::operator""sv;
        using file_type = kcv::eoen::database::kancolle_api::api_file_type;
        if (name == "api_req_map/start"sv and type == file_type::request) {
            using T = kcv::kcsapi::api_req_map::start::request;
            kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content);
            continue;
        }
        if (name == "api_req_map/start"sv and type == file_type::response) {
            using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>;
            kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content);
            continue;
        }
        if (name == "api_req_sortie/battle"sv and type == file_type::response) {
            using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>;
            kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content);
            continue;
        }
        if (name == "api_req_battle_midnight/battle"sv and type == file_type::response) {
            using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>;
            kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content);
            continue;
        }
        if (name == "api_req_sortie/battleresult"sv and type == file_type::response) {
            using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>;
            kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content);
            continue;
        }
        if (name == "api_get_member/ship_deck"sv and type == file_type::response) {
            using T = kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>;
            kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content);
            continue;
        }
        if (name == "api_req_map/next"sv and type == file_type::response) {
            using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>;
            kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content);
            continue;
        }

        throw kcv::exception{
            std::format(
                "id: {}, api_file_type: {}, name: {}, time_stamp: {}, version: {}, sortie_record_id: {}",  //
                e.id, std::to_underlying(e.api_file_type), e.name, e.time_stamp, e.version, e.sortie_record_id
            ),
        };
    }

    return dst;
}

namespace {

template <typename T>
bool success(const kcv::kcsapi::svdata<T>& svdata) noexcept {
    return svdata.api_result == 1 and svdata.api_result_msg == std::string_view{"成功"};
}

}  // namespace

void kcv::process_api(
    [[maybe_unused]] const std::monostate&,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    // unreachable
}

void kcv::process_api(
    [[maybe_unused]] const kcv::kcsapi::api_req_map::start::request& start_request,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    //
}

void kcv::process_api(
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    //
}

void kcv::process_api(
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    //
}

void kcv::process_api(
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    //
}

void kcv::process_api(
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    //
}

void kcv::process_api(
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    //
}

void kcv::process_api(
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] const kcv::eoen::database::sortie::sortie_record& sortie_record,
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs
) {
    //
}
