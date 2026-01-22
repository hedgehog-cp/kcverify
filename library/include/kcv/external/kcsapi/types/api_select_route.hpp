#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_SELECT_ROUTE_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_SELECT_ROUTE_HPP_INCLUDED

#include <cstdint>
#include <vector>

namespace kcv {
namespace kcsapi {

/// @brief 能動分岐マス.
struct api_select_route final {
    /// @brief 選択可能なセルIDのリスト.
    std::vector<std::int32_t> api_select_cells;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_SELECT_ROUTE_HPP_INCLUDED
