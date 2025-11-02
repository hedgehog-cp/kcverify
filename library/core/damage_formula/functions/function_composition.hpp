#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_FUNCTION_COMPOSITION_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_FUNCTION_COMPOSITION_HPP_INCLUDED

// std
#include <cstddef>
#include <tuple>
#include <utility>

// kcv
#include "core/damage_formula/functions/composable.hpp"
#include "extensions/functional.hpp"

namespace kcv {
namespace functions {

/// @brief 合成関数.
template <kcv::functions::composable... Funcs>
class function_composition final {
    /// @brief 合成関数を左畳み込みで適用する, その実装詳細.
    struct apply_fn final {
        /// @brief 合成関数を適用する.
        template <typename T, typename... Fs>
        static constexpr auto operator()(const T& x, const std::tuple<Fs...>& fs) {
            return fold_left(x, fs);
        }

       private:
        template <typename T, typename... Fs>
        static constexpr auto fold_left(const T& x, const std::tuple<Fs...>& fs) {
            return fold_left_impl_1(x, fs, std::make_index_sequence<sizeof...(Fs)>{});
        }

        template <typename T, typename... Fs, std::size_t... I>
        static constexpr auto fold_left_impl_1(const T& x, const std::tuple<Fs...>& fs, std::index_sequence<I...>) {
            return fold_left_impl_2(x, std::get<I>(fs)...);
        }

        template <typename T, typename F, typename... Fs>
        static constexpr auto fold_left_impl_2(const T& x, const F& f, const Fs&... fs) {
            return fold_left_impl_2(kcv::invoke(f, x), fs...);
        }

        template <typename T>
        static constexpr auto fold_left_impl_2(T&& x) noexcept -> decltype(auto) {
            return std::forward<T>(x);
        }
    } static constexpr apply{};

    /// @brief 合成関数に対する逆関数を返す, その実装詳細.
    struct inverse_fn final {
        template <typename... Fs>
        static constexpr auto operator()(const std::tuple<Fs...>& fs) {
            return inverse(fs);
        }

       private:
        template <typename... Fs>
        static constexpr auto inverse(const std::tuple<Fs...>& fs) {
            return inverse_impl_1(fs, std::make_index_sequence<sizeof...(Fs)>{});
        }

        template <typename... Fs, std::size_t... I>
        static constexpr auto inverse_impl_1(const std::tuple<Fs...>& fs, std::index_sequence<I...>) {
            // 型を明示しなければFuncs...で構築しようとしてエラーとなる.
            return function_composition<decltype(std::get<sizeof...(I) - 1 - I>(fs) ^ -1)...>{
                (std::get<sizeof...(I) - 1 - I>(fs) ^ -1)...
            };
        }
    } static constexpr inverse{};

   public:
    using composable_concept = kcv::functions::compose_tag;

    /// @brief 合成関数を構築する.
    explicit constexpr function_composition(const Funcs&... fs)
        : fs_{fs...} {}

    /// @brief 合成関数を構築する.
    explicit constexpr function_composition(const std::tuple<Funcs...>& fs)
        : fs_{fs} {}

    /// @brief 合成関数を適用する.
    template <typename T>
    constexpr auto operator()(const T& x) const {
        return this->apply(x, this->fs_);
    }

    /// @brief 逆関数を返す.
    constexpr auto operator^(int) const {
        return this->inverse(this->fs_);
    }

    /// @brief 合成された関数を返す.
    constexpr auto decompose() const noexcept -> const std::tuple<Funcs...>& {
        return this->fs_;
    }

   private:
    std::tuple<Funcs...> fs_;
};

/// @brief 関数を合成する.
template <kcv::functions::composable F1, kcv::functions::composable F2>
constexpr auto operator|(const F1& f1, const F2& f2) {
    return function_composition<F1, F2>{f1, f2};
}

/// @brief 関数を合成する.
template <kcv::functions::composable... Fs1, kcv::functions::composable... Fs2>
constexpr auto operator|(const function_composition<Fs1...>& lhs, const function_composition<Fs2...>& rhs) {
    return function_composition<Fs1..., Fs2...>{std::tuple_cat(lhs.decompose(), rhs.decompose())};
}

/// @brief 関数を合成する.
template <kcv::functions::composable... Fs1, kcv::functions::composable F2>
constexpr auto operator|(const function_composition<Fs1...>& lhs, const F2& rhs) {
    return function_composition<Fs1..., F2>{std::tuple_cat(lhs.decompose(), std::make_tuple(rhs))};
}

/// @brief 関数を合成する.
template <kcv::functions::composable F, kcv::functions::composable... Fs2>
constexpr auto operator|(const F& lhs, const function_composition<Fs2...>& rhs) {
    return function_composition<F, Fs2...>{std::tuple_cat(std::make_tuple(lhs), rhs.decompose())};
}

}  // namespace functions
}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_FUNCTION_COMPOSITION_HPP_INCLUDED
