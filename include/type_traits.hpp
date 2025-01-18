#ifndef KCVERIFY_TYPE_TRAITS_HPP_INCLUDED
#define KCVERIFY_TYPE_TRAITS_HPP_INCLUDED

/**
 * @file type_traits.hpp
 * @brief 標準ヘッダ<type_traits>の拡張.
 */
#include <type_traits>

// std
#include <optional>

namespace kcv {

template <typename T>
inline constexpr bool is_optional_v = false;

template <typename T>
inline constexpr bool is_optional_v<std::optional<T>> = true;

}  // namespace kcv

#endif  // KCVERIFY_TYPE_TRAITS_HPP_INCLUDED
