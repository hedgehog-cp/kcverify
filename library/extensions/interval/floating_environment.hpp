#ifndef KCVERIFY_EXTENSIONS_INTERVAL_FLOATING_ENVIRONMENT_HPP_INCLUDED
#define KCVERIFY_EXTENSIONS_INTERVAL_FLOATING_ENVIRONMENT_HPP_INCLUDED

// std
#include <cfenv>
#include <concepts>
#include <type_traits>

// kcv
#include "extensions/attributes.hpp"

namespace kcv {

/// @brief 浮動小数点数環境.
template <typename T>
concept floating_environment = requires(const T x) {
    // 引数無しで浮動小数点数環境を提供できること.
    requires std::default_initializable<T>;

    // RAIIを利用した浮動小数点数環境のリセットを例外なしで行えること.
    requires std::is_nothrow_destructible_v<T>;

    // 下向き丸め環境のもとで関数を評価するとともに, その結果を返すこと.
    {
        x.down([]() -> std::floating_point auto { return 0.0; })
    } -> std::floating_point;

    // 上向き丸め環境のもとで関数を評価するとともに, その結果を返すこと.
    {
        x.up([]() -> std::floating_point auto { return 0.0; })
    } -> std::floating_point;
};

namespace fenv {

/// @brief 精度保証なし数値計算のための浮動小数点数環境.
/// 単なる区間演算のための, 既定の最近接丸めの浮動小数点数環境を提供する.
struct neutral final {
    neutral() = default;

    ~neutral() = default;

    auto down(const std::invocable<> auto& f) const noexcept(noexcept(f())) {
        return f();
    }

    auto up(const std::invocable<> auto& f) const noexcept(noexcept(f())) {
        return f();
    }
};

/// @brief 精度保証付き数値計算のための浮動小数点数環境.
/// 最適化(inline展開が主原因か?)によって精度保証付き数値計算が壊れるため,
/// 処理系が提供する非標準のnoinline属性を指定する.
struct rounding final {
    rounding() = default;

    ~rounding() {
        std::fesetround(FE_TONEAREST);
    }

    [[NOINLINE]]
    auto down(const std::invocable<> auto& f) const noexcept(noexcept(f())) {
        std::fesetround(FE_DOWNWARD);
        return f();
    }

    [[NOINLINE]]
    auto up(const std::invocable<> auto& f) const noexcept(noexcept(f())) {
        std::fesetround(FE_UPWARD);
        return f();
    }
};

}  // namespace fenv
}  // namespace kcv

#endif  // KCVERIFY_EXTENSIONS_INTERVAL_FLOATING_ENVIRONMENT_HPP_INCLUDED
