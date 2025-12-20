#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_INVERSE_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_INVERSE_HPP_INCLUDED

// std
#include <cstddef>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utility>

//kcv
#include "core/damage_formula/damage_formula.hpp"
#include "core/damage_formula/functions/composed_function.hpp"
#include "core/damage_formula/functions/modifier_functions.hpp"
#include "extensions/functional.hpp"
#include "extensions/interval.hpp"
#include "extensions/utility.hpp"

namespace kcv {

/// @brief 補正関数Fの逆算結果.
template <typename F>
struct inverse_result final {};

template <>
struct inverse_result<kcv::functions::liner> final {
    std::optional<kcv::interval> a;
    std::optional<kcv::interval> b;
};

template <typename T, typename U, typename F>
auto solve(const T&, const U&, const F&) -> inverse_result<F> {
    return inverse_result<F>{};
}

template <typename T, typename U>
auto solve(const T& x, const U& minmax, const kcv::functions::liner& f)
    -> std::optional<inverse_result<kcv::functions::liner>> {
    if constexpr (kcv::is_optional_v<T>) {
        if (x.has_value()) {
            return solve(*x, minmax, f);
        } else {
            return std::nullopt;
        }
    } else {
        if constexpr (kcv::is_optional_v<U>) {
            if (minmax.has_value()) {
                return solve(x, *minmax, f);
            } else {
                return std::nullopt;
            }
        } else {
            const auto a = (minmax - kcv::make_interval(f.b)) / kcv::make_interval(x);
            const auto b = minmax - kcv::make_interval(x) * kcv::make_interval(f.a);
            return inverse_result<kcv::functions::liner>{a, b};
        }
    }
}

/// @brief 逆算をする.
/// min <= (fn ∘ ... ∘ f2 ∘ f1)(x) <= max に対して, fi(i=1,2,...,n)の上下をもとにfiの各パラメータが取り得る範囲を解く.
template <typename... Fs>
auto inverse(const auto& x, const auto& minmax, const kcv::functions::composed_function<Fs...>& fs) {
    return []<std::size_t... I>(const auto& x, const auto& minmax, std::tuple<Fs...>& fs, std::index_sequence<I...>) {
        return kcv::overloaded{
            [](this const auto& self, const auto& x, const auto& minmax, const auto& f, const auto&... fs) {
                const auto inv = kcv::functions::composed_function{fs...} ^ -1;
                const auto y   = kcv::invoke(inv, minmax);
                return std::tuple_cat(
                    std::make_tuple(solve(x, y, f)),        //
                    self(kcv::invoke(f, x), minmax, fs...)  //
                );
            },
            []([[maybe_unused]] const auto& x, [[maybe_unused]] const auto& minmax) static {
                return std::make_tuple(std::ignore);
            },
        }(x, minmax, std::get<I>(fs)...);
    }(x, minmax, fs.decompose(), std::index_sequence_for<Fs...>{});
}

/// @brief 攻撃力式の各補正値を逆算する.
template <typename AttackPowerFormula, typename DefencePowerFormula>
auto inverse_attack_power_formula(
    std::int32_t observed_damage,
    const kcv::damage_formula<AttackPowerFormula, DefencePowerFormula>& damage_formula
) {
    const auto damage        = (damage_formula.modifier_function() ^ -1)(observed_damage);
    const auto defence_power = damage_formula.defence_power_formula().evaluate();
    const auto attack_power  = damage + defence_power;
    const auto x             = damage_formula.attack_power_formula().base_value();
    return inverse(x, attack_power, damage_formula.attack_power_formula().modifier_function());
}

/// @brief 防御力式の各補正値を逆算する.
template <typename AttackPowerFormula, typename DefencePowerFormula>
auto inverse_defence_power_formula(
    std::int32_t observed_damage,
    const kcv::damage_formula<AttackPowerFormula, DefencePowerFormula>& damage_formula
) {
    const auto damage        = (damage_formula.modifier_function() ^ -1)(observed_damage);
    const auto attack_power  = damage_formula.attack_power_formula().evaluate();
    const auto defence_power = attack_power - damage;
    const auto x             = damage_formula.defence_power_formula().base_value();
    return inverse(x, defence_power, damage_formula.defence_power_formula().modifer_function());
}

}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_INVERSE_HPP_INCLUDED
