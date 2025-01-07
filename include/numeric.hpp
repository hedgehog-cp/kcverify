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

}  // namespace kcv

#endif  // KCVERIFY_NUMERIC_HPP_INCLUDED
