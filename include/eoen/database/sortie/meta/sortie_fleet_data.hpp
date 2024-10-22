#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_FLEET_DATA_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_FLEET_DATA_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "eoen/database/sortie/sortie_fleet_data.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_fleet_data> {
    using T = kcv::eoen::database::sortie::sortie_fleet_data;

    static constexpr auto value = object(
        // clang-format off

        "FleetId",            &T::fleet_id,
        "NodeSupportFleetId", &T::node_support_fleet_id,
        "BossSupportFleetId", &T::boss_support_fleet_id,
        "CombinedFlag",       &T::combined_flag,
        "Fleets",             &T::fleets,
        "AirBases",           &T::air_bases

        // clang-format on
    );
};

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_FLEET_DATA_HPP_INCLUDED
