#ifndef KCVERIFY_TYPE_TRAITS_HPP_INCLUDED
#define KCVERIFY_TYPE_TRAITS_HPP_INCLUDED

/**
 * @file type_traits.hpp
 * @brief 標準ヘッダ<type_traits>の拡張.
 */
#include <type_traits>

// std
#include <optional>

// kcv
#include "numeric.hpp"

namespace kcv {

/// @brief Tがstd::optionalでなければ, std::false_typeから派生する.
template <typename T>
struct is_optional : std::false_type {};

/// @brief Tがstd::optionalならば, std::true_typeから派生する.
template <typename T>
struct is_optional<std::optional<T>> : std::true_type {};

/// @brief Tがstd::optionalならば, true.
/// @note 必要に応じて呼び出し元でstd::remove_cvref_tなどをすること.
/// あとで `inline constexpr bool is_optional_v = is_optional<std::remove_cv_t<T>>::value;` とかにするかも.
template <typename T>
inline constexpr bool is_optional_v = is_optional<T>::value;

}  // namespace kcv

namespace kcv {

/// @brief Tが機械区間でなければ, std::false_typeから派生する.
template <typename T>
struct is_interval : std::false_type {};

/// @brief Tが機械区間ならば, std::true_typeから派生する.
template <typename T>
struct is_interval<boost::numeric::interval<T>> : std::true_type {};

/// @brief Tが機械区間ならば, true.
template <typename T>
inline constexpr bool is_interval_v = is_interval<T>::value;

}  // namespace kcv

#endif  // KCVERIFY_TYPE_TRAITS_HPP_INCLUDED
