#ifndef KCVERIFY_CONSTANTS_SHIP_HPP_INCLUDED
#define KCVERIFY_CONSTANTS_SHIP_HPP_INCLUDED

#include <algorithm>
#include <array>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <ranges>
#include <string_view>
#include <vector>

#include "kcsapi/types/enum/ship_id.hpp"
#include "kcsapi/types/enum/stype.hpp"

namespace kcv {

namespace detail {

struct api_mst_ship_value_t final {
    kcv::kcsapi::ship_id api_id;
    std::string_view api_name;
    kcv::kcsapi::stype api_stype;

    // enumへの変換のためにコンストラクタを定義.
    consteval api_mst_ship_value_t(int api_id, const char* api_name, int api_stype)
        : api_id{api_id}
        , api_name{api_name}
        , api_stype{api_stype} {}

    // コンストラクタを定義してしまったので, デフォルトコンストラクタを定義.
    consteval api_mst_ship_value_t() = default;
};

inline constexpr auto api_mst_ship = std::to_array<api_mst_ship_value_t>({
#include "constants/ship.hpp.inc"
});
static_assert(std::ranges::is_sorted(api_mst_ship, {}, &api_mst_ship_value_t::api_id));

/// @brief 条件に一致するマスタデータを抽出して, コピーした値を固定長配列で返す.
/// @note predをラムダ式で定義するとき, キャプチャをするとconstexprの文脈で使えなくなるためコンパイルエラーとなる.
consteval auto extract_ships_from_mst(const std::predicate<const api_mst_ship_value_t&> auto pred) {
    constexpr auto size = std::ranges::count_if(api_mst_ship, pred);

    auto arr = std::array<api_mst_ship_value_t, size>{};
    for (auto&& [dst, src] : std::ranges::views::zip(arr, api_mst_ship | std::ranges::views::filter(pred))) {
        dst = src;
    }

    return arr;
}

}  // namespace detail

/// @brief 艦船名から艦船IDに変換する.
/// @note 艦船名と艦船IDは全単射しない. このため, 一意に変換できない引数に対してエラーとする.
consteval auto to_ship_id(std::string_view name) -> kcv::kcsapi::ship_id {
    const auto matched = kcv::detail::api_mst_ship
                       | std::ranges::views::filter([&name](const auto& e) -> bool { return e.api_name == name; })
                       | std::ranges::to<std::vector>();
    assert(matched.size() == 1);
    return matched.front().api_id;
}

inline namespace literals {
inline namespace ship_literals {

consteval auto operator""_id(const char* str, std::size_t size) -> kcv::kcsapi::ship_id {
    const auto name = std::string_view{str, size};
    return kcv::to_ship_id(name);
}

}  // namespace ship_literals
}  // namespace literals

// 以下の関数群は全て`std::predicate<kcv::kcsapi::ship_id>`を満たす.

/// @brief 潜水艦であるかを検証する.
constexpr bool is_submarine(kcv::kcsapi::ship_id id) noexcept {
    constexpr auto list = kcv::detail::extract_ships_from_mst([](const auto& e) static -> bool {
        switch (e.api_stype) {
            case kcv::kcsapi::stype::ss:
            case kcv::kcsapi::stype::ssv:
                return true;

            default:
                return false;
        }
    });
    return std::ranges::binary_search(list, id, {}, &kcv::detail::api_mst_ship_value_t::api_id);
}

/// @brief 航空母艦であるかを検証する.
constexpr bool is_aircraft_carrier(kcv::kcsapi::ship_id id) noexcept {
    constexpr auto list = kcv::detail::extract_ships_from_mst([](const auto& e) static -> bool {
        switch (e.api_stype) {
            case kcv::kcsapi::stype::cvl:
            case kcv::kcsapi::stype::cv:
            case kcv::kcsapi::stype::cvb:
                return true;

            default:
                return false;
        }
    });
    return std::ranges::binary_search(list, id, {}, &kcv::detail::api_mst_ship_value_t::api_id);
}

/// @brief 夜間作戦空母であるかを検証する.
constexpr bool is_night_operation_aircraft_carrier(kcv::kcsapi::ship_id id) noexcept {
    constexpr auto list = kcv::detail::extract_ships_from_mst([](const auto& e) static -> bool {
        switch (e.api_id) {
            using literals::ship_literals::operator""_id;
            case "Saratoga Mk.II"_id:
            case "赤城改二戊"_id:
            case "加賀改二戊"_id:
            case "龍鳳改二戊"_id:
                return true;

            default:
                return false;
        }
    });
    return std::ranges::binary_search(list, id, {}, &kcv::detail::api_mst_ship_value_t::api_id);
}

/// @brief 夜間砲撃可能空母であるかを検証する.
constexpr bool is_night_shellable_aircraft_carrier(kcv::kcsapi::ship_id id) noexcept {
    constexpr auto list = kcv::detail::extract_ships_from_mst([](const auto& e) static -> bool {
        switch (e.api_id) {
            using literals::ship_literals::operator""_id;
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
    });
    return std::ranges::binary_search(list, id, {}, &kcv::detail::api_mst_ship_value_t::api_id);
}

/// @brief アークロイヤルであるかを検証する.
constexpr bool is_ark_royal(kcv::kcsapi::ship_id id) noexcept {
    constexpr auto list = kcv::detail::extract_ships_from_mst([](const auto& e) static -> bool {
        switch (e.api_id) {
            using literals::ship_literals::operator""_id;
            case "Ark Royal"_id:
            case "Ark Royal改"_id:
                return true;

            default:
                return false;
        }
    });
    return std::ranges::binary_search(list, id, {}, &kcv::detail::api_mst_ship_value_t::api_id);
}

}  // namespace kcv

#endif  // KCVERIFY_CONSTANTS_SHIP_HPP_INCLUDED
