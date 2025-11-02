#include "core/battlelog/generate_battlelog/process_kcsapi.hpp"

// std
#include <vector>

// kcv
#include "core/battlelog/battlelog.hpp"
#include "models/kcsapi/api_req_combined_battle/ec_midnight_battle/response.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/svdata.hpp"

void kcv::process_kcsapi(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ec_midnight_battle::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    bool& error
) {}