#ifndef KCVERIFY_KCAPI_TYPES_API_MINMAX_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_MINMAX_HPP_INCLUDED

#include <cstddef>
#include <tuple>

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

using api_minmax = std::tuple<int, int>;

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_MINMAX_HPP_INCLUDED
