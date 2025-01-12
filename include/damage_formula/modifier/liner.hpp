#ifndef KCVERIFY_DAMAGE_FORMULA_MODIFIER_LINER_HPP_INCLUDED
#define KCVERIFY_DAMAGE_FORMULA_MODIFIER_LINER_HPP_INCLUDED

#include <optional>

namespace kcv {
namespace mod {

/// @brief 線形補正逆関数.
/// @tparam T 浮動小数点数または機械区間.
template <typename T>
struct liner_inverse final {
    const T a = 1.0;
    const T b = 0.0;

    constexpr auto operator()(const auto& x) const -> std::optional<decltype((x - b) / a)> {
        if (a >= 0 and a <= 0) return std::nullopt;
        return (x - b) / a;
    }
};

/// @brief 線形補正関数.
/// @tparam T 浮動小数点数または機械区間.
template <typename T>
struct liner final {
    const T a = 1.0;
    const T b = 0.0;

    constexpr auto operator()(const auto& x) const {
        return x * a + b;
    }

    constexpr auto operator^(int) const noexcept -> liner_inverse<T> {
        return liner_inverse<T>{a, b};
    }
};

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_DAMAGE_FORMULA_MODIFIER_LINER_HPP_INCLUDED
