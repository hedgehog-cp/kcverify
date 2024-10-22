#ifndef KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_META_FIT_BONUS_PER_EQUIPMENT_HPP_INCLUDED
#define KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_META_FIT_BONUS_PER_EQUIPMENT_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"

template <>
struct glz::meta<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment> {
    using T = kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment;

    static constexpr auto value = object(
        // clang-format off

        "types",   &T::equipment_types,
        "ids",     &T::equipment_ids,
        "bonuses", &T::bonuses

        // clang-format on
    );
};

#endif  // KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_META_FIT_BONUS_PER_EQUIPMENT_HPP_INCLUDED
