#ifndef KCVERIFY_CONSTANTS_EQUIPMENT_HPP_INCLUDED
#define KCVERIFY_CONSTANTS_EQUIPMENT_HPP_INCLUDED

// std
#include <algorithm>
#include <array>
#include <cassert>
#include <memory>
#include <ranges>
#include <string_view>
#include <vector>

// kcv
#include "kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcsapi/types/api_type.hpp"
#include "kcsapi/types/enum/equipment_id.hpp"
#include "kcsapi/types/enum/icon.hpp"

namespace kcv {
namespace detail {

struct api_mst_slotitem_value_t final {
    kcv::kcsapi::equipment_id api_id;
    std::string_view api_name;

    // enumへの変換のためにコンストラクタを定義.
    consteval api_mst_slotitem_value_t(int api_id, const char *api_name)
        : api_id{api_id}
        , api_name{api_name} {}

    // コンストラクタを定義してしまったので, デフォルトコンストラクタを定義.
    consteval api_mst_slotitem_value_t() = default;
};

inline constexpr auto api_mst_slotitem = std::to_array<api_mst_slotitem_value_t>({
#include "constants/equipment.hpp.inc"
});
static_assert(std::ranges::is_sorted(api_mst_slotitem, {}, &api_mst_slotitem_value_t::api_id));

}  // namespace detail

/// @brief 装備名から装備IDに変換する.
consteval auto to_equipment_id(std::string_view name) -> kcv::kcsapi::equipment_id {
    const auto matched = kcv::detail::api_mst_slotitem
                       | std::ranges::views::filter([&name](const auto &e) -> bool { return e.api_name == name; })
                       | std::ranges::to<std::vector>();
    assert(matched.size() == 1);
    return matched.front().api_id;
}

inline namespace literals {
inline namespace equipment_literals {

consteval auto operator""_id(const char *str, std::size_t size) -> kcv::kcsapi::equipment_id {
    const auto name = std::string_view{str, size};
    return kcv::to_equipment_id(name);
}

}  // namespace equipment_literals
}  // namespace literals

// std::optional<const T &>を扱えるようになれば変更する.
// constexpr auto find_equipment_mst(kcv::kcsapi::equipment_id id, const kcv::kcsapi::api_mst_slotitem &mst)
//     -> std::optional<const kcv::kcsapi::api_mst_slotitem_value_t &>;
constexpr auto get_if(kcv::kcsapi::equipment_id id, const kcv::kcsapi::api_mst_slotitem &mst)
    -> const kcv::kcsapi::api_mst_slotitem_value_t *  //
{
    const auto itr = std::ranges::lower_bound(mst, id, {}, &kcv::kcsapi::api_mst_slotitem_value_t::api_id);
    if (itr != std::ranges::end(mst) and itr->api_id == id) [[likely]] {
        return std::to_address(itr);
    }

    return nullptr;
}

// 以下の関数群は全て`std::predicate<const kcv::kcsapi::api_mst_slotitem &>`を満たす.

/// @brief 電探であるかを検証する.
constexpr bool is_radar(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept {
    return std::get<kcsapi::idx_type::icon>(mst.api_type) == kcsapi::icon::radar;
}

/// @brief 対空電探であるかを検証する.
constexpr bool is_anti_air_radar(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept {
    return is_radar(mst) and mst.api_tyku >= 2;
}

/// @brief 水上電探であるかを検証する.
constexpr bool is_surface_radar(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept {
    return is_radar(mst) and mst.api_saku >= 5;
}

/// @brief 命中電探であるかを検証する.
constexpr bool is_accuracy_radar(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept {
    return is_radar(mst) and mst.api_houm >= 8;
}

/// @brief 夜間作戦航空要員であるかを検証する.
constexpr bool is_night_operation_aviation_personnel(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept {
    switch (mst.api_id) {
        using literals::equipment_literals::operator""_id;
        case "夜間作戦航空要員"_id:
        case "夜間作戦航空要員+熟練甲板員"_id:
            return true;

        default:
            return false;
    }
}

/// @brief 艦攻Swordfishであるかを検証する.
constexpr bool is_cb_swordfish(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept {
    switch (mst.api_id) {
        using literals::equipment_literals::operator""_id;
        case "Swordfish"_id:
        case "Swordfish Mk.II(熟練)"_id:
        case "Swordfish Mk.III(熟練)"_id:
            return true;

        default:
            return false;
    }
}

/// @brief 夜間機であるかを検証する.
constexpr bool is_night_plane(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept {
    switch (std::get<kcv::kcsapi::idx_type::icon>(mst.api_type)) {
        case kcv::kcsapi::icon::night_fighter:
        case kcv::kcsapi::icon::night_attacker:
            return true;

        default:
            return false;
    }
}

/// @brief 準夜間機であるかを検証する.
constexpr bool is_semi_night_plane(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept {
    switch (mst.api_id) {
        using literals::equipment_literals::operator""_id;
        case "零戦62型(爆戦/岩井隊)"_id:
        case "彗星一二型(三一号光電管爆弾搭載機)"_id:
            return true;

        default:
            return false;
    }
}

}  // namespace kcv

#endif  // KCVERIFY_CONSTANTS_EQUIPMENT_HPP_INCLUDED
