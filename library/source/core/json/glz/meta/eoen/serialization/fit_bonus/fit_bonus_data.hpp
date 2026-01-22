#ifndef KCV_CORE_JSON_GLZ_META_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_DATA_HPP_INCLUDED
#define KCV_CORE_JSON_GLZ_META_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_DATA_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "kcv/external/eoen/serialization/fit_bonus/fit_bonus_data.hpp"

template <>
struct glz::meta<kcv::eoen::serialization::fit_bonus::fit_bonus_data> final {
    using T = kcv::eoen::serialization::fit_bonus::fit_bonus_data;

    static constexpr auto value = glz::object(
        // clang-format off

        "shipS",           &T::original_id,
        "shipClass",       &T::ship_class,
        "shipNationality", &T::nationality,
        "shipType",        &T::ship_type,
        "shipX",           &T::ship_id,
        "requires",        &T::requires_id, 
        "requiresLevel",   &T::requires_level,
        "requiresNum",     &T::requires_num,
        "requiresType",    &T::requires_type,
        "requiresNumType", &T::requires_num_type,
                           &T::level,
                           &T::num,
                           &T::bonus,
        "bonusAR",         &T::bonus_if_anti_air_radar,
        "bonusAccR",       &T::bonus_if_accuracy_radar,
        "bonusSR",         &T::bonus_if_surface_radar

        // clang-format on
    );
};

#endif  // KCV_CORE_JSON_GLZ_META_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_DATA_HPP_INCLUDED
