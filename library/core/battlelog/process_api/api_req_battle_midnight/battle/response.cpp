#include "core/battlelog/process_api.hpp"

// std
#include <vector>

// kcv
#include "core/battlelog/battlelog.hpp"
#include "core/battlelog/process_api/common.hpp"
#include "core/entity/fleet_data.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/kcsapi/api_req_battle_midnight/battle/response.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/api_friendly_battle.hpp"
#include "models/kcsapi/types/api_friendly_info.hpp"
#include "models/kcsapi/types/api_hougeki.hpp"
#include "models/kcsapi/types/svdata.hpp"

namespace {

/// @brief 状況開始.
void initialize_situation(kcv::battlelog& current, const kcv::kcsapi::api_req_battle_midnight::battle::response& data) {
    current.x_al01            = data.api_x_al01;
    current.balloon_cell      = data.api_balloon_cell;
    current.atoll_cell        = data.api_atoll_cell;
    current.girls_formation   = std::get<0>(data.api_formation);
    current.abyssal_formation = std::get<1>(data.api_formation);
    current.engagement        = std::get<2>(data.api_formation);
}

/// @brief 敵艦隊を初期化.
void initialize_abyssal_fleet_data(
    kcv::battlelog& current,
    const kcv::kcsapi::api_req_battle_midnight::battle::response& data
) {}

/// @brief 友軍艦隊を構築.
auto make_friend_fleet_data(
    const kcv::kcsapi::api_friendly_info& data,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::fleet_data {}

/// @brief 友軍艦隊夜戦攻撃をもって戦闘ログを更新する.
void update(
    kcv::battlelog& current,
    std::vector<kcv::battlelog>& battlelogs,
    const kcv::fleet_data& friend_fleet_data,
    const kcv::kcsapi::api_friendly_battle& data
) {
    //
}

/// @brief 夜戦攻撃をもって戦闘ログを更新する.
void update(kcv::battlelog& current, std::vector<kcv::battlelog>& battlelogs, const kcv::kcsapi::api_hougeki& data) {
    //
}

}  // namespace

void kcv::process_api(
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs,
    [[maybe_unused]] kcv::battlelog& current,
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] bool& error
) {
    if (not kcv::success(svdata)) {
        error = true;
        return;
    }

    const auto& data = svdata.api_data;

    // 状況開始.
    initialize_situation(current, data);

    //
    initialize_abyssal_fleet_data(current, data);

    // 友軍.
    if (data.api_friendly_info.has_value() and data.api_friendly_battle.has_value()) {
        // 友軍艦隊を構築.
        const auto friend_fleet_data = make_friend_fleet_data(*data.api_friendly_info, api_mst_ship, api_mst_slotitem);

        // ダメージ更新.
        update(current, battlelogs, friend_fleet_data, *data.api_friendly_battle);
    }

    // 本隊.
    if (data.api_hougeki.has_value()) {
        update(current, battlelogs, *data.api_hougeki);
    }
}
