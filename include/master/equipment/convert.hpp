#ifndef KCVERIFY_MASTER_EQUIPMENT_CONVERT_HPP_INCLUDED
#define KCVERIFY_MASTER_EQUIPMENT_CONVERT_HPP_INCLUDED

// std
#include <algorithm>
#include <concepts>
#include <cstddef>
#include <functional>
#include <ranges>
#include <string_view>

// kcv
#include "master/equipment/entity.hpp"
#include "master/equipment/equipment.hpp"

namespace kcv {

template <std::equality_comparable_with<std::string_view> T>
constexpr auto to_master(const T& name) noexcept -> const equipment_t& {
    const auto itr = std::ranges::lower_bound(mst_equipment, name, std::ranges::less{}, &equipment_t::name);
    if (itr != std::ranges::end(mst_equipment) and itr->name() == name) [[likely]] {
        return *itr;
    }
    return null_equipment;
}

inline namespace literals {
inline namespace equipment_literals {

consteval auto operator""_id(const char* str, std::size_t size) noexcept -> equipment_t::id_type {
    const auto name = std::string_view{str, size};
    const auto itr  = std::ranges::lower_bound(mst_equipment, name, std::ranges::less{}, &equipment_t::name);
    assert(itr != std::ranges::end(mst_equipment));
    assert(itr->name() == name);
    return itr->id();
}

}  // namespace equipment_literals
}  // namespace literals

}  // namespace kcv

#endif  // KCVERIFY_MASTER_EQUIPMENT_CONVERT_HPP_INCLUDED
