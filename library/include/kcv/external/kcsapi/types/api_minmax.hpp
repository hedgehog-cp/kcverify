#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_MINMAX_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_MINMAX_HPP_INCLUDED

#include <array>
#include <cstddef>
#include <cstdint>

namespace kcv {
namespace kcsapi {

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
using api_minmax = std::array<std::int32_t, 2>;

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_MINMAX_HPP_INCLUDED
