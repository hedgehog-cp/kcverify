#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_INVERSE_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_INVERSE_HPP_INCLUDED

// std
#include <cstddef>
#include <optional>
#include <tuple>
#include <utility>

// kcv
#include "core/damage_formula/functions/function_composition.hpp"
#include "core/damage_formula/functions/modifier_functions.hpp"
#include "extensions/interval.hpp"
#include "extensions/type_traits.hpp"

namespace kcv {

template <typename T>
struct inverse_result final {};

template <typename T, typename U, typename F>
auto solve(const T&, const U& minmax, const F&) -> std::optional<inverse_result<F>> {
    if constexpr (kcv::is_optional_v<T>) {
        return std::nullopt;
    }

    if constexpr (kcv::is_optional_v<U>) {
        if (minmax.has_value()) {
            return inverse_result<F>{};
        } else {
            return std::nullopt;
        }
    }

    return inverse_result<F>{};
}

template <>
struct inverse_result<kcv::liner_fn> final {
    std::optional<kcv::interval> a;
    std::optional<kcv::interval> b;
};

template <typename T, typename U>
auto solve(const T& x, const U& minmax, const kcv::liner_fn& f) -> std::optional<inverse_result<kcv::liner_fn>> {
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
            return inverse_result<kcv::liner_fn>{a, b};
        }
    }
}

struct inverse_fn final {
    template <typename T, typename U, typename... Fs>
    static constexpr auto operator()(T x, U minmax, const kcv::function_composition<Fs...>& f) {
        return inverse(x, minmax, f);
    }

   private:
    template <typename T, typename U, typename... Fs>
    static constexpr auto inverse(T x, U minmax, const kcv::function_composition<Fs...>& f) {
        return inverse_impl_1(x, minmax, f.decompose(), std::make_index_sequence<sizeof...(Fs)>{});
    }

    template <typename T, typename U, typename... Fs, std::size_t... I>
    static constexpr auto inverse_impl_1(T x, U minmax, const std::tuple<Fs...>& fs, std::index_sequence<I...>) {
        return inverse_impl_2(x, minmax, std::get<I>(fs)...);
    }

    template <typename T, typename U, typename F, typename... Fs>
    static constexpr auto inverse_impl_2(T x, U minmax, const F& f, const Fs&... fs) {
        const auto inv = kcv::function_composition{fs...} ^ -1;
        const auto y   = kcv::invoke(inv, minmax);
        return std::tuple_cat(inverse_impl_2(f(x), minmax, fs...), std::make_tuple(solve(x, y, f)));
    }

    template <typename T, typename U>
    static constexpr auto inverse_impl_2(T, U) {
        return std::make_tuple(std::ignore);
    }

} inline constexpr inverse{};

}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_INVERSE_HPP_INCLUDED
