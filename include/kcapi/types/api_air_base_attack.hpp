#ifndef KCVERIFY_KCAPI_TYPES_API_AIR_BASE_ATTACK_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_AIR_BASE_ATTACK_HPP_INCLUDED

// std
#include <optional>
#include <vector>

// kcv
#include "kcapi/types/api_squadron_plane.hpp"
#include "kcapi/types/api_stage1.hpp"
#include "kcapi/types/api_stage2.hpp"
#include "kcapi/types/api_stage3.hpp"
#include "kcapi/types/api_stage3_combined.hpp"

namespace kcv {
namespace kcapi {

/// @brief 基地航空隊攻撃.
struct api_air_base_attack_value_type final {
    int api_base_id;
    std::vector<std::optional<std::vector<int>>> api_plane_from;
    std::vector<kcapi::api_squadoron_plane> api_squadron_plane;
    std::optional<kcapi::api_stage1> api_stage1;
    std::optional<kcapi::api_stage2> api_stage2;
    std::optional<kcapi::api_stage3> api_stage3;
    std::optional<kcapi::api_stage3_combined> api_stage3_combined;
    std::vector<int> api_stage_flag;
};

/// @brief 基地航空隊攻撃. [攻撃回数].
using api_air_base_attack = std::vector<api_air_base_attack_value_type>;

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_AIR_BASE_ATTACK_HPP_INCLUDED
