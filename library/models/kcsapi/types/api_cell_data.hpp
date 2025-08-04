#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_CELL_DATA_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_CELL_DATA_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "models/kcsapi/types/enum/cell_type.hpp"

namespace kcv {
namespace kcsapi {

/// @brief セルデータ.
struct api_cell_data_value_t final {
    /// @brief セルタイプ. セルの状態.
    kcv::kcsapi::cell_type api_color_no;

    /// @brief 基地からの距離. 基地航空隊出撃時のみ存在.
    std::optional<std::int32_t> api_distance;

    /// @brief 海域セルユニークID.
    std::int32_t api_id;

    /// @brief 海域セルID.
    std::int32_t api_no;

    /// @brief 0=初期地点 || 未通行, 1=通行済み.
    std::int32_t api_passed;
};

/// @brief 当該海域の全セルデータ.
using api_cell_data = std::vector<api_cell_data_value_t>;

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_CELL_DATA_HPP_INCLUDED
