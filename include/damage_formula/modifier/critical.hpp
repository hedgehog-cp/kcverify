#ifndef KCVERIFY_DAMAGE_FORMULA_MODIFIER_CRITICAL_HPP_INCLUDED
#define KCVERIFY_DAMAGE_FORMULA_MODIFIER_CRITICAL_HPP_INCLUDED

namespace kcv {
namespace mod {

/// @brief 急所補正逆関数.
struct critical_inverse final {
    const bool is_critical;

    constexpr auto operator()(const auto& x) const {
        return this->is_critical ? x / 1.5 : x;
    }
};

/// @brief 急所補正関数.
struct critical final {
    const bool is_critical;

    constexpr auto operator()(const auto& x) const {
        return this->is_critical ? x * 1.5 : x;
    }

    constexpr auto operator^(int) const noexcept -> critical_inverse {
        return critical_inverse{this->is_critical};
    }
};

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_DAMAGE_FORMULA_MODIFIER_CRITICAL_HPP_INCLUDED
