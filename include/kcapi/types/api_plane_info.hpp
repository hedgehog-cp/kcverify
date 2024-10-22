#ifndef KCVERIFY_KCAPI_TYPES_API_PLANE_INFO_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_PLANE_INFO_HPP_INCLUDED

// std
#include <optional>
#include <vector>

// kcv
#include "kcapi/types/api_unset_slot.hpp"

namespace kcv {
namespace kcapi {

/// @brief 基地航空隊関連データ.
struct api_plane_info final {
    /// @brief 配置転換中の装備IDリスト[].
    std::optional<std::vector<int>> api_base_convert_slot;

    /// @brief
    std::optional<std::vector<kcapi::api_unset_slot>> api_unset_slot;
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_PLANE_INFO_HPP_INCLUDED
