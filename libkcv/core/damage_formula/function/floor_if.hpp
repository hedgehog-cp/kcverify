#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_FLOOR_IF_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_FLOOR_IF_HPP_INCLUDED

#include "core/damage_formula/function/floor.hpp"
#include "core/interval.hpp"

namespace kcv {
namespace mod {

/// @brief 条件付き床逆関数.
struct floor_if_inverse final {
    /// @brief 条件付き床逆関数を適用する.
    auto operator()(const kcv::interval& x) const noexcept -> kcv::interval {
        return is_flooring ? kcv::mod::floor_inverse{}(x) : x;
    }

    /// @brief 床関数を適用するか.
    bool is_flooring;
};

/// @brief 条件付き床関数.
struct floor_if final {
    /// @brief 条件付き床関数を適用する.
    auto operator()(const kcv::number& x) const noexcept -> kcv::number {
        return is_flooring ? kcv::mod::floor{}(x) : x;
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> floor_if_inverse {
        return floor_if_inverse{.is_flooring = is_flooring};
    }

    /// @brief 床関数を適用するか.
    bool is_flooring;
};

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_FLOOR_IF_HPP_INCLUDED
