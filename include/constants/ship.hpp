#ifndef KCVERIFY_CONSTANTS_SHIP_HPP_INCLUDED
#define KCVERIFY_CONSTANTS_SHIP_HPP_INCLUDED

// std
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <ranges>
#include <string_view>
#include <vector>

// kcv
#include "kcsapi/api_start2/api_mst_ship.hpp"
#include "kcsapi/types/enum/ship_id.hpp"
#include "kcsapi/types/enum/stype.hpp"

namespace kcv {

namespace detail {

struct api_mst_ship_value_t final {
    kcv::kcsapi::ship_id api_id;
    std::string_view api_name;

    // enumへの変換のためにコンストラクタを定義.
    consteval api_mst_ship_value_t(int api_id, const char* api_name)
        : api_id{api_id}
        , api_name{api_name} {}

    // コンストラクタを定義してしまったので, デフォルトコンストラクタを定義.
    consteval api_mst_ship_value_t() = default;
};

inline constexpr auto api_mst_ship = std::to_array<api_mst_ship_value_t>({
#include "constants/ship.hpp.inc"
});
static_assert(std::ranges::is_sorted(api_mst_ship, {}, &api_mst_ship_value_t::api_id));

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

// std::optional<const T &>を扱えるようになれば変更する.
// constexpr auto find_ship_mst(kcv::kcsapi::ship_id id, const kcv::kcsapi::api_mst_ship &mst)
//     -> std::optional<const kcv::kcsapi::api_mst_ship_value_t &>;
constexpr auto get_if(kcv::kcsapi::ship_id id, const kcv::kcsapi::api_mst_ship& mst)
    -> const kcv::kcsapi::api_mst_ship_value_t*  //
{
    const auto itr = std::ranges::lower_bound(mst, id, {}, &kcv::kcsapi::api_mst_ship_value_t::api_id);
    if (itr != std::ranges::end(mst) and itr->api_id == id) [[likely]] {
        return std::to_address(itr);
    }

    return nullptr;
}

// 以下の関数群は全て`std::predicate<const kcv::kcsapi::api_mst_ship_value_t& `を満たす.

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
        using literals::ship_literals::operator""_id;
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
}

/// @brief アークロイヤルであるかを検証する.
constexpr bool is_ark_royal(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    switch (mst.api_id) {
        using literals::ship_literals::operator""_id;
        case "Ark Royal"_id:
        case "Ark Royal改"_id:
            return true;

        default:
            return false;
    }
}

}  // namespace kcv

#endif  // KCVERIFY_CONSTANTS_SHIP_HPP_INCLUDED
