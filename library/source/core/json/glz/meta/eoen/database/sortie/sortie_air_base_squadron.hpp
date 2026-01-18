#ifndef KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_AIR_BASE_SQUADRON_HPP_INCLUDED
#define KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_AIR_BASE_SQUADRON_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "kcv/external/eoen/database/sortie/sortie_air_base_squadron.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_air_base_squadron> final {
    using T = kcv::eoen::database::sortie::sortie_air_base_squadron;

    static constexpr auto value = glz::object(
        // clang-format off

        "AircraftCurrent", &T::aircraft_current,
        "State",           &T::state,
        "Condition",       &T::condition,
        "EquipmentSlot",   &T::equipment_slot

        // clang-format on
    );
};

#endif  // KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_AIR_BASE_SQUADRON_HPP_INCLUDED
