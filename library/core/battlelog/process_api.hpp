#ifndef KCVERIFY_CORE_BATTLELOG_PROCESS_API_HPP_INCLUDED
#define KCVERIFY_CORE_BATTLELOG_PROCESS_API_HPP_INCLUDED

// std
#include <utility>
#include <variant>
#include <vector>

// kcv
#include "core/battlelog/battlelog.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/kcsapi/api_get_member/ship_deck/response.hpp"
#include "models/kcsapi/api_req_battle_midnight/battle/response.hpp"
#include "models/kcsapi/api_req_battle_midnight/sp_midnight/response.hpp"
#include "models/kcsapi/api_req_combined_battle/battle_water/response.hpp"
#include "models/kcsapi/api_req_combined_battle/battleresult/response.hpp"
#include "models/kcsapi/api_req_combined_battle/each_battle_water/response.hpp"
#include "models/kcsapi/api_req_combined_battle/ec_battle/response.hpp"
#include "models/kcsapi/api_req_combined_battle/ec_midnight_battle/response.hpp"
#include "models/kcsapi/api_req_combined_battle/ld_airbattle/response.hpp"
#include "models/kcsapi/api_req_combined_battle/midnight_battle/response.hpp"
#include "models/kcsapi/api_req_map/next/response.hpp"
#include "models/kcsapi/api_req_map/start/request.hpp"
#include "models/kcsapi/api_req_map/start/response.hpp"
#include "models/kcsapi/api_req_map/start_air_base/request.hpp"
#include "models/kcsapi/api_req_map/start_air_base/response.hpp"
#include "models/kcsapi/api_req_sortie/battle/response.hpp"
#include "models/kcsapi/api_req_sortie/battleresult/response.hpp"
#include "models/kcsapi/api_req_sortie/goback_port/response.hpp"
#include "models/kcsapi/api_req_sortie/ld_airbattle/response.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/svdata.hpp"

namespace kcv {

/// @brief 出撃API.
using sortie_api = std::variant<
    std::monostate,
    kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::sp_midnight::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::battle_water::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::battleresult::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::each_battle_water::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ec_battle::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ec_midnight_battle::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ld_airbattle::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::midnight_battle::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>,
    kcv::kcsapi::api_req_map::start::request,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>,
    kcv::kcsapi::api_req_map::start_air_base::request,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start_air_base::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::goback_port::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::ld_airbattle::response> >;

/// @brief 出撃APIのvisitor関数の一つ. この関数は呼び出されない.
/// @param battlelogs 戦闘ログ.
/// @param current `battlelogs`に書き込む基礎となる現在値あるいはキャッシュ値.
/// @param api_mst_ship 艦船マスタ.
/// @param api_mst_slotitem 装備マスタ.
/// @param fit_bonuses 74式EN固有の装備ボーナスオブジェクト.
/// @param error 出撃APIにF5やその他何らかのエラーがある場合にtrueを設定して返る.
[[noreturn]] inline void process_api(
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs,
    [[maybe_unused]] kcv::battlelog& current,
    [[maybe_unused]] const std::monostate&,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] bool& error
) {
    std::unreachable();
}

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::sp_midnight::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::battle_water::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::battleresult::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::each_battle_water::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ec_battle::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ec_midnight_battle::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ld_airbattle::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::midnight_battle::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::api_req_map::start::request& data,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::api_req_map::start_air_base::request& data,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start_air_base::response>& data,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::goback_port::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

/// @brief 出撃APIのvisitor関数の一つ.
void process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::ld_airbattle::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
);

}  // namespace kcv

#endif  // KCVERIFY_CORE_BATTLELOG_PROCESS_API_HPP_INCLUDED
