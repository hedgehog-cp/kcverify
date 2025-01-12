#ifndef KCVERIFY_RANGES_HPP_INCLUDED
#define KCVERIFY_RANGES_HPP_INCLUDED

/**
 * @file ranges.hpp
 * @brief 標準ヘッダ<ranges>の拡張.
 */
#include <ranges>

// std
#include <concepts>

// range-v3
#include <range/v3/view/concat.hpp>

namespace kcv {

namespace ranges {

/// @brief 要素型がValueである範囲Rangeを表すコンセプト.
/// @tparam Range 範囲
/// @tparam Value 範囲の要素型
/// @see https://github.com/cplusplus/papers/issues/735
/// @see https://onihusube.hatenablog.com/entry/2022/10/09/021557#P1985R3-Universal-template-parameters
/// @see https://stackoverflow.com/questions/65894358/how-to-concisely-express-the-c20-concept-of-range-containing-t-typed-values
/// @note 標準入りするまで代替として利用する.
template <typename Range, typename Value>
concept range_of = std::ranges::range<Range> and std::same_as<Value, std::ranges::range_value_t<Range>>;

/// @brief 要素型がValueであるビューViewを表すコンセプト.
/// @tparam View ビュー
/// @tparam Value ビューの要素型
/// @note 標準入りするまで代替として利用する.
template <typename View, typename Value>
concept view_of = std::ranges::view<View> and std::same_as<Value, std::ranges::range_value_t<View>>;

namespace views {

/// @note C++26のstd::ranges::views::concatの代替として, range-v3を使って実装.
inline constexpr auto concat = ::ranges::views::concat;

}  // namespace views

}  // namespace ranges

namespace views = kcv::ranges::views;

}  // namespace kcv

#endif  // KCVERIFY_RANGES_HPP_INCLUDED
