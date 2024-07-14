#ifndef KCVERIFY_MASTER_SHIP_ENTITY_HPP_INCLUDED
#define KCVERIFY_MASTER_SHIP_ENTITY_HPP_INCLUDED

// std
#include <algorithm>
#include <array>
#include <functional>

// kcv
#include "master/ship/ship.hpp"

namespace kcv {

inline constexpr auto null_ship = ship_t{};

inline constexpr auto mst_ship = std::to_array<ship_t>({
#include "master/ship/ship.inc"
});

static_assert(std::ranges::is_sorted(mst_ship, std::ranges::less{}, &ship_t::id));

}  // namespace kcv

#endif  // KCVERIFY_MASTER_SHIP_ENTITY_HPP_INCLUDED
