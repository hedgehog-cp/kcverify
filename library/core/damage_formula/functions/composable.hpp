#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_COMPOSABLE_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_COMPOSABLE_HPP_INCLUDED

// std
#include <concepts>
#include <type_traits>

// kcv
#include "core/damage_formula/functions/composable_fwd.hpp"
#include "core/damage_formula/functions/composed_function.hpp"

namespace kcv {
namespace functions {

/// @brief operator|による関数の合成を提供する. CRTP.
template <typename F>
    requires std::is_class_v<F> and std::same_as<F, std::remove_cv_t<F>>
class composable {
    template <typename G>
        requires std::derived_from<G, composable<G>>
    friend constexpr auto operator|(const G& g, const F& f) {
        if constexpr (kcv::functions::is_composed_function_v<G>) {
            if constexpr (kcv::functions::is_composed_function_v<F>) {
                return kcv::functions::composed_function{std::tuple_cat(g.decompose(), f.decompose())};
            } else {
                return kcv::functions::composed_function{std::tuple_cat(g.decompose(), std::make_tuple(f))};
            }
        } else {
            if constexpr (kcv::functions::is_composed_function_v<F>) {
                return kcv::functions::composed_function{std::tuple_cat(std::make_tuple(g), f.decompose())};
            } else {
                return kcv::functions::composed_function{g, f};
            }
        }
    }
};

}  // namespace functions
}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_COMPOSABLE_HPP_INCLUDED
