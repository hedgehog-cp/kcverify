#include "core/battlelog/process_api.hpp"

// std
#include <vector>

// kcv
#include "core/battlelog/battlelog.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/kcsapi/api_req_combined_battle/ld_airbattle/response.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/svdata.hpp"

void kcv::process_api(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ld_airbattle::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    bool& error
) {}