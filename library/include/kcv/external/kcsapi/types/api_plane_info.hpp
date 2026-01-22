#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_PLANE_INFO_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_PLANE_INFO_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "kcv/external/kcsapi/types/api_unset_slot.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 基地航空隊関連データ.
struct api_plane_info final {
    /// @brief 配置転換中の装備IDリスト[].
    std::optional<std::vector<std::int32_t>> api_base_convert_slot;

    /// @brief
    std::optional<std::vector<kcv::kcsapi::api_unset_slot>> api_unset_slot;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_PLANE_INFO_HPP_INCLUDED
