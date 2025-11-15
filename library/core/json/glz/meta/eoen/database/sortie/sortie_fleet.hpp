#ifndef KCVERIFY_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_FLEET_HPP_INCLUDED
#define KCVERIFY_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_FLEET_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "models/eoen/database/sortie/sortie_fleet.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_fleet> final {
    using T = kcv::eoen::database::sortie::sortie_fleet;

    static constexpr auto value = glz::object(
        // clang-format off

        "Name",  &T::name,
        "Ships", &T::ships

        // clang-format on
    );
};

#endif  // KCVERIFY_CORE_JSON_GLZ_META_EOEN_DATABASE_SORTIE_SORTIE_FLEET_HPP_INCLUDED
