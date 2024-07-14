#ifndef KCVERIFY_META_EQUIPMENTS_HPP_INCLUDED
#define KCVERIFY_META_EQUIPMENTS_HPP_INCLUDED

#include "master/equipment/convert.hpp"
#include "master/equipment/equipment.hpp"

namespace kcv {

constexpr bool is_night_operation_aviation_personnel(const equipment_t &equipment) noexcept {
    switch (equipment.id()) {
        using literals::equipment_literals::operator""_id;
        case "夜間作戦航空要員"_id:
        case "夜間作戦航空要員+熟練甲板員"_id:
            return true;
        default:
            return false;
    }
}

constexpr bool is_cb_swordfish(const equipment_t &equipment) noexcept {
    switch (equipment.id()) {
        using literals::equipment_literals::operator""_id;
        case "Swordfish"_id:
        case "Swordfish Mk.II(熟練)"_id:
        case "Swordfish Mk.III(熟練)"_id:
            return true;
        default:
            return false;
    }
}

constexpr bool is_night_plane(const equipment_t &equipment) noexcept {
    switch (equipment.icon()) {
        using enum icon_t;
        case night_fighter:
        case night_attacker:
            return true;
        default:
            return false;
    }
}

constexpr bool is_semi_night_plane(const equipment_t &equipment) noexcept {
    switch (equipment.id()) {
        using literals::equipment_literals::operator""_id;
        case "零戦62型(爆戦/岩井隊)"_id:
        case "彗星一二型(三一号光電管爆弾搭載機)"_id:
            return true;
        default:
            return false;
    }
}

}  // namespace kcv

#endif  // KCVERIFY_META_EQUIPMENTS_HPP_INCLUDED
