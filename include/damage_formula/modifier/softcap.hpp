#ifndef KCVERIFY_DAMAGE_FORMULA_MODIFIER_SOFTCAP_HPP_INCLUDED
#define KCVERIFY_DAMAGE_FORMULA_MODIFIER_SOFTCAP_HPP_INCLUDED

// std
#include <concepts>

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
        // REVIEW: 区間に対する大小比較.
        if constexpr (std::same_as<T, kcv::interval>) {
            constexpr auto f = [](const auto& x) { return x <= cap ? x : kcv::square(x - cap) + cap; };
            return kcv::interval{f(postcap.lower()), f(postcap.upper())};
        } else {
            return postcap < cap ? postcap : kcv::square(postcap - cap) + cap;
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
        return kcv::min(precap, cap) + kcv::sqrt(kcv::max(precap - cap, 0.0));
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
