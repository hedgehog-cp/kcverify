#ifndef KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_META_FIT_BONUS_DATA_HPP_INCLUDED
#define KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_META_FIT_BONUS_DATA_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "eoen/serialization/fit_bonus/fit_bonus_data.hpp"

template <>
struct glz::meta<kcv::eoen::serialization::fit_bonus::fit_bonus_data> {
    using T = kcv::eoen::serialization::fit_bonus::fit_bonus_data;

    static constexpr auto value = object(
        // clang-format off

        "shipType",        &T::ship_type,
        "level",           &T::level,
        "num",             &T::num,
        "bonus",           &T::bonus,
        "shipX",           &T::ship_id,
        "bonusAR",         &T::air_radar,
        "shipS",           &T::original_id,
        "requires",        &T::requires_id, 
        "requiresLevel",   &T::requires_level,
        "requiresNum",     &T::requires_num,
        "requiresType",    &T::requires_type,
        "requiresNumType", &T::requires_num_type,
        "shipClass",       &T::ship_class,
        "bonusSR",         &T::surface_radar,
        "shipNationality", &T::nationality,
        "bonusAccR",       &T::accuracy_radar

        // clang-format on
    );
};

#endif  // KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_META_FIT_BONUS_DATA_HPP_INCLUDED
