#ifndef KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_SLOT_HPP_INCLUDED
#define KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_SLOT_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "kcv/external/eoen/database/sortie/sortie_equipment_slot.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_equipment_slot> final {
    using T = kcv::eoen::database::sortie::sortie_equipment_slot;

    static constexpr auto value = glz::object(
        // clang-format off

        "AircraftCurrent", &T::aircraft_current,
        "AircraftMax",     &T::aircraft_max,
        "Equipment",       &T::equipment

        // clang-format on
    );
};

#endif  // KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_SLOT_HPP_INCLUDED
