#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_FLOOR_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_FLOOR_HPP_INCLUDED

// std
#include <cmath>

// kcv
#include "core/interval.hpp"

namespace kcv {
namespace mod {

/// @brief 床逆関数.
struct floor_inverse final {
    /// @brief 床逆関数を適当する.
    static auto operator()(const kcv::interval& x) noexcept -> kcv::interval {
        return kcv::interval{
            std::ceil(x.lower()),
            std::ceil(x.upper()) + 1,
        };
    }
};

/// @brief 床関数.
struct floor final {
    /// @brief 床関数を適用する.
    static auto operator()(const kcv::number& x) noexcept -> kcv::number {
        return kcv::number{
            std::floor(x.lower()),
            std::floor(x.upper()),
        };
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> floor_inverse {
        return floor_inverse{};
    }
};

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_FLOOR_HPP_INCLUDED
