#ifndef KCVERIFY_DAMAGE_FORMULA_MODIFIER_FLOOR_IF_HPP_INCLUDED
#define KCVERIFY_DAMAGE_FORMULA_MODIFIER_FLOOR_IF_HPP_INCLUDED

// std
#include <cmath>

// kcv
#include "damage_formula/modifier/floor.hpp"
#include "numeric.hpp"

namespace kcv {
namespace mod {

/// @brief 条件付き床逆関数.
/// @note 全単射しないため数学的には定義できない.
struct floor_inverse_if final {
    const bool condition;

    /// @note T = kcv::float64_t かつ not this->condition のとき,
    /// doubleを返してもよいが難しそうなのでとりあえず全部 kcv::interval で返す.
    auto operator()(const auto& x) const -> interval {
        if (this->condition) {
            return kcv::mod::floor_inverse{}(x);
        }

        return x;
    }
};

/// @brief 条件付き床関数.
struct floor_if final {
    const bool condition;

    constexpr auto operator()(const auto& x) const {
        if (this->condition) {
            return kcv::mod::floor{}(x);
        }

        return x;
    }

    constexpr auto operator^(int) const noexcept -> floor_inverse_if {
        return floor_inverse_if{this->condition};
    }
};

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_DAMAGE_FORMULA_MODIFIER_FLOOR_IF_HPP_INCLUDED
