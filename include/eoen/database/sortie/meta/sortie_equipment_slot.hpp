#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_EQUIPMENT_SLOT_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_EQUIPMENT_SLOT_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "eoen/database/sortie/sortie_equipment_slot.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_equipment_slot> {
    using T = kcv::eoen::database::sortie::sortie_equipment_slot;

    static constexpr auto value = object(
        // clang-format off

        "AircraftCurrent", &T::aircraft_current,
        "AircraftMax",     &T::aircraft_max,
        "Equipment",       &T::equipment

        // clang-format on
    );
};

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_EQUIPMENT_SLOT_HPP_INCLUDED
