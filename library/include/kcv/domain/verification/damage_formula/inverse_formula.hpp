#ifndef KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_INVERSE_FORMULA_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_INVERSE_FORMULA_HPP_INCLUDED

// std
#include <cstddef>
#include <cstdint>
#include <optional>
#include <tuple>
#include <type_traits>
#include <utility>

//kcv
#include "kcv/core/numeric/composed_function.hpp"
#include "kcv/core/numeric/interval.hpp"
#include "kcv/domain/verification/damage_formula/damage_formula.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"
#include "kcv/std_ext/functional.hpp"
#include "kcv/std_ext/utility.hpp"

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
auto inverse_formula(const auto& x, const auto& minmax, const kcv::functions::composed_function<Fs...>& fs) {
    // clang-format off

    return []<std::size_t... I>(const auto& x, const auto& minmax, const std::tuple<Fs...>& fs, std::index_sequence<I...>) {
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

    // clang-format on
}

/// @brief 攻撃力式の各補正値を逆算する.
inline auto inverse_attack_power_formula(std::int32_t observed_damage, const kcv::damage_formula& damage_formula) {
    const auto damage        = (damage_formula.modifier_function() ^ -1)(observed_damage);
    const auto defence_power = damage_formula.defence_power();
    const auto attack_power  = damage.has_value() and defence_power.has_value()
                                 ? std::make_optional(*damage + kcv::make_interval(*defence_power))
                                 : std::nullopt;
    const auto x             = damage_formula.attack_power_formula().base_value();
    return inverse_formula(x, attack_power, damage_formula.attack_power_formula().modifier_function());
}

/// @brief 攻撃力式の逆算結果の型.
using inverse_attack_formula_result_t
    = std::invoke_result_t<decltype(inverse_attack_power_formula), std::int32_t, const kcv::damage_formula&>;

/// @brief 防御力式の各補正値を逆算する.
inline auto inverse_defence_power_formula(std::int32_t observed_damage, const kcv::damage_formula& damage_formula) {
    const auto damage        = (damage_formula.modifier_function() ^ -1)(observed_damage);
    const auto attack_power  = damage_formula.attack_power_formula().evaluate();
    const auto defence_power = attack_power.has_value() and damage.has_value()
                                 ? std::make_optional(kcv::make_interval(*attack_power) - *damage)
                                 : std::nullopt;
    const auto x             = damage_formula.defence_power_formula().base_value();
    return inverse_formula(x, defence_power, damage_formula.defence_power_formula().modifier_function());
}

/// @brief 防御力式の逆算結果の型.
using inverse_defence_formula_result_t
    = std::invoke_result_t<decltype(inverse_defence_power_formula), std::int32_t, const kcv::damage_formula&>;

}  // namespace kcv

#endif  // KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_INVERSE_FORMULA_HPP_INCLUDED
