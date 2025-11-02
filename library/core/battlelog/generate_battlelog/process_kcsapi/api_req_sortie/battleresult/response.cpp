#include "core/battlelog/generate_battlelog/process_kcsapi.hpp"

// std
#include <vector>

// kcv
#include "core/battlelog/battlelog.hpp"
#include "core/battlelog/generate_battlelog/process_kcsapi/common.hpp"
#include "models/kcsapi/api_req_sortie/battleresult/response.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/svdata.hpp"

namespace {

void set_enemy_fleet_name(
    std::vector<kcv::battlelog>& battlelogs,
    const kcv::kcsapi::api_req_sortie::battleresult::response& data
) {
    for (auto& battlelog : battlelogs) {
        for (auto& fleet : battlelog.abyssal_fleet_data.fleets()) {
            if (fleet.has_value()) {
                if (fleet->name() == kcv::uninitialized_enemy_fleet_name_tag) {
                    fleet->name(data.api_enemy_info.api_deck_name);
                }
            }
        }
    }
}

}  // namespace

void kcv::process_kcsapi(
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs,
    [[maybe_unused]] kcv::battlelog& current,
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] bool& error
) {
    if (not kcv::success(svdata)) {
        error = true;
        return;
    }

    const auto& data = svdata.api_data;

    set_enemy_fleet_name(battlelogs, data);
}
