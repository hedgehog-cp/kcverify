#ifndef KCVERIFY_KCAPI_TYPES_API_SELECT_ROUTE_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_SELECT_ROUTE_HPP_INCLUDED

#include <vector>

namespace kcv {
namespace kcapi {

/// @brief 能動分岐マス.
struct api_select_route final {
    /// @brief 選択可能なセルIDのリスト.
    std::vector<int> api_select_cells;
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_SELECT_ROUTE_HPP_INCLUDED
