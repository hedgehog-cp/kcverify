#ifndef KCVERIFY_CORE_BATTLELOG_EQUIPMENT_BONUS_HPP_INCLUDED
#define KCVERIFY_CORE_BATTLELOG_EQUIPMENT_BONUS_HPP_INCLUDED

// std
#include <vector>

// kcv
#include "core/battlelog/ship.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_value.hpp"
#include "models/kc3kai/mst_slotitem_bonus.hpp"

namespace kcv {

/// @brief 装備ボーナスを求める.
/// @param ship 艦船.
/// @param bonus_list 74式EN固有の装備ボーナスオブジェクト.
/// @return 装備ボーナスの合計.
auto get_equipment_bonus(
    const kcv::ship& ship,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& bonus_list
) -> kcv::eoen::serialization::fit_bonus::fit_bonus_value;

/// @brief 装備ボーナスを求める.
/// @param ship 艦船.
/// @param bonus_list KC3改固有の装備ボーナスオブジェクト.
/// @return 装備ボーナスの合計.
auto get_equipment_bonus(
    const kcv::ship& ship,                                          //
    const std::vector<kcv::kc3kai::mst_slotitem_bonus>& bonus_list  //
) -> kcv::kc3kai::bonus_value;

}  // namespace kcv

#endif  // KCVERIFY_CORE_BATTLELOG_EQUIPMENT_BONUS_HPP_INCLUDED
