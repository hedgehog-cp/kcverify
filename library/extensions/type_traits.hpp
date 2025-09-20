#ifndef KCVERIFY_EXTENSIONS_TYPE_TRAITS_HPP_INCLUDED
#define KCVERIFY_EXTENSIONS_TYPE_TRAITS_HPP_INCLUDED

#include <expected>
#include <optional>

namespace kcv {

/// @brief 型がexpectedであるかを検証する.
template <typename T>
inline constexpr bool is_expected_v = false;

/// @brief 型がexpectedであるかを検証する.
template <typename T, typename E>
inline constexpr bool is_expected_v<std::expected<T, E>> = true;

/// @brief 型がoptionalであるかを検証する.
template <typename T>
inline constexpr bool is_optional_v = false;

/// @brief 型がoptionalであるかを検証する.
template <typename T>
inline constexpr bool is_optional_v<std::optional<T>> = true;

}  // namespace kcv

#endif  // KCVERIFY_EXTENSIONS_TYPE_TRAITS_HPP_INCLUDED
