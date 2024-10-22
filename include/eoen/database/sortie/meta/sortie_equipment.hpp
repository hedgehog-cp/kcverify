#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_EQUIPMENT_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_EQUIPMENT_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "eoen/database/sortie/sortie_equipment.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_equipment> {
    using T = kcv::eoen::database::sortie::sortie_equipment;

    static constexpr auto value = object(
        // clang-format off

        "Id",            &T::id,
        "Level",         &T::level,
        "AircraftLevel", &T::aircraft_level

        // clang-format on
    );
};

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_EQUIPMENT_HPP_INCLUDED
