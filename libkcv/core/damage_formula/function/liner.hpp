#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_LINER_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_LINER_HPP_INCLUDED

// std
#include <optional>

// kcv
#include "core/interval.hpp"

namespace kcv {
namespace mod {

/// @brief 線形補正逆関数.
/// inv(x) = (x - b) / a, a > 0.
struct liner_inverse final {
    /// @brief 線形補正逆関数を適用する.
    auto operator()(const kcv::interval& x) const noexcept -> std::optional<kcv::interval> {
        if (kcv::is_zero(a)) {
            return std::nullopt;
        }

        if (kcv::is_positive(a)) {
            return (x - b) / a;
        }

        return std::nullopt;
    }

    /// @brief 乗算補正値.
    kcv::interval a = 1.0;

    /// @brief 加算補正値.
    kcv::interval b = 0.0;
};

/// @brief 線形補正関数.
/// func(x) = x * a + b, a > 0.
struct liner final {
    /// @brief 線形補正関数を適用する.
    auto operator()(const kcv::number& x) const noexcept -> kcv::number {
        return x * a + b;
    }

    /// @brief 逆関数を返す.
    /// @example func ^ -1;
    auto operator^(int) const noexcept -> liner_inverse {
        return liner_inverse{
            .a = kcv::make_interval(a),
            .b = kcv::make_interval(b),
        };
    }

    /// @brief 乗算補正値.
    kcv::number a = 1.0;

    /// @brief 加算補正値.
    kcv::number b = 0.0;
};

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_LINER_HPP_INCLUDED
