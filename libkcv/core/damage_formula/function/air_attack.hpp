#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_AIR_ATTACK_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_AIR_ATTACK_HPP_INCLUDED

#include "core/interval.hpp"

namespace kcv {
namespace mod {

/// @brief 砲撃戦.航空攻撃補正逆関数.
struct air_attack_inverse final {
    /// @brief 砲撃戦.航空攻撃補正逆関数を適用する.
    auto operator()(const kcv::interval& x) const noexcept -> kcv::interval {
        return is_air_attack ? (x - 25.0) / 1.5 - 15.0 : x;
    }

    /// @brief 砲撃戦.航空攻撃であるか.
    bool is_air_attack;
};

/// @brief 砲撃戦.航空攻撃補正関数.
struct air_attack final {
    /// @brief 砲撃戦.航空攻撃補正関数を適用する.
    auto operator()(const kcv::number& x) const noexcept -> kcv::number {
        return is_air_attack ? (x + 15.0) * 1.5 + 25.0 : x;
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> air_attack_inverse {
        return air_attack_inverse{is_air_attack};
    }

    /// @brief 砲撃戦.航空攻撃であるか.
    bool is_air_attack;
};

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_AIR_ATTACK_HPP_INCLUDED
