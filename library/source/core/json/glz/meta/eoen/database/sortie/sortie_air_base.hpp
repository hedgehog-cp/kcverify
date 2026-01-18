#ifndef KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_AIR_BASE_HPP_INCLUDED
#define KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_AIR_BASE_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "kcv/external/eoen/database/sortie/sortie_air_base.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_air_base> final {
    using T = kcv::eoen::database::sortie::sortie_air_base;

    static constexpr auto value = glz::object(
        // clang-format off

        "Name",          &T::name,
        "MapAreaId",     &T::map_area_id,
        "AirCorpsId",    &T::air_corps_id,
        "ActionKind",    &T::action_kind,
        "BaseDistance",  &T::base_distance,
        "BonusDistance", &T::bonus_distance,
        "Squadrons",     &T::squadrons

        // clang-format on
    );
};

#endif  // KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_AIR_BASE_HPP_INCLUDED
