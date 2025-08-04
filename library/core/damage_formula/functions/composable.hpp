#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_COMPOSABLE_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_COMPOSABLE_HPP_INCLUDED

#include <concepts>

namespace kcv {

/// @brief 合成関数として合成可能な型を表すタグ型.
struct compose_tag final {};

/// @brief 合成関数として合成可能な型を表す.
/// @todo operator(), operator^などがあることを追加したい.
template <typename T>
concept composable = requires { requires std::same_as<typename T::composable_concept, compose_tag>; };

}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_COMPOSABLE_HPP_INCLUDED
