#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_FLEET_DATA_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_FLEET_DATA_HPP_INCLUDED

// std
#include <cstdint>
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
/// @brief namespace ElectronicObserver.Database.Sortie; public class SortieFleetData { ... }
/// @see ElectronicObserver/Database/Sortie/SortieFleetData.cs
struct sortie_fleet_data final {
    /// @brief 1 or 2 or 3 or 4.
    std::int32_t fleet_id;

    /// @brief 前衛支援. 0 = none, 1~4 = fleets
    std::int32_t node_support_fleet_id;

    /// @brief 艦隊決戦支援.
    std::int32_t boss_support_fleet_id;

    /// @see https://github.com/ElectronicObserverEN/ElectronicObserver/blob/main/ElectronicObserverTypes/FleetType.cs
    std::int32_t combined_flag;

    /// @brief 第1艦隊~第4艦隊.
    std::vector<std::optional<kcv::eoen::database::sortie::sortie_fleet>> fleets;

    /// @brief 第1基地航空隊~第3基地航空隊.
    std::vector<kcv::eoen::database::sortie::sortie_air_base> air_bases;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_FLEET_DATA_HPP_INCLUDED
