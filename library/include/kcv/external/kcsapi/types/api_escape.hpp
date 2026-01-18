#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_ESCAPE_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_ESCAPE_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "kcv/external/kcsapi/types/enum/escape_type.hpp"
namespace kcv {
namespace kcsapi {

/// @brief 退避艦. api_esace_flag==0のときnull.
struct api_escape final {
    /// @brief 退避艦のインデックス. [対象艦数]. 1基点, 実際は[0]が対象となる.
    std::vector<std::int32_t> api_escape_idx;

    /// @brief 護衛艦のインデックス. [対象艦数]. 1基点. 実際は[0]が対象となる. 連合艦隊時のみ存在.
    std::optional<std::vector<std::int32_t>> api_tow_idx;

    /// @brief 退避のタイプ. 1=遊撃部隊退避, 2=水雷戦隊退避.
    kcv::kcsapi::escape_type api_escape_type;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_ESCAPE_HPP_INCLUDED
