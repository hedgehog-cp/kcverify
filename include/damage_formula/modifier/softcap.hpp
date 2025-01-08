#ifndef KCVERIFY_DAMAGE_FORMULA_MODIFIER_SOFTCAP_HPP_INCLUDED
#define KCVERIFY_DAMAGE_FORMULA_MODIFIER_SOFTCAP_HPP_INCLUDED

// std
#include <algorithm>
#include <cmath>
#include <type_traits>

// kcv
#include "numeric.hpp"

namespace kcv {
namespace mod {

/// @brief ソフトキャップ補正逆関数.
/// @tparam Cap キャップ値.
template <unsigned Cap>
struct softcap_inverse final {
    static constexpr auto cap = static_cast<kcv::float64_t>(Cap);

    /// @tparam T 浮動小数点数または機械区間.
    template <typename T>
    static constexpr auto operator()(const T& postcap) -> T {
        if constexpr (std::is_same_v<T, kcv::interval>) {
            // XXX: 仮実装. たぶんだめ.
            return postcap < cap ? postcap : boost::numeric::square(postcap - cap) + cap;
        } else {
            return postcap < cap ? postcap : std::pow(postcap - cap, 2.0) + cap;
        }
    }
};

/// @brief ソフトキャップ補正関数.
/// @tparam Cap キャップ値.
template <unsigned Cap>
struct softcap final {
    static constexpr auto cap = static_cast<kcv::float64_t>(Cap);

    /// @tparam T 浮動小数点数または機械区間.
    template <typename T>
    static constexpr auto operator()(const T& precap) -> T {
        using boost::numeric::min, boost::numeric::max, boost::numeric::sqrt;
        using std::min, std::max, std::sqrt;

        return min(precap, cap) + sqrt(max(precap - cap, 0.0));
    }

    constexpr auto operator^(int) const noexcept -> softcap_inverse<Cap> {
        return softcap_inverse<Cap>{};
    }
};

inline constexpr auto softcap170 = softcap<170>{};
inline constexpr auto softcap180 = softcap<180>{};
inline constexpr auto softcap220 = softcap<220>{};
inline constexpr auto softcap360 = softcap<360>{};

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_DAMAGE_FORMULA_MODIFIER_SOFTCAP_HPP_INCLUDED
