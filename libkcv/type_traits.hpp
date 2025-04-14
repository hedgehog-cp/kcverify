#ifndef KCVERIFY_TYPE_TRAITS_HPP_INCLUDED
#define KCVERIFY_TYPE_TRAITS_HPP_INCLUDED

/// @note 将来の標準に提案されていないため, std_alt配下に配置しない.

// MARK: optional

#include <optional>

namespace kcv {

/// @brief 型がoptionalであるかを検証する.
template <typename T>
inline constexpr bool is_optional_v = false;

/// @brief 型がoptionalであるかを検証する.
template <typename T>
inline constexpr bool is_optional_v<std::optional<T>> = true;

}  // namespace kcv

// MARK: expected

#include <expected>

namespace kcv {

/// @brief 型がexpectedであるかを検証する.
template <typename T>
inline constexpr bool is_expected_v = false;

/// @brief 型がexpectedであるかを検証する.
template <typename T, typename E>
inline constexpr bool is_expected_v<std::expected<T, E>> = true;

}  // namespace kcv

#endif  // KCVERIFY_TYPE_TRAITS_HPP_INCLUDED
