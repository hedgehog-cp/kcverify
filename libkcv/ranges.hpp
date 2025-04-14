#ifndef KCVERIFY_RANGES_HPP_INCLUDED
#define KCVERIFY_RANGES_HPP_INCLUDED

#include <range/v3/view/concat.hpp>

namespace kcv {
namespace ranges {
namespace views {

/// @brief C++26 std::ranges::views::concatの代替.
using ::ranges::views::concat;

}  // namespace views
}  // namespace ranges

namespace views = ranges::views;

}  // namespace kcv

#endif  // KCVERIFY_RANGES_HPP_INCLUDED
