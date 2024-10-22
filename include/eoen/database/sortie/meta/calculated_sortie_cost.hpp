#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_META_CALCULATED_SORTIE_COST_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_META_CALCULATED_SORTIE_COST_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "eoen/database/sortie/calculated_sortie_cost.hpp"

template <>
struct glz::meta<kcv::eoen::database::sortie::calculated_sortie_cost> {
    using T = kcv::eoen::database::sortie::calculated_sortie_cost;

    static constexpr auto value = object(
        // clang-format off

        "SortieFleetSupplyCost",  &T::sortie_fleet_supply_cost,
        "SortieFleetRepairCost",  &T::sortie_fleet_repair_cost,
        "NodeSupportSupplyCost",  &T::node_support_supply_cost,
        "BossSupportSupplyCost",  &T::boss_support_supply_cost,
        "TotalAirBaseSortieCost", &T::total_air_base_sortie_cost,
        "TotalAirBaseSupplyCost", &T::total_air_base_supply_cost

        // clang-format on
    );
};

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_META_CALCULATED_SORTIE_COST_HPP_INCLUDED
