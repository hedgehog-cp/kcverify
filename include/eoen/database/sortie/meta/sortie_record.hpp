#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_RECORD_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_RECORD_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "eoen/database/sortie/sortie_record.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_record_t> {
    using T = kcv::eoen::database::sortie::sortie_record_t;

    static constexpr auto value = object(
        // clang-format off

        "Id",                   &T::id,
        "Version",              &T::version,
        "World",                &T::world,
        "Map",                  &T::map,
        "ApiFiles",             &T::api_files,
        "FleetData",            &T::fleet_data,
        "FleetAfterSortieData", &T::fleet_after_sortie_data,
        "MapData",              &T::map_data,
        "CalculatedSortieCost", skip{}

        // clang-format on
    );
};

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_RECORD_HPP_INCLUDED
