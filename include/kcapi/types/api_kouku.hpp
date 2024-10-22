#ifndef KCVERIFY_KCAPI_TYPES_API_KOUKU_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_KOUKU_HPP_INCLUDED

// std
#include <optional>
#include <vector>

// kcv
#include "kcapi/types/api_stage1.hpp"
#include "kcapi/types/api_stage2.hpp"
#include "kcapi/types/api_stage3.hpp"
#include "kcapi/types/api_stage3_combined.hpp"

namespace kcv {
namespace kcapi {

/// @brief 航空戦情報
struct api_kouku final {
    std::vector<std::optional<std::vector<int>>> api_plane_from;
    std::optional<kcapi::api_stage1> api_stage1;
    std::optional<kcapi::api_stage2> api_stage2;
    std::optional<kcapi::api_stage3> api_stage3;
    std::optional<kcapi::api_stage3_combined> api_stage3_combined;
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_KOUKU_HPP_INCLUDED
