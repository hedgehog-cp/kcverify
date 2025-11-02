#include "core/battlelog/generate_battlelog/process_kcsapi.hpp"

// std
#include <vector>

// kcv
#include "core/battlelog/battlelog.hpp"
#include "models/kcsapi/api_req_map/start_air_base/request.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"

void kcv::process_kcsapi(
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs,
    [[maybe_unused]] kcv::battlelog& current,
    [[maybe_unused]] const kcv::kcsapi::api_req_map::start_air_base::request& data,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] bool& error
) {}
