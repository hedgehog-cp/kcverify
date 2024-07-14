#ifndef KCVERIFY_MASTER_EQUIPMENT_ENTITY_HPP_INCLUDED
#define KCVERIFY_MASTER_EQUIPMENT_ENTITY_HPP_INCLUDED

// std
#include <algorithm>
#include <array>
#include <cassert>
#include <functional>

// kcv
#include "master/equipment/equipment.hpp"

namespace kcv {

inline constexpr auto null_equipment = equipment_t{};

inline constexpr auto mst_equipment = std::to_array<equipment_t>({
#include "master/equipment/equipment.inc"
});
static_assert(std::ranges::is_sorted(mst_equipment, std::ranges::less{}, &equipment_t::name));

}  // namespace kcv

#endif  // KCVERIFY_MASTER_EQUIPMENT_ENTITY_HPP_INCLUDED
