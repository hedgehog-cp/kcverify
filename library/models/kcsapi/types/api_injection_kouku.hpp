#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_INJECTION_KOUKU_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_INJECTION_KOUKU_HPP_INCLUDED

// std
#include <optional>
#include <vector>

// kcv
#include "models/kcsapi/types/api_stage1.hpp"
#include "models/kcsapi/types/api_stage2.hpp"
#include "models/kcsapi/types/api_stage3.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 噴式強襲航空攻撃.
struct api_injection_kouku final {
    /// @brief 航空機発艦可能艦インデックス[2]. [0]=味方, [1]=敵. いなければnull. 1基点.
    std::vector<std::optional<std::vector<std::int32_t>>> api_plane_from;

    /// @brief 空対空戦闘.
    std::optional<kcv::kcsapi::api_stage1> api_stage1;

    /// @brief 艦対空戦闘.
    std::optional<kcv::kcsapi::api_stage2> api_stage2;

    /// @brief ：航空攻撃.
    std::optional<kcv::kcsapi::api_stage3> api_stage3;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_INJECTION_KOUKU_HPP_INCLUDED
