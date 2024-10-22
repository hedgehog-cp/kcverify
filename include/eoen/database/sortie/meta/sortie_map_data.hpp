#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_MAP_DATA_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_MAP_DATA_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "eoen/database/sortie/sortie_map_data.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_map_data> {
    using T = kcv::eoen::database::sortie::sortie_map_data;

    static constexpr auto value = object(
        // clang-format off

        "RequiredDefeatedCount", &T::required_defeated_count,
        "MapHPCurrent",          &T::map_hp_current,
        "MapHPMax",              &T::map_hp_max

        // clang-format on
    );
};

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_MAP_DATA_HPP_INCLUDED
