#ifndef KCVERIFY_DAMAGE_FORMULA_MODIFIER_FLOOR_HPP_INCLUDED
#define KCVERIFY_DAMAGE_FORMULA_MODIFIER_FLOOR_HPP_INCLUDED

// std
#include <cmath>
#include <type_traits>

// kcv
#include "numeric.hpp"

namespace kcv {
namespace mod {

/// @brief 床逆関数.
/// @note 全単射しないため数学的には定義できない.
struct floor_inverse final {
    template <typename T>
    static auto operator()(const T& x) -> kcv::interval {
        if constexpr (std::is_same_v<T, kcv::interval>) {
            return kcv::interval{std::ceil(x.lower()), std::ceil(x.upper()) + 1};
        } else {
            return kcv::interval{x, x + 1};
        }
    }
};

/// @brief 床関数.
struct floor final {
    template <typename T>
    static constexpr auto operator()(const T& x) -> T {
        if constexpr (std::is_same_v<T, kcv::interval>) {
            return T{std::floor(x.lower()), std::floor(x.upper())};
        } else {
            return std::floor(x);
        }
    }

    constexpr auto operator^(int) const noexcept -> floor_inverse {
        return floor_inverse{};
    }
};

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_DAMAGE_FORMULA_MODIFIER_FLOOR_HPP_INCLUDED
