#ifndef KCVERIFY_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_SHIP_HPP_INCLUDED
#define KCVERIFY_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_SHIP_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "models/eoen/database/sortie/sortie_ship.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_ship> final {
    using T = kcv::eoen::database::sortie::sortie_ship;

    static constexpr auto value = glz::object(
        // clang-format off
        
        "Id",                  &T::id,
        "DropId",              &T::drop_id,
        "Level",               &T::level,
        "Condition",           &T::condition,
        "Kyouka",              &T::kyouka,
        "Fuel",                &T::fuel,
        "Ammo",                &T::ammo,
        "Hp",                  &T::hp,
        "Armor",               &T::armor,
        "Evasion",             &T::evasion,
        "Aircraft",            &T::aircraft,
        "Range",               &T::range,
        "Speed",               &T::speed,
        "Firepower",           &T::firepower,
        "Torpedo",             &T::torpedo,
        "Aa",                  &T::aa,
        "Asw",                 &T::asw,
        "Search",              &T::search,
        "Luck",                &T::luck,
        "EquipmentSlots",      &T::equipment_slots,
        "ExpansionSlot",       &T::expansion_slot,
        "SpecialEffectItems",  &T::special_effect_items

        // clang-format on
    );
};

#endif  // KCVERIFY_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_SHIP_HPP_INCLUDED
