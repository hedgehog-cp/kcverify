#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_TORPEDO_EQUIPMENT_LEVEL_BONUS_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_TORPEDO_EQUIPMENT_LEVEL_BONUS_HPP_INCLUDED

// std
#include <cstdint>

// kcv
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "stdfloat.hpp"

namespace kcv {
namespace damage_formulae {
namespace torpedo {

/// @brief 雷撃戦.改修効果.
/// @param mst 装備マスタ.
/// @param level 改修値.
auto equipment_level_bonus(const kcv::kcsapi::api_mst_slotitem_value_t& mst, std::int32_t level) -> kcv::float64_t;

}  // namespace torpedo
}  // namespace damage_formulae
}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_TORPEDO_EQUIPMENT_LEVEL_BONUS_HPP_INCLUDED
