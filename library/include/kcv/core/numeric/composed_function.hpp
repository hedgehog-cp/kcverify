#ifndef KCV_CORE_NUMERIC_COMPOSED_FUNCTION_HPP_INCLUDED
#define KCV_CORE_NUMERIC_COMPOSED_FUNCTION_HPP_INCLUDED

// std
#include <concepts>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

// kcv
#include "kcv/std_ext/functional.hpp"
#include "kcv/std_ext/utility.hpp"

namespace kcv {
namespace functions {

/// @brief operator|による関数の合成を提供する. CRTP.
/// @note operator|の実装がcomposed_functionに依存するため前方宣言する.
template <typename F>
    requires std::is_class_v<F> and std::same_as<F, std::remove_cv_t<F>>
class composable;

/// @brief 合成関数. operator|でcomposableの型を合成できる.
template <typename... Fs>
    requires (... and std::derived_from<Fs, kcv::functions::composable<Fs>>)
class composed_function final : public kcv::functions::composable<composed_function<Fs...>> {
   public:
    explicit constexpr composed_function(const Fs&... fs)
        : fs_{fs...} {}

    explicit constexpr composed_function(const std::tuple<Fs...>& fs)
        : fs_{fs} {}

    /// @brief 合成関数を適用する.
    template <typename T>
    constexpr auto operator()(const T& x) const {
        return []<std::size_t... I>(const T& x, const std::tuple<Fs...>& fs, std::index_sequence<I...>) static {
            return kcv::overloaded{
                [](this const auto& self, const auto& x, const auto& f, const auto&... fs) {
                    return self(kcv::invoke(f, x), fs...);
                },
                [](const auto& x) static { return x; },
            }(x, std::get<I>(fs)...);
        }(x, this->fs_, std::index_sequence_for<Fs...>{});
    }

    /// @brief 合成関数の逆関数を返す.
    constexpr auto operator^(int) const {
        return []<std::size_t... I>(const std::tuple<Fs...>& fs, std::index_sequence<I...>) static {
            // 型を明示しなければFs...で構築しようとしてエラーとなる.
            return composed_function<decltype(std::get<sizeof...(I) - 1 - I>(fs) ^ -1)...>{
                (std::get<sizeof...(I) - 1 - I>(fs) ^ -1)...
            };
        }(this->fs_, std::index_sequence_for<Fs...>{});
    }

    /// @brief 合成関数をなす各関数を返す.
    constexpr auto decompose() const noexcept -> const std::tuple<Fs...>& {
        return this->fs_;
    }

   private:
    std::tuple<Fs...> fs_;
};

/// @brief 型がcomposed_functionであるかを検証する.
template <typename... Fs>
inline constexpr bool is_composed_function_v = false;

/// @brief 型がcomposed_functionであるかを検証する.
template <typename... Fs>
inline constexpr bool is_composed_function_v<composed_function<Fs...>> = true;

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

#endif  // KCV_CORE_NUMERIC_COMPOSED_FUNCTION_HPP_INCLUDED
