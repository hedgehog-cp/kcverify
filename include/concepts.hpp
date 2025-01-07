#ifndef KCVERIFY_CONCEPTS_HPP_INCLUDED
#define KCVERIFY_CONCEPTS_HPP_INCLUDED

#include <ranges>
#include <type_traits>

namespace kcv {
namespace ranges {

/// @brief 要素型がValueである範囲Rangeを表すコンセプト.
/// @tparam Range 範囲
/// @tparam Value 範囲の要素型
/// @see https://github.com/cplusplus/papers/issues/735
/// @see https://onihusube.hatenablog.com/entry/2022/10/09/021557#P1985R3-Universal-template-parameters
/// @see https://stackoverflow.com/questions/65894358/how-to-concisely-express-the-c20-concept-of-range-containing-t-typed-values
/// @note 標準入りするまで代替として利用する.
template <class Range, class Value>
concept range_of = std::ranges::range<Range> && std::is_same_v<Value, std::ranges::range_value_t<Range>>;

/// @brief 要素型がValueであるビューViewを表すコンセプト.
/// @tparam View ビュー
/// @tparam Value ビューの要素型
/// @note 標準入りするまで代替として利用する.
template <class View, class Value>
concept view_of = std::ranges::view<View> && std::is_same_v<Value, std::ranges::range_value_t<View>>;

}  // namespace ranges
}  // namespace kcv

#endif  // KCVERIFY_CONCEPTS_HPP_INCLUDED
