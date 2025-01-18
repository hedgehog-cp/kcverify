#ifndef KCVERIFY_DAMAGE_FORMULA_MODIFIER_PROFICIENCY_HPP_INCLUDED
#define KCVERIFY_DAMAGE_FORMULA_MODIFIER_PROFICIENCY_HPP_INCLUDED

#include "numeric.hpp"

namespace kcv {
namespace mod {

/// @brief 熟練度補正逆関数.
struct proficiency_inverse final {
    const kcv::interval a = 1.0;

    auto operator()(const auto& x) const -> kcv::interval {
        return x / a;
    }
};

/// @brief 熟練度補正関数.
struct proficiency final {
    const kcv::interval a = 1.0;

    auto operator()(const auto& x) const -> kcv::interval {
        return x * a;
    }

    auto operator^(int) const noexcept -> kcv::mod::proficiency_inverse {
        return proficiency_inverse{a};
    }
};

}  // namespace mod
}  // namespace kcv

#endif  // KCVERIFY_DAMAGE_FORMULA_MODIFIER_PROFICIENCY_HPP_INCLUDED
