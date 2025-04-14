#ifndef KCVERIFY_CORE_CONSTANTS_SHIP_HPP_INCLUDED
#define KCVERIFY_CORE_CONSTANTS_SHIP_HPP_INCLUDED

// std
#include <algorithm>
#include <array>
#include <cstddef>
#include <ranges>
#include <stdexcept>
#include <string_view>
#include <utility>

// kcv
#include "inplace_vector.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"

namespace kcv {
namespace detail {

#include "core/constants/ship.hpp.inc"

}  // namespace detail
}  // namespace kcv

namespace kcv {

consteval auto ship_id(std::string_view name) -> kcv::kcsapi::ship_id {
    if (name == "宗谷") {
        throw std::invalid_argument{"ship id is not uniquely determined from '宗谷'."};
    }

    for (const auto& [api_id, api_name] : kcv::detail::api_mst_ship) {
        if (name == api_name) {
            return api_id;
        }
    }

    throw std::invalid_argument{"ship id not found."};
}

inline namespace literals {
inline namespace ship_literals {

consteval auto operator""_id(const char* str, std::size_t size) -> kcv::kcsapi::ship_id {
    const auto name = std::string_view{str, size};
    return kcv::ship_id(name);
}

}  // namespace ship_literals
}  // namespace literals
}  // namespace kcv

// MARK: 述語関数
// 以下の関数群は全て`std::predicate<const kcv::kcsapi::api_mst_ship_value_t& `を満たす.

namespace kcv {

/// @brief 深海棲艦であるかを検証する.
constexpr bool is_abyssal_ship(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    return mst.api_id > kcv::kcsapi::ship_id{1500};
}

/// @brief 陸上型であるかを検証する.
constexpr bool is_installation(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    return mst.api_soku == 0;
}

/// @brief 砲台小鬼あるいはトーチカであるかを検証する.
constexpr bool is_pillbox(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    static constexpr auto ids = kcv::detail::api_mst_ship
                              | std ::ranges::views::filter([](const auto& e) static -> bool {
                                    const auto& [_, api_name] = e;
                                    return api_name == "砲台小鬼"              //
                                        or api_name == "トーチカ小鬼"          //
                                        or api_name == "対空小鬼"              //
                                        or api_name == "トーチカ要塞棲姫"      //
                                        or api_name == "トーチカ要塞棲姫-壊";  //
                                })
                              | std::ranges ::views::transform([](const auto& e) static -> kcv::kcsapi::ship_id {
                                    const auto& [api_id, _] = e;
                                    return api_id;
                                })
                              | std::ranges::to<kcv::inplace_vector<kcv::kcsapi::ship_id, 13>>();

    static_assert(std::ranges::is_sorted(ids));
    return std::ranges::binary_search(ids, mst.api_id);
}

/// @brief 離島棲姫であるかを検証する.
constexpr bool is_isolated_island(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    static constexpr auto ids = kcv::detail::api_mst_ship
                              | std::ranges::views::filter([](const auto& e) static -> bool {
                                    const auto& [_, api_name] = e;
                                    return api_name == "離島棲姫";
                                })
                              | std::ranges::views::transform([](const auto& e) static -> kcv::kcsapi::ship_id {
                                    const auto& [api_id, _] = e;
                                    return api_id;
                                })
                              | std::ranges::to<kcv::inplace_vector<kcv::kcsapi::ship_id, 5>>();

    static_assert(std::ranges::is_sorted(ids));
    return std::ranges::binary_search(ids, mst.api_id);
}

/// @brief 港湾棲姫であるかを検証する.
constexpr bool is_harbour_summer_princess(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    static constexpr auto ids = kcv::detail::api_mst_ship
                              | std::ranges::views::filter([](const auto& e) static -> bool {
                                    const auto& [_, api_name] = e;
                                    return api_name == "港湾夏姫"               //
                                        or api_name == "港湾夏姫II"             //
                                        or api_name == "港湾夏姫II-壊"          //
                                        or api_name == "港湾夏姫-壊"            //
                                        or api_name == "港湾棲姫 休日mode"      //
                                        or api_name == "港湾棲姫 休日mode-壊";  //
                                })
                              | std::ranges::views::transform([](const auto& e) static -> kcv::kcsapi::ship_id {
                                    const auto& [api_id, _] = e;
                                    return api_id;
                                })
                              | std::ranges::to<kcv::inplace_vector<kcv::kcsapi::ship_id, 16>>();

    static_assert(std::ranges::is_sorted(ids));
    return std::ranges::binary_search(ids, mst.api_id);
}

/// @brief ソフトスキンであるかを検証する.
constexpr bool is_soft_skin(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    return is_installation(mst) and not(is_pillbox(mst) or is_isolated_island(mst) or is_harbour_summer_princess(mst));
}

/// @brief 潜水艦であるかを検証する.
constexpr bool is_submarine(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    switch (mst.api_stype) {
        case kcv::kcsapi::stype::ss:
        case kcv::kcsapi::stype::ssv:
            return true;

        default:
            return false;
    }
}

/// @brief 航空母艦であるかを検証する.
constexpr bool is_aircraft_carrier(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    switch (mst.api_stype) {
        case kcv::kcsapi::stype::cvl:
        case kcv::kcsapi::stype::cv:
        case kcv::kcsapi::stype::cvb:
            return true;

        default:
            return false;
    }
}

/// @brief 夜間作戦空母であるかを検証する.
constexpr bool is_night_operation_aircraft_carrier(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::ship_literals::operator""_id;
        case "Saratoga Mk.II"_id:
        case "赤城改二戊"_id:
        case "加賀改二戊"_id:
        case "龍鳳改二戊"_id:
            return true;

        default:
            return false;
    }
}

/// @brief 夜間砲撃可能空母であるかを検証する.
constexpr bool is_night_shellable_aircraft_carrier(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::ship_literals::operator""_id;
        case "Graf Zeppelin"_id:
        case "Graf Zeppelin改"_id:
        case "大鷹改二"_id:
        case "神鷹改二"_id:
        case "Saratoga"_id:
        case "加賀改二護"_id:
            return true;

        default:
            return false;
    }
}

/// @brief アークロイヤルであるかを検証する.
constexpr bool is_ark_royal(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::ship_literals::operator""_id;
        case "Ark Royal"_id:
        case "Ark Royal改"_id:
            return true;

        default:
            return false;
    }
}

}  // namespace kcv

#endif  // KCVERIFY_CORE_CONSTANTS_SHIP_HPP_INCLUDED
