#ifndef KCVERIFY_KCSAPI_TYPES_API_SELECT_ROUTE_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_API_SELECT_ROUTE_HPP_INCLUDED

#include <vector>

namespace kcv {
namespace kcsapi {

/// @brief 能動分岐マス.
struct api_select_route final {
    /// @brief 選択可能なセルIDのリスト.
    std::vector<int> api_select_cells;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_API_SELECT_ROUTE_HPP_INCLUDED
