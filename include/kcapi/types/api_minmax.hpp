#ifndef KCVERIFY_KCAPI_TYPES_API_MINMAX_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_MINMAX_HPP_INCLUDED

#include <array>
#include <cstddef>

namespace kcv {
namespace kcapi {

namespace detail {
struct idx_minmax final {
    enum _ : std::size_t {
        min,
        max,
    };
};

}  // namespace detail

using idx_minmax = detail::idx_minmax::_;

/// @brief [0]: min. [1]: max.
/// @note std::tupleにするとclangでコンパイルできない.
using api_minmax = std::array<int, 2>;

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_MINMAX_HPP_INCLUDED
