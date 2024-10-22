#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_META_SORITE_AIR_BASE_SQUADRON_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_META_SORITE_AIR_BASE_SQUADRON_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "eoen/database/sortie/sorite_air_base_squadron.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sorite_air_base_squadron> {
    using T = kcv::eoen::database::sortie::sorite_air_base_squadron;

    static constexpr auto value = object(
        // clang-format off

        "AircraftCurrent", &T::aircraft_current,
        "State",           &T::state,
        "Condition",       &T::condition,
        "EquipmentSlot",   &T::equipment_slot

        // clang-format on
    );
};

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_META_SORITE_AIR_BASE_SQUADRON_HPP_INCLUDED
