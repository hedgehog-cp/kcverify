#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_AIR_BASE_INJECTION_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_AIR_BASE_INJECTION_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "models/kcsapi/types/api_squadron_plane.hpp"
#include "models/kcsapi/types/api_stage1and2jet.hpp"
#include "models/kcsapi/types/api_stage3jet.hpp"
#include "models/kcsapi/types/api_stage3jet_combined.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 基地航空隊噴式強襲.
struct api_air_base_injection final {
    std::vector<kcv::kcsapi::api_squadoron_plane> api_air_base_data;
    std::vector<std::optional<std::vector<std::int32_t>>> api_plane_from;
    std::optional<kcv::kcsapi::api_stage1and2jet> api_stage1;
    std::optional<kcv::kcsapi::api_stage1and2jet> api_stage2;
    std::optional<kcv::kcsapi::api_stage3jet> api_stage3;
    std::optional<kcv::kcsapi::api_stage3jet_combined> api_stage3_combined;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_AIR_BASE_INJECTION_HPP_INCLUDED
