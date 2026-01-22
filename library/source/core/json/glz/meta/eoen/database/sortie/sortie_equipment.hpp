#ifndef KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_HPP_INCLUDED
#define KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "kcv/external/eoen/database/sortie/sortie_equipment.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_equipment> final {
    using T = kcv::eoen::database::sortie::sortie_equipment;

    static constexpr auto value = glz::object(
        // clang-format off

        "Id",            &T::id,
        "Level",         &T::level,
        "AircraftLevel", &T::aircraft_level

        // clang-format on
    );
};

#endif  // KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_HPP_INCLUDED
