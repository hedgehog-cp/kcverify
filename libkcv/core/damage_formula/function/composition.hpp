#ifndef KCVERIFY_CORE_FUNCTION_COMPOSITION_HPP_INCLUDED
#define KCVERIFY_CORE_FUNCTION_COMPOSITION_HPP_INCLUDED

// std
#include <expected>
#include <optional>
#include <type_traits>
#include <utility>

// kcv
#include "type_traits.hpp"

namespace kcv {
namespace mod {

/// @brief 合成関数.
/// @tparam 関数1.
/// @tparam 関数2.
/// @note F1, F2ともに, operator()の引数がoptionalおよびexpectedであってはならない.
/// すなわち, auto f(const std::optional<T>& x); のようなシグネチャは受け入れない.
/// 関数呼び出しする前に処理すべきである.
template <typename F1, typename F2>
class composition final {
   public:
    constexpr composition(F1 f1, F2 f2)
        : f1_{std::move(f1)}
        , f2_{std::move(f2)} {}

    constexpr auto operator()(const auto &x) const {
        return this->invoke(this->f2_, this->invoke(this->f1_, x));
    }

    constexpr auto operator^(int) const noexcept {
        return (this->f2_ ^ -1) | (this->f1_ ^ -1);
    }

   private:
    template <typename F, typename T>
    static constexpr auto invoke(const F &f, const T &x) noexcept(noexcept(f(x))) {
        return f(x);
    }

    /// @brief エラー型を折り畳んで関数呼び出しを行う.
    /// 返り値の型がstd::optional<std::optional<T>>のようになるのを回避する.
    template <typename F, typename T>
    static constexpr auto invoke(const F &f, const std::optional<T> &x) {
        using result_t = std::invoke_result_t<F, const T &>;
        if constexpr (kcv::is_optional_v<result_t>) {
            return x.and_then(f);
        } else {
            return x.transform(f);
        }
    }

    /// @brief エラー型を折り畳んで関数呼び出しを行う.
    /// 返り値の型がstd::expected<std::expected<T, E>, E>のようになるのを回避する.
    template <typename F, typename T, typename E>
    static constexpr auto invoke(const F &f, const std::expected<T, E> &x) {
        using result_t = std::invoke_result_t<F, const T &>;
        if constexpr (kcv::is_expected_v<result_t>) {
            // この条件を明示せずともコンパイルエラーにできるが,
            // 書かなければ候補の関数を探索してエラーメッセージが長大になるだろう.
            if constexpr (std::same_as<typename result_t::error_type, E>) {
                return x.and_then(f);
            } else {
                static_assert(false, "two error_types are not the same.");
            }
        } else {
            return x.transform(f);
        }
    }

   private:
    F1 f1_;
    F2 f2_;
};

/// @brief 関数を合成する.
/// @tparam 関数1.
/// @tparam 関数2.
/// @note 関数ポインタ同士にoperator|を適用できないため, たとえばフリー関数のみからなる合成関数は作成できない.
/// @example auto y = (f1 | f2 | f3)(x);
/// @todo いい感じに制約する.
template <typename F1, typename F2>
constexpr auto operator|(const F1 &f1, const F2 &f2) -> composition<F1, F2> {
    return composition<F1, F2>{f1, f2};
}

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_CORE_FUNCTION_COMPOSITION_HPP_INCLUDED
