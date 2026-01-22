#ifndef KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_RECORD_HPP_INCLUDED
#define KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_RECORD_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "kcv/external/eoen/database/sortie/sortie_record.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_record> final {
    using T = kcv::eoen::database::sortie::sortie_record;

    static constexpr auto value = glz::object(
        // clang-format off

        "Id",                   &T::id,
        "Version",              &T::version,
        "World",                &T::world,
        "Map",                  &T::map,
        "ApiFiles",             &T::api_files,
        "FleetData",            &T::fleet_data,
        "FleetAfterSortieData", &T::fleet_after_sortie_data,
        "MapData",              &T::map_data,
        "CalculatedSortieCost", glz::skip{}

        // clang-format on
    );
};

#endif  // KCV_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_RECORD_HPP_INCLUDED
