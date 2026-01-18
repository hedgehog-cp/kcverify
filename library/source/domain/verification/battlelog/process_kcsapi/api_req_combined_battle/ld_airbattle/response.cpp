#include "domain/verification/battlelog/process_kcsapi.hpp"

// std
#include <vector>

// kcv
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/external/kcsapi/api_req_combined_battle/ld_airbattle/response.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_ship.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcv/external/kcsapi/types/svdata.hpp"

void kcv::process_kcsapi(
    kcv::battlelogs_t& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ld_airbattle::response>& svdata,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    bool& error
) {}