#ifndef KCVERIFY_EXTENSIONS_META_HPP_INCLUDED
#define KCVERIFY_EXTENSIONS_META_HPP_INCLUDED

#include <cstddef>
#include <tuple>
#include <type_traits>

namespace kcv {
namespace meta {

/// @brief どのような型にも暗黙変換可能な型.
/// @note utility.hppへの移動を検討.
struct any_castable final {
    /// @brief 実際に評価されないため実装不要.
    template <typename T>
    consteval operator T() const;
};

/// @brief 集成体のメンバの個数を数え上げてこれを返す. その実装詳細.
template <typename T, typename... Args>
consteval auto count_members_impl() noexcept -> std::size_t {
    if constexpr (requires { typename std::remove_cvref_t<T>{Args{}..., any_castable{}}; }) {
        return count_members_impl<T, Args..., any_castable>();
    } else {
        return sizeof...(Args);
    }
}

/// @brief 集成体のメンバの個数を数え上げてこれを返す.
template <typename T, typename... Args>
    requires std::is_aggregate_v<std::remove_cvref_t<T>>
consteval auto count_members() noexcept -> std::size_t {
    return count_members_impl<T>();
}

/// @brief 集成体をstd::tupleに変換する.
template <typename T, size_t N = count_members<T>()>
constexpr auto to_tuple(const T& aggregate) noexcept {
    if constexpr (N == 0) {
        return std::tuple<>{};
    } else if constexpr (N == 1) {
        const auto& [v0] = aggregate;
        return std::tie(v0);
    } else if constexpr (N == 2) {
        const auto& [v0, v1] = aggregate;
        return std::tie(v0, v1);
    } else if constexpr (N == 3) {
        const auto& [v0, v1, v2] = aggregate;
        return std::tie(v0, v1, v2);
    } else if constexpr (N == 4) {
        const auto& [v0, v1, v2, v3] = aggregate;
        return std::tie(v0, v1, v2, v3);
    } else if constexpr (N == 5) {
        const auto& [v0, v1, v2, v3, v4] = aggregate;
        return std::tie(v0, v1, v2, v3, v4);
    } else if constexpr (N == 6) {
        const auto& [v0, v1, v2, v3, v4, v5] = aggregate;
        return std::tie(v0, v1, v2, v3, v4, v5);
    } else if constexpr (N == 7) {
        const auto& [v0, v1, v2, v3, v4, v5, v6] = aggregate;
        return std::tie(v0, v1, v2, v3, v4, v5, v6);
    } else if constexpr (N == 8) {
        const auto& [v0, v1, v2, v3, v4, v5, v6, v7] = aggregate;
        return std::tie(v0, v1, v2, v3, v4, v5, v6, v7);
    } else if constexpr (N == 9) {
        const auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8] = aggregate;
        return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8);
    } else if constexpr (N == 10) {
        const auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9] = aggregate;
        return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
    } else if constexpr (N == 11) {
        const auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10] = aggregate;
        return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
    } else if constexpr (N == 12) {
        const auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11] = aggregate;
        return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
    } else {
        static_assert(N <= 12, "support only up to 12 members in this function.");
    }
}

}  // namespace meta
}  // namespace kcv

#endif  // KCVERIFY_EXTENSIONS_META_HPP_INCLUDED
