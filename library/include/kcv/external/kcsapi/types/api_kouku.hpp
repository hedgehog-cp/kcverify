#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_KOUKU_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_KOUKU_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "kcv/external/kcsapi/types/api_stage1.hpp"
#include "kcv/external/kcsapi/types/api_stage2.hpp"
#include "kcv/external/kcsapi/types/api_stage3.hpp"
#include "kcv/external/kcsapi/types/api_stage3_combined.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 航空戦情報
struct api_kouku final {
    /// @brief 航空機発艦可能艦インデックス[2]. [0]=味方, [1]=敵. いなければnull. 1基点.
    std::vector<std::optional<std::vector<std::int32_t>>> api_plane_from;

    /// @brief 空対空戦闘.
    std::optional<kcv::kcsapi::api_stage1> api_stage1;

    /// @brief 艦対空戦闘.
    std::optional<kcv::kcsapi::api_stage2> api_stage2;

    /// @brief ：航空攻撃. [味方の艦船数] or [敵の艦船数].
    std::optional<kcv::kcsapi::api_stage3> api_stage3;

    std::optional<kcv::kcsapi::api_stage3_combined> api_stage3_combined;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_KOUKU_HPP_INCLUDED
