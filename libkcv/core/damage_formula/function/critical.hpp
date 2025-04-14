#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_CRITICAL_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_CRITICAL_HPP_INCLUDED

#include "core/interval.hpp"

namespace kcv {
namespace mod {

/// @brief 急所補正逆関数.
struct critical_inverse final {
    /// @brief 急所補正逆関数を適用する.
    auto operator()(const kcv::interval& x) const noexcept -> kcv::interval {
        return is_critical ? x / 1.5 : x;
    }

    /// @brief 急所攻撃であるか.
    bool is_critical;
};

/// @brief 急所補正関数.
struct critical final {
    /// @brief 急所補正関数を適用する.
    auto operator()(const kcv::number& x) const noexcept -> kcv::number {
        return is_critical ? x * 1.5 : x;
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> critical_inverse {
        return critical_inverse{.is_critical = is_critical};
    }

    /// @brief 急所攻撃であるか.
    bool is_critical;
};

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_CRITICAL_HPP_INCLUDED
