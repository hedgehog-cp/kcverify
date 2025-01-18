#ifndef KCVERIFY_DAMAGE_FORMULA_MODIFIER_AIR_ATTACK_HPP_INCLUDED
#define KCVERIFY_DAMAGE_FORMULA_MODIFIER_AIR_ATTACK_HPP_INCLUDED

namespace kcv {
namespace mod {

/// @brief 砲撃戦.航空攻撃補正逆関数.
struct air_attack_inverse final {
    const bool is_air_attack;

    constexpr auto operator()(const auto& x) const {
        return this->is_air_attack ? (x - 25.0) / 1.5 - 15.0 : x;
    }
};

/// @brief 砲撃戦.航空攻撃補正関数.
struct air_attack final {
    const bool is_air_attack;

    constexpr auto operator()(const auto& x) const {
        return this->is_air_attack ? (x + 15.0) * 1.5 + 25.0 : x;
    }

    constexpr auto operator^(int) const -> kcv::mod::air_attack_inverse {
        return kcv::mod::air_attack_inverse{this->is_air_attack};
    }
};

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_DAMAGE_FORMULA_MODIFIER_AIR_ATTACK_HPP_INCLUDED
