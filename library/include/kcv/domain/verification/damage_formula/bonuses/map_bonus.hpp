#ifndef KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_MODIFIERS_ATTACK_POWER_MODIFIERS_BONUSES_MAP_BONUS_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_MODIFIERS_ATTACK_POWER_MODIFIERS_BONUSES_MAP_BONUS_HPP_INCLUDED

#include "kcv/domain/verification/entity/ship.hpp"
#include "kcv/external/kc3kai/bonus/bonus.hpp"

namespace kcv {

struct map_bonus_result final {
    double dmg = 1.0;
    double acc = 1.0;
    double eva = 1.0;

    friend auto operator*=(map_bonus_result& lhs, const map_bonus_result& rhs) noexcept -> map_bonus_result& {
        lhs.dmg *= rhs.dmg;
        lhs.acc *= rhs.acc;
        lhs.eva *= rhs.eva;
        return lhs;
    }
};

auto total_map_bonus(
    const kcv::ship& ship,                                      //
    const std::vector<kcv::kc3kai::bonus_bonus_t>& map_bonuses  //
) -> map_bonus_result;

}  // namespace kcv

#endif  // KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_MODIFIERS_ATTACK_POWER_MODIFIERS_BONUSES_MAP_BONUS_HPP_INCLUDED
