#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_PT_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_PT_HPP_INCLUDED

// std
#include <optional>

// kcv
#include "core/interval.hpp"

namespace kcv {
namespace mod {

/// @brief PT小鬼群補正逆関数.
struct pt_inverse final {
    static auto operator()(const kcv::interval& x) noexcept -> std::optional<kcv::interval> {
        const auto a = 6.0 * x - 55.0;
        if (kcv::is_negative(a)) {
            return std::nullopt;
        }

        const auto b = -3.0 * x + kcv::sqrt(kcv::interval{5.0}) * kcv::sqrt(a) + 25.0;
        if (kcv::is_zero(b)) {
            return std::nullopt;
        }

        return -10.0 / 9.0 * b;
    }
};

/// @brief PT小鬼群補正関数.
struct pt final {
    /// @brief PT小鬼群補正関数を適用する.
    static auto operator()(const kcv::number& x) noexcept -> std::optional<kcv::number> {
        if (kcv::is_negative(x)) {
            return std::nullopt;
        }

        return 0.3 * x + kcv::sqrt(x) + 10.0;
    }

    auto operator^(int) const noexcept -> pt_inverse {
        return pt_inverse{};
    }
};

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTION_PT_HPP_INCLUDED
