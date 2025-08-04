#ifndef KCVERIFY_CORE_BATTLELOG_SORTIE_API_HPP_INCLUDED
#define KCVERIFY_CORE_BATTLELOG_SORTIE_API_HPP_INCLUDED

// std
#include <variant>
#include <vector>

// kcv
#include "core/battlelog/battlelog.hpp"
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

namespace kcv {

using sortie_api = std::variant<
    std::monostate,
    kcv::kcsapi::api_req_map::start::request,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>>;

auto parse_api_files(const std::vector<kcv::eoen::database::kancolle_api::api_files>& src) -> std::vector<sortie_api>;

void process_api(
    const std::monostate&,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    const kcv::eoen::database::sortie::sortie_record& sortie_record,
    std::vector<kcv::battlelog>& battlelogs
);

void process_api(
    const kcv::kcsapi::api_req_map::start::request& start_request,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    const kcv::eoen::database::sortie::sortie_record& sortie_record,
    std::vector<kcv::battlelog>& battlelogs
);

void process_api(
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    const kcv::eoen::database::sortie::sortie_record& sortie_record,
    std::vector<kcv::battlelog>& battlelogs
);

void process_api(
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    const kcv::eoen::database::sortie::sortie_record& sortie_record,
    std::vector<kcv::battlelog>& battlelogs
);

void process_api(
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    const kcv::eoen::database::sortie::sortie_record& sortie_record,
    std::vector<kcv::battlelog>& battlelogs
);

void process_api(
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    const kcv::eoen::database::sortie::sortie_record& sortie_record,
    std::vector<kcv::battlelog>& battlelogs
);

void process_api(
    const kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    const kcv::eoen::database::sortie::sortie_record& sortie_record,
    std::vector<kcv::battlelog>& battlelogs
);

void process_api(
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    const kcv::eoen::database::sortie::sortie_record& sortie_record,
    std::vector<kcv::battlelog>& battlelogs
);

}  // namespace kcv

#endif  // KCVERIFY_CORE_BATTLELOG_SORTIE_API_HPP_INCLUDED
