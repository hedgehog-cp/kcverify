#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_SLOT_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_SLOT_HPP_INCLUDED

// std
#include <optional>

// kcv
#include "eoen/database/sortie/sortie_equipment.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `EquipmentSlot` の要素型.
/// /0/FleetData/Fleets/0/Ships/0/EquipmentSlots/0
/// /0/FleetData/Fleets/0/Ships/0/ExpansionSlot
/// /0/FleetAfterSortieData/Fleets/0/Ships/0/EquipmentSlots/0
/// /0/FleetAfterSortieData/Fleets/0/Ships/0/ExpansionSlot
/// @see namespace ElectronicObserver.Database.Sortie; public class SortieEquipmentSlot { ... }
struct sortie_equipment_slot final {
    /// @brief 現在搭載数
    int aircraft_current;

    /// @brief 最大搭載数
    int aircraft_max;

    /// @brief 装備
    std::optional<database::sortie::sortie_equipment> equipment;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_SLOT_HPP_INCLUDED
