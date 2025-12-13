#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_COMPOSABLE_FWD_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_COMPOSABLE_FWD_HPP_INCLUDED

#include <concepts>
#include <type_traits>

namespace kcv {
namespace functions {

/// @brief operator|による関数の合成を提供する. CRTP.
/// @note operator|の実装がcomposed_functionに依存するため前方宣言する.
template <typename F>
    requires std::is_class_v<F> and std::same_as<F, std::remove_cv_t<F>>
class composable;

}  // namespace functions
}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_COMPOSABLE_FWD_HPP_INCLUDED
