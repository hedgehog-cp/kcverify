#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_FLEET_DATA_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_FLEET_DATA_HPP_INCLUDED

// std
#include <optional>
#include <vector>

// kcv
#include "eoen/database/sortie/sortie_air_base.hpp"
#include "eoen/database/sortie/sortie_fleet.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `FleetData` または `FleetAfterSortieData`.
/// /0/FleetData
/// /0/FleetAfterSortieData
/// @see namespace ElectronicObserver.Database.Sortie; public class SortieFleetData { ... }
struct sortie_fleet_data final {
    int fleet_id;

    /// @brief 0 = none, 1~4 = fleets
    int node_support_fleet_id;

    int boss_support_fleet_id;

    int combined_flag;

    std::vector<std::optional<sortie_fleet>> fleets;

    std::vector<sortie_air_base> air_bases;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_FLEET_DATA_HPP_INCLUDED
