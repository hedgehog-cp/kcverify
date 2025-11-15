#ifndef KCVERIFY_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_MAP_DATA_HPP_INCLUDED
#define KCVERIFY_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_MAP_DATA_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "models/eoen/database/sortie/sortie_map_data.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_map_data> final {
    using T = kcv::eoen::database::sortie::sortie_map_data;

    static constexpr auto value = glz::object(
        // clang-format off
        
        "RequiredDefeatedCount", &T::required_defeat_count,
        "MapHPCurrent",          &T::map_hp_current,
        "MapHPMax",              &T::map_hp_max

        // clang-format on
    );
};

#endif  // KCVERIFY_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_MAP_DATA_HPP_INCLUDED
