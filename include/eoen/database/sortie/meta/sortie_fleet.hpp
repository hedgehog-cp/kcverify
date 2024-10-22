#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_FLEET_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_FLEET_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "eoen/database/sortie/sortie_fleet.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_fleet> {
    using T = kcv::eoen::database::sortie::sortie_fleet;

    static constexpr auto value = object(
        // clang-format off

        "Name",  &T::name,
        "Ships", &T::ships

        // clang-format on
    );
};

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_META_SORTIE_FLEET_HPP_INCLUDED
