#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_MODIFIER_FUNCTIONS_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_MODIFIER_FUNCTIONS_HPP_INCLUDED

// std
#include <optional>

// kcv
#include "core/damage_formula/functions/composable.hpp"
#include "core/damage_formula/functions/interval.hpp"

namespace kcv {

/// @brief 線形補正逆関数.
struct liner_inverse_fn final {
    using composable_concept = kcv::compose_tag;

    /// @brief 乗算補正値.
    kcv::interval a = kcv::interval{1.0};

    /// @brief 加算補正値.
    kcv::interval b = kcv::interval{0.0};

    /// @brief 線形補正逆関数を適用する.
    auto operator()(const auto& x) const noexcept -> std::optional<kcv::interval> {
        if (kcv::is_zero(a)) {
            return std::nullopt;
        }

        if (kcv::is_positive(a)) {
            return (x - b) / a;
        }

        return std::nullopt;
    }
};

/// @brief 線形補正関数.
struct liner_fn final {
    using composable_concept = kcv::compose_tag;

    /// @brief 乗算補正値.
    kcv::number a = kcv::number{1.0};

    /// @brief 加算補正値.
    kcv::number b = kcv::number{0.0};

    /// @brief 線形補正関数を適用する.
    auto operator()(const auto& x) const noexcept -> kcv::number {
        return x * a + b;
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> kcv::liner_inverse_fn {
        return liner_inverse_fn{
            .a = kcv::make_interval(a),
            .b = kcv::make_interval(b),
        };
    }
};

/// @brief 砲撃戦.航空攻撃補正逆関数.
struct air_attack_inverse_fn final {
    using composable_concept = kcv::compose_tag;

    /// @brief 砲撃戦.航空攻撃であるか.
    bool is_air_attack;

    /// @brief 砲撃戦.航空攻撃補正逆関数を適用する.
    auto operator()(const kcv::interval& x) const noexcept -> kcv::interval {
        return is_air_attack ? (x - 25.0) / 1.5 - 15.0 : x;
    }
};

/// @brief 砲撃戦.航空攻撃補正関数.
struct air_attack_fn final {
    using composable_concept = kcv::compose_tag;

    /// @brief 砲撃戦.航空攻撃であるか.
    bool is_air_attack;

    /// @brief 砲撃戦.航空攻撃補正関数を適用する.
    auto operator()(const kcv::number& x) const noexcept -> kcv::number {
        return is_air_attack ? (x + 15.0) * 1.5 + 25.0 : x;
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> air_attack_inverse_fn {
        return air_attack_inverse_fn{.is_air_attack = is_air_attack};
    }
};

/// @brief 床逆関数.
struct floor_inverse_fn final {
    using composable_concept = kcv::compose_tag;

    /// @brief 床逆関数を適当する.
    static auto operator()(const kcv::interval& x) noexcept -> kcv::interval {
        return kcv::interval{
            std::ceil(x.lower()),
            std::ceil(x.upper()) + 1,
        };
    }
};

/// @brief 床関数.
struct floor_fn final {
    using composable_concept = kcv::compose_tag;

    /// @brief 床関数を適用する.
    static auto operator()(const kcv::number& x) noexcept -> kcv::number {
        return kcv::number{
            std::floor(x.lower()),
            std::floor(x.upper()),
        };
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> floor_inverse_fn {
        return floor_inverse_fn{};
    }
};

/// @brief 条件付き床逆関数.
struct floor_if_inverse_fn final {
    using composable_concept = kcv::compose_tag;

    /// @brief 床関数を適用するか.
    bool is_flooring;

    /// @brief 条件付き床逆関数を適用する.
    auto operator()(const kcv::interval& x) const noexcept -> kcv::interval {
        return is_flooring ? kcv::floor_inverse_fn{}(x) : x;
    }
};

/// @brief 条件付き床関数.
struct floor_if_fn final {
    using composable_concept = kcv::compose_tag;

    /// @brief 床関数を適用するか.
    bool is_flooring;

    /// @brief 条件付き床関数を適用する.
    auto operator()(const kcv::number& x) const noexcept -> kcv::number {
        return is_flooring ? kcv::floor_fn{}(x) : x;
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> floor_if_inverse_fn {
        return floor_if_inverse_fn{.is_flooring = is_flooring};
    }
};

/// @brief ソフトキャップ補正逆関数.
struct softcap_inverse_fn final {
    using composable_concept = kcv::compose_tag;

    /// @brief キャップ値.
    kcv::interval cap;

    /// @brief ソフトキャップ補正逆関数を適用する.
    auto operator()(const kcv::interval& x) const noexcept -> std::optional<kcv::interval> {
        if (kcv::is_negative(x)) {
            return std::nullopt;
        }

        return x < cap ? x : kcv::square(x - cap) + cap;
    }
};

/// @brief ソフトキャップ補正関数.
struct softcap_fn final {
    using composable_concept = kcv::compose_tag;

    /// @brief キャップ値.
    kcv::number cap;

    /// @brief ソフトキャップ補正関数を適用する.
    auto operator()(const kcv::number& precap) const noexcept -> kcv::number {
        return kcv::min(precap, cap) + kcv::sqrt(kcv::max(precap - cap, kcv::number{0.0}));
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> softcap_inverse_fn {
        return softcap_inverse_fn{
            .cap = kcv::make_interval(cap),
        };
    }
};

/// @brief PT小鬼群補正逆関数.
struct pt_inverse_fn final {
    using composable_concept = kcv::compose_tag;

    static auto operator()(const kcv::interval& x) noexcept -> std::optional<kcv::interval> {
        const auto a = 6.0 * x - 55.0;
        if (kcv::is_negative(a)) {
            return std::nullopt;
        }

        const auto b = -3.0 * x + kcv::sqrt(kcv::interval{5.0}) * kcv::sqrt(a) + 25.0;
        if (kcv::is_zero(b)) {
            return std::nullopt;
        }

        return -10.0 / 9.0 * b;
    }
};

/// @brief PT小鬼群補正関数.
struct pt_fn final {
    using composable_concept = kcv::compose_tag;

    /// @brief PT小鬼群補正関数を適用する.
    static auto operator()(const kcv::number& x) noexcept -> std::optional<kcv::number> {
        if (kcv::is_negative(x)) {
            return std::nullopt;
        }

        return 0.3 * x + kcv::sqrt(x) + 10.0;
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> pt_inverse_fn {
        return pt_inverse_fn{};
    }
};

/// @brief 急所補正逆関数.
struct critical_inverse_fn final {
    using composable_concept = kcv::compose_tag;

    /// @brief 急所攻撃であるか.
    bool is_critical;

    /// @brief 急所補正逆関数を適用する.
    auto operator()(const kcv::interval& x) const noexcept -> kcv::interval {
        return is_critical ? x / 1.5 : x;
    }
};

/// @brief 急所補正関数.
struct critical_fn final {
    using composable_concept = kcv::compose_tag;

    /// @brief 急所攻撃であるか.
    bool is_critical;

    /// @brief 急所補正関数を適用する.
    auto operator()(const kcv::number& x) const noexcept -> kcv::number {
        return is_critical ? x * 1.5 : x;
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> critical_inverse_fn {
        return critical_inverse_fn{.is_critical = is_critical};
    }
};

}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_MODIFIER_FUNCTIONS_HPP_INCLUDED
