#include "core/battlelog/process_api.hpp"

// std
#include <vector>

// kcv
#include "core/battlelog/battlelog.hpp"
#include "core/battlelog/process_api/common.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/kcsapi/api_get_member/ship_deck/response.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/svdata.hpp"

namespace {

void update_girls_fleet_data(kcv::battlelog& current, const kcv::kcsapi::api_get_member::ship_deck::response& data) {
    //
}

}  // namespace

void kcv::process_api(
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs,
    [[maybe_unused]] kcv::battlelog& current,
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>& svdata,
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

    update_girls_fleet_data(current, data);
}
