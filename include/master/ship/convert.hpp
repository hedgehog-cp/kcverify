#ifndef KCVERIFY_MASTER_SHIP_CONVERT_HPP_INCLUDED
#define KCVERIFY_MASTER_SHIP_CONVERT_HPP_INCLUDED

// std
#include <algorithm>
#include <cstddef>
#include <functional>
#include <ranges>
#include <string_view>

// kcv
#include "master/ship/entity.hpp"
#include "master/ship/ship.hpp"

namespace kcv {

constexpr auto to_master(ship_t::id_type id) noexcept -> const ship_t& {
    const auto itr = std::ranges::lower_bound(mst_ship, id, std::ranges::less{}, &ship_t::id);
    if (itr != std::ranges::end(mst_ship) and itr->id() == id) [[likely]] {
        return *itr;
    }
    return null_ship;
}

inline namespace literals {
inline namespace ship_literals {

consteval auto operator""_id(const char* str, std::size_t size) noexcept -> ship_t::id_type {
    const auto name = std::string_view{str, size};
    const auto itr  = std::ranges::find(mst_ship, name, &ship_t::name);
    assert(itr != std::ranges::end(mst_ship));
    return itr->id();
}

}  // namespace ship_literals
}  // namespace literals

}  // namespace kcv

#endif  // KCVERIFY_MASTER_SHIP_CONVERT_HPP_INCLUDED
