#ifndef KCVERIFY_CONSTANTS_EQUIPMENT_HPP_INCLUDED
#define KCVERIFY_CONSTANTS_EQUIPMENT_HPP_INCLUDED

#include <algorithm>
#include <array>
#include <cassert>
#include <ranges>
#include <string_view>
#include <vector>

#include "kcsapi/types/api_type.hpp"
#include "kcsapi/types/enum/equipment_id.hpp"
#include "kcsapi/types/enum/icon.hpp"

namespace kcv {
namespace detail {

struct api_mst_slotitem_value_t final {
    kcv::kcsapi::equipment_id api_id;
    std::string_view api_name;
    kcv::kcsapi::api_type api_type;

    // enumへの変換のためにコンストラクタを定義.
    consteval api_mst_slotitem_value_t(int api_id, const char* api_name, int icon)
        : api_id{api_id}
        , api_name{api_name}
        , api_type{{}, {}, {}, kcv::kcsapi::icon{icon}, {}} {}

    // コンストラクタを定義してしまったので, デフォルトコンストラクタを定義.
    consteval api_mst_slotitem_value_t() = default;
};

inline constexpr auto api_mst_slotitem = std::to_array<api_mst_slotitem_value_t>({
#include "constants/equipment.hpp.inc"
});
static_assert(std::ranges::is_sorted(api_mst_slotitem, {}, &api_mst_slotitem_value_t::api_id));

/// @brief 条件に一致するマスタデータを抽出して, コピーした値を固定長配列で返す.
/// @note predをラムダ式で定義するとき, キャプチャをするとconstexprの文脈で使えなくなるためコンパイルエラーとなる.
consteval auto extract_equipments_from_mst(const std::predicate<const api_mst_slotitem_value_t&> auto pred) {
    constexpr auto size = std::ranges::count_if(api_mst_slotitem, pred);

    auto arr = std::array<api_mst_slotitem_value_t, size>{};
    for (auto&& [dst, src] : std::ranges::views::zip(arr, api_mst_slotitem | std::ranges::views::filter(pred))) {
        dst = src;
    }

    return arr;
}

}  // namespace detail

/// @brief 装備名から装備IDに変換する.
consteval auto to_equipment_id(std::string_view name) -> kcv::kcsapi::equipment_id {
    const auto matched = kcv::detail::api_mst_slotitem
                       | std::ranges::views::filter([&name](const auto& e) -> bool { return e.api_name == name; })
                       | std::ranges::to<std::vector>();
    assert(matched.size() == 1);
    return matched.front().api_id;
}

inline namespace literals {
inline namespace equipment_literals {

consteval auto operator""_id(const char* str, std::size_t size) -> kcv::kcsapi::equipment_id {
    const auto name = std::string_view{str, size};
    return kcv::to_equipment_id(name);
}

}  // namespace equipment_literals
}  // namespace literals

/// @brief 夜間作戦航空要員であるかを検証する.
constexpr bool is_night_operation_aviation_personnel(kcv::kcsapi::equipment_id id) noexcept {
    constexpr auto list = kcv::detail::extract_equipments_from_mst([](const auto& e) static -> bool {
        switch (e.api_id) {
            using literals::equipment_literals::operator""_id;
            case "夜間作戦航空要員"_id:
            case "夜間作戦航空要員+熟練甲板員"_id:
                return true;

            default:
                return false;
        }
    });
    return std::ranges::binary_search(list, id, {}, &kcv::detail::api_mst_slotitem_value_t::api_id);
}

/// @brief 艦攻Swordfishであるかを検証する.
constexpr bool is_cb_swordfish(kcv::kcsapi::equipment_id id) noexcept {
    constexpr auto list = kcv::detail::extract_equipments_from_mst([](const auto& e) static -> bool {
        switch (e.api_id) {
            using literals::equipment_literals::operator""_id;
            case "Swordfish"_id:
            case "Swordfish Mk.II(熟練)"_id:
            case "Swordfish Mk.III(熟練)"_id:
                return true;

            default:
                return false;
        }
    });
    return std::ranges::binary_search(list, id, {}, &kcv::detail::api_mst_slotitem_value_t::api_id);
}

/// @brief 夜間機であるかを検証する.
constexpr bool is_night_plane(kcv::kcsapi::equipment_id id) noexcept {
    constexpr auto list = kcv::detail::extract_equipments_from_mst([](const auto& e) static -> bool {
        switch (std::get<kcv::kcsapi::idx_type::icon>(e.api_type)) {
            case kcv::kcsapi::icon::night_fighter:
            case kcv::kcsapi::icon::night_attacker:
                return true;

            default:
                return false;
        }
    });
    return std::ranges::binary_search(list, id, {}, &kcv::detail::api_mst_slotitem_value_t::api_id);
}

/// @brief 準夜間機であるかを検証する.
constexpr bool is_semi_night_plane(kcv::kcsapi::equipment_id id) noexcept {
    constexpr auto list = kcv::detail::extract_equipments_from_mst([](const auto& e) static -> bool {
        switch (e.api_id) {
            using literals::equipment_literals::operator""_id;
            case "零戦62型(爆戦/岩井隊)"_id:
            case "彗星一二型(三一号光電管爆弾搭載機)"_id:
                return true;

            default:
                return false;
        }
    });
    return std::ranges::binary_search(list, id, {}, &kcv::detail::api_mst_slotitem_value_t::api_id);
}

}  // namespace kcv

#endif  // KCVERIFY_CONSTANTS_EQUIPMENT_HPP_INCLUDED
