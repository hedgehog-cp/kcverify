#ifndef KCVERIFY_NUMERIC_HPP_INCLUDED
#define KCVERIFY_NUMERIC_HPP_INCLUDED

/**
 * @file numeric.hpp
 * @brief 標準ヘッダ<numeric>の拡張.
 */
#include <numeric>

// clang(libc++)では未実装なので使えない.
// https://stackoverflow.com/questions/79134066/missing-include-file-in-llvm-clang-stdfloat
// #include <stdfloat>
// namespace kcv {
// using real = std::float64_t;
// }  // namespace kcv

// もちろんまだない
// #include <strict_float>

// std
#include <concepts>
#include <limits>

// boost
#include <boost/numeric/interval.hpp>

namespace kcv {

/// @note 艦これのサーバはIEEE754 binary64準拠の規格に基づいて計算していると推測されている.
using float64_t = double;
static_assert(sizeof(float64_t) == 8);
static_assert(std::numeric_limits<float64_t>::is_iec559);

/// @brief 機械区間.
using interval = boost::numeric::interval<float64_t>;

template <typename T>
constexpr auto sqrt(const T& x) {
    if constexpr (std::same_as<T, kcv::interval>) {
        return boost::numeric::sqrt(x);
    } else {
        return std::sqrt(x);
    }
}

template <typename T>
constexpr auto square(const T& x) {
    if constexpr (std::same_as<T, kcv::interval>) {
        return boost::numeric::square(x);
    } else {
        return std::sqrt(x);
    }
}

// TODO: kcv::min, kcv::maxを定義する.
// シグネチャの都合でちょっと定義するのが難しいので後回し.

}  // namespace kcv

#endif  // KCVERIFY_NUMERIC_HPP_INCLUDED
