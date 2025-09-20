#ifndef KCVERIFY_EXTENSIONS_UTILITY_HPP_INCLUDED
#define KCVERIFY_EXTENSIONS_UTILITY_HPP_INCLUDED

// std
#include <functional>
#include <utility>

// kcv
#include "extensions/type_traits.hpp"

namespace kcv {

template <typename... Ts>
struct overloaded : public Ts... {
    using Ts::operator()...;
};

template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

struct invoke_fn final {
    template <typename F, typename... Args>
    static constexpr auto operator()(F&& f, Args&&... args) noexcept(std::is_nothrow_invocable_v<F, Args...>)
        -> std::invoke_result_t<F, Args...> {
        return std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    }

    template <typename F, typename T>
    static constexpr auto operator()(const F& f, const std::optional<T>& x) {
        if constexpr (kcv::is_optional_v<std::invoke_result_t<F, T>>) {
            return x.and_then(f);
        } else {
            return x.transform(f);
        }
    }
};

inline constexpr auto invoke = invoke_fn{};

}  // namespace kcv

#endif  // KCVERIFY_EXTENSIONS_UTILITY_HPP_INCLUDED
