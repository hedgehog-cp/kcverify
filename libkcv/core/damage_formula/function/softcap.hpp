#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_SOFTCAP_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_SOFTCAP_HPP_INCLUDED

// std
#include <optional>

// kcv
#include "core/interval.hpp"

namespace kcv {
namespace mod {

/// @brief ソフトキャップ補正逆関数.
struct softcap_inverse final {
    /// @brief ソフトキャップ補正逆関数を適用する.
    auto operator()(const kcv::interval& x) const noexcept -> std::optional<kcv::interval> {
        if (kcv::is_negative(x)) {
            return std::nullopt;
        }

        return x < cap ? x : cap + kcv::square(x - cap);
    }

    /// @brief キャップ値.
    kcv::interval cap;
};

/// @brief ソフトキャップ補正関数.
struct softcap final {
    /// @brief ソフトキャップ補正関数を適用する.
    auto operator()(const kcv::number& precap) const noexcept -> kcv::number {
        return kcv::min(precap, cap) + kcv::sqrt(kcv::max(precap - cap, kcv::number{0}));
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> softcap_inverse {
        return softcap_inverse{
            .cap = kcv::make_interval(cap),
        };
    }

    /// @brief キャップ値.
    kcv::number cap;
};

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_SOFTCAP_HPP_INCLUDED
