#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_EQUIPMENT_BONUS_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_EQUIPMENT_BONUS_HPP_INCLUDED

// std
#include <vector>

// kcv
#include "core/entity/ship.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_value.hpp"
#include "models/kc3kai/mst_slotitem_bonus.hpp"

namespace kcv {

/// @brief 装備ボーナスを求める.
/// @param ship 艦船.
/// @param fit_bonuses 74式EN固有の装備ボーナスオブジェクト.
/// @return 装備ボーナスの合計.
auto total_equipment_bonus(
    const kcv::ship& ship,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses
) -> kcv::eoen::serialization::fit_bonus::fit_bonus_value;

/// @brief 装備ボーナスを求める.
/// @param ship 艦船.
/// @param fit_bonuses KC3改固有の装備ボーナスオブジェクト.
/// @return 装備ボーナスの合計.
auto total_equipment_bonus(
    const kcv::ship& ship,                                           //
    const std::vector<kcv::kc3kai::mst_slotitem_bonus>& fit_bonuses  //
) -> kcv::kc3kai::bonus_value;

}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_EQUIPMENT_BONUS_HPP_INCLUDED
