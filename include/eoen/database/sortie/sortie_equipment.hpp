#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_HPP_INCLUDED

#include "kcsapi/types/enum/equipment_id.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `Equipment`.
/// /0/FleetData/Fleets/0/Ships/0/EquipmentSlots/0/Equipment
/// /0/FleetData/Fleets/0/Ships/0/ExpansionSlot/Equipment
/// /0/FleetData/AirBases/0/Squadrons/0/Equipment
/// /0/FleetAfterSortieData/Fleets/0/Ships/0/EquipmentSlots/0/Equipment
/// /0/FleetAfterSortieData/Fleets/0/Ships/0/ExpansionSlot/Equipment
/// /0/FleetAfterSortieData/AirBases/0/Squadrons/0/Equipment
/// @brief namespace ElectronicObserver.Database.Sortie; public class SortieEquipment { ... }
struct sortie_equipment final {
    /// @brief 装備ID
    kcsapi::equipment_id id;

    /// @brief 改修値
    int level;

    /// @brief 熟練度
    int aircraft_level;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_HPP_INCLUDED
