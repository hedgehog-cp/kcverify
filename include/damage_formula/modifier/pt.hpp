#ifndef KCVERIFY_DAMAGE_FORMULA_MODIFIER_PT_HPP_INCLUDED
#define KCVERIFY_DAMAGE_FORMULA_MODIFIER_PT_HPP_INCLUDED

#include <cmath>
#include <optional>

#include "numeric.hpp"

namespace kcv {
namespace mod {

/// @brief PT小鬼群補正逆関数.
/// @todo sqrt(5)を定数化する.
struct pt_inverse final {
    template <typename T>
    static constexpr auto operator()(const T& x) -> std::optional<T> {
        const auto d1 = 6.0 * x - 55.0;
        if (d1 < 0) return std::nullopt;

        using boost::numeric::sqrt;
        using std::sqrt;

        const auto d2 = (-3.0 * x + sqrt(T{5.0}) * sqrt(d1) + 25.0);
        if (d2 >= 0 and d2 <= 0) return std::nullopt;

        return -10.0 / 9.0 * d2;
    }
};

/// @brief PT小鬼群補正関数.
struct pt final {
    template <typename T>
    static constexpr auto operator()(const T& x) -> std::optional<T> {
        if (x < 0) return std::nullopt;

        using boost::numeric::sqrt;
        using std::sqrt;

        return 0.3 * x + sqrt(x) + 10.0;
    }

    constexpr auto operator^(int) const noexcept -> pt_inverse {
        return pt_inverse{};
    }
};

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_DAMAGE_FORMULA_MODIFIER_PT_HPP_INCLUDED
