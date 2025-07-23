#ifndef KCVERIFY_EXTENSIONS_STDFLOAT_HPP_INCLUDED
#define KCVERIFY_EXTENSIONS_STDFLOAT_HPP_INCLUDED

#include <climits>
#include <limits>

namespace kcv {

/// @brief C++26 std::float128_tの代替.
using float128_t = long double;
static_assert(std::numeric_limits<float128_t>::is_iec559);
static_assert(sizeof(float128_t) * CHAR_BIT == 128);

/// @brief C++26 std::float64_tの代替.
using float64_t = double;
static_assert(std::numeric_limits<float64_t>::is_iec559);
static_assert(sizeof(float64_t) * CHAR_BIT == 64);

/// @brief C++26 std::float32_tの代替.
using float32_t = float;
static_assert(std::numeric_limits<float32_t>::is_iec559);
static_assert(sizeof(float32_t) * CHAR_BIT == 32);

}  // namespace kcv

#endif  // KCVERIFY_EXTENSIONS_STDFLOAT_HPP_INCLUDED
