#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_SUPPORT_INFO_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_SUPPORT_INFO_HPP_INCLUDED

// std
#include <optional>

// kcv
#include "kcv/external/kcsapi/types/api_support_airatack.hpp"
#include "kcv/external/kcsapi/types/api_support_hourai.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 支援艦隊情報. api_support_flag = 0 なら null.
struct api_support_info final {
    /// @brief 空撃もしくは対潜の時有効. それ以外はnull.
    std::optional<kcv::kcsapi::api_support_airatack> api_support_airatack;

    /// @brief 砲撃もしくは雷撃の時有効. それ以外はnull.
    std::optional<kcv::kcsapi::api_support_hourai> api_support_hourai;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_SUPPORT_INFO_HPP_INCLUDED
