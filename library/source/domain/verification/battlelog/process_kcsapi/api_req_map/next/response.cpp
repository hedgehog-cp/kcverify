#include "domain/verification/battlelog/process_kcsapi.hpp"

// std
#include <vector>

// kcv
#include "domain/verification/battlelog/common.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/external/kcsapi/api_req_map/next/response.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_ship.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcv/external/kcsapi/types/svdata.hpp"

void kcv::process_kcsapi(
    [[maybe_unused]] kcv::battlelogs_t& battlelogs,
    [[maybe_unused]] kcv::battlelog& current,
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] bool& error
) {
    if (not kcv::success(svdata)) {
        error = true;
        return;
    }

    const auto& data = svdata.api_data;

    current.cell = data.api_no;
}
