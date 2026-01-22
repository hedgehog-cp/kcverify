#ifndef KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_FLEET_DATA_HPP_INCLUDED
#define KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_FLEET_DATA_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "kcv/external/eoen/database/sortie/sortie_fleet_data.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_fleet_data> final {
    using T = kcv::eoen::database::sortie::sortie_fleet_data;

    static constexpr auto value = glz::object(
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

#endif  // KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_FLEET_DATA_HPP_INCLUDED
