#ifndef KCVERIFY_META_SHIPS_HPP_INCLUDED
#define KCVERIFY_META_SHIPS_HPP_INCLUDED

#include "master/ship/convert.hpp"
#include "master/ship/ship.hpp"

namespace kcv {

constexpr bool is_submarine(const ship_t &ship) noexcept {
    switch (ship.stype()) {
        using enum stype_t;
        case ss:
        case ssv:
            return true;
        default:
            return false;
    }
}

constexpr bool is_aircraft_carrier(const ship_t &ship) noexcept {
    switch (ship.stype()) {
        using enum stype_t;
        case cvl:
        case cv:
        case cvb:
            return true;
        default:
            return false;
    }
}

constexpr bool is_night_operation_aircraft_carrier(const ship_t &ship) noexcept {
    switch (ship.id()) {
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

constexpr bool is_night_shellable_aircraft_carrier(const ship_t &ship) noexcept {
    switch (ship.id()) {
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

constexpr bool is_ark_royal(const ship_t &ship) noexcept {
    switch (ship.id()) {
        using literals::ship_literals::operator""_id;
        case "Ark Royal"_id:
        case "Ark Royal改"_id:
            return true;
        default:
            return false;
    }
}

}  // namespace kcv

#endif  // KCVERIFY_META_SHIPS_HPP_INCLUDED
