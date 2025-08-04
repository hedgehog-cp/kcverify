#ifndef KCVERIFY_EXTENSIONS_INTERVAL_HPP_INCLUDED
#define KCVERIFY_EXTENSIONS_INTERVAL_HPP_INCLUDED

// std
#include <concepts>

// kcv
#include "extensions/interval/basic_interval.hpp"
#include "extensions/interval/floating_environment.hpp"
#include "extensions/stdfloat.hpp"

namespace kcv {

/// @brief 順算用算術数値型. 精度保証なしの区間演算を行える.
using number = basic_interval<kcv::float64_t, kcv::fenv::neutral>;

/// @brief 逆算用算術数値型. 精度保証付きの区間演算を行える.
using interval = basic_interval<kcv::float64_t, kcv::fenv::rounding>;

/// @brief intervalにする.
template <typename T>
auto make_interval(const T& x) noexcept -> interval {
    if constexpr (std::same_as<T, interval::base_type>) {
        return interval{x};
    } else if constexpr (std::same_as<T, number>) {
        return interval{x.lower(), x.upper()};
    } else {
        static_assert(false);
    }
}

}  // namespace kcv

#endif  // KCVERIFY_EXTENSIONS_INTERVAL_HPP_INCLUDED
