#ifndef KCVERIFY_DAMAGE_FORMULA_MODIFIER_COMPOSITION_HPP_INCLUDED
#define KCVERIFY_DAMAGE_FORMULA_MODIFIER_COMPOSITION_HPP_INCLUDED

#include "type_traits.hpp"

namespace kcv {
namespace mod {

/// @brief 関数合成のアダプタ. 直接利用しない.
/// @todo 合成できる関数を制限する.
template <typename F1, typename F2>
class composition_function_adapter final {
   public:
    constexpr composition_function_adapter(const F1& f1, const F2& f2) noexcept
        : f1_{f1}
        , f2_{f2} {}

    template <typename T>
    constexpr auto operator()(const T& x) const {
        return this->invoke(this->f2_, this->invoke(this->f1_, x));
    }

   private:
    /// @brief 関数を単純に呼び出すと, 引数や返り値の型がstd::optionalを含む場合に,
    /// std::optionalで多重にラップされた型 e.g. std::optional<std::optional<U>> を生成してしまう.
    /// この関数は, std::optionalを適切に処理し, 返り値の型をUまたはstd::optional<U>に整える.
    template <typename F, typename T>
    constexpr auto invoke(const F& f, const T& x) const {
        if constexpr (kcv::is_optional_v<T>) {
            if constexpr (kcv::is_optional_v<std::invoke_result_t<F, const typename T::value_type&>>) {
                return x.and_then(f);
            } else {
                return x.transform(f);
            }
        } else {
            return f(x);
        }
    }

   private:
    const F1& f1_;
    const F2& f2_;
};

/// @brief 関数の合成を表現する.
/// @note auto y = (f | y)(x);  // のように使う.
/// ただし, y = g(f(x)) = (g ∘ f)(x) = (f | g)(x).
/// (g | f)(x)と書く設計にしてもよいが, pipeを尊重して左から右に適用する.
/// ならば, x | f | g または (x | f | g)()ではないかとなるが, これでは関数オブジェクトとして扱いづらい.
/// @todo 合成できる関数を制限する.
template <typename F1, typename F2>
constexpr auto operator|(const F1& f1, const F2& f2) noexcept -> kcv::mod::composition_function_adapter<F1, F2> {
    return kcv::mod::composition_function_adapter<F1, F2>{f1, f2};
}

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_DAMAGE_FORMULA_MODIFIER_COMPOSITION_HPP_INCLUDED