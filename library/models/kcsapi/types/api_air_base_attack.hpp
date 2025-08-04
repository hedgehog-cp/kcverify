#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_AIR_BASE_ATTACK_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_AIR_BASE_ATTACK_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "models/kcsapi/types/api_squadron_plane.hpp"
#include "models/kcsapi/types/api_stage1.hpp"
#include "models/kcsapi/types/api_stage2.hpp"
#include "models/kcsapi/types/api_stage3.hpp"
#include "models/kcsapi/types/api_stage3_combined.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 基地航空隊攻撃.
struct api_air_base_attack_value_t final {
    std::int32_t api_base_id;
    std::vector<std::optional<std::vector<std::int32_t>>> api_plane_from;
    std::vector<kcv::kcsapi::api_squadoron_plane> api_squadron_plane;
    std::optional<kcv::kcsapi::api_stage1> api_stage1;
    std::optional<kcv::kcsapi::api_stage2> api_stage2;
    std::optional<kcv::kcsapi::api_stage3> api_stage3;
    std::optional<kcv::kcsapi::api_stage3_combined> api_stage3_combined;
    std::vector<std::int32_t> api_stage_flag;
};

/// @brief 基地航空隊攻撃. [攻撃回数].
using api_air_base_attack = std::vector<api_air_base_attack_value_t>;

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_AIR_BASE_ATTACK_HPP_INCLUDED
