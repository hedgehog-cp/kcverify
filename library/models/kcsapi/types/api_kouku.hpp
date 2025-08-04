#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_KOUKU_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_KOUKU_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "models/kcsapi/types/api_stage1.hpp"
#include "models/kcsapi/types/api_stage2.hpp"
#include "models/kcsapi/types/api_stage3.hpp"
#include "models/kcsapi/types/api_stage3_combined.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 航空戦情報
struct api_kouku final {
    std::vector<std::optional<std::vector<std::int32_t>>> api_plane_from;
    std::optional<kcv::kcsapi::api_stage1> api_stage1;
    std::optional<kcv::kcsapi::api_stage2> api_stage2;
    std::optional<kcv::kcsapi::api_stage3> api_stage3;
    std::optional<kcv::kcsapi::api_stage3_combined> api_stage3_combined;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_KOUKU_HPP_INCLUDED
