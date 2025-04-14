#ifndef KCVERIFY_CORE_ATTRIBUTES_EQUIPMENT_HPP_INCLUDED
#define KCVERIFY_CORE_ATTRIBUTES_EQUIPMENT_HPP_INCLUDED

// std
#include <array>
#include <stdexcept>
#include <string_view>
#include <utility>

// kcv
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/api_type.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"

namespace kcv {
namespace detail {

#include "core/constants/equipment.hpp.inc"

}  // namespace detail
}  // namespace kcv

namespace kcv {

consteval auto equipment_id(std::string_view name) -> kcv::kcsapi::equipment_id {
    for (const auto &[api_id, api_name] : kcv::detail::api_mst_slotitem) {
        if (name == api_name) {
            return api_id;
        }
    }

    throw std::invalid_argument{"equipment id not found."};
}

inline namespace literals {
inline namespace equipment_literals {

consteval auto operator""_id(const char *str, std::size_t size) -> kcv::kcsapi::equipment_id {
    const auto name = std::string_view{str, size};
    return kcv::equipment_id(name);
}

}  // namespace equipment_literals
}  // namespace literals
}  // namespace kcv

namespace kcv {

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
        using kcv::literals::equipment_literals::operator""_id;
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
        using kcv::literals::equipment_literals::operator""_id;
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
        using kcv::literals::equipment_literals::operator""_id;
        case "零戦62型(爆戦/岩井隊)"_id:
        case "彗星一二型(三一号光電管爆弾搭載機)"_id:
            return true;

        default:
            return false;
    }
}

}  // namespace kcv

#endif  // KCVERIFY_CORE_ATTRIBUTES_EQUIPMENT_HPP_INCLUDED
