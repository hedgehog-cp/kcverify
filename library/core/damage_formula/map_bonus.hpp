#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_MAP_BONUS_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_MAP_BONUS_HPP_INCLUDED

#include "core/entity/ship.hpp"
#include "models/kc3kai/bonus/bonus.hpp"

namespace kcv {

struct map_bonus_result_t final {
    double dmg;
    double acc;
    double eva;
};

auto total_map_bonus(
    const kcv::ship& ship,                                      //
    const std::vector<kcv::kc3kai::bonus_bonus_t>& map_bonuses  //
) -> map_bonus_result_t;

}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_MAP_BONUS_HPP_INCLUDED
