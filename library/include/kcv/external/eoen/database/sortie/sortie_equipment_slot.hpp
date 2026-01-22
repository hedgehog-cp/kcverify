#ifndef KCV_EXTERNAL_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_SLOT_HPP_INCLUDED
#define KCV_EXTERNAL_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_SLOT_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>

// kcv
#include "kcv/external/eoen/database/sortie/sortie_equipment.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `EquipmentSlot` の要素型.
/// @brief namespace ElectronicObserver.Database.Sortie; public class SortieEquipmentSlot { ... }
/// @see ElectronicObserver/Database/Sortie/SortieEquipmentSlot.cs
struct sortie_equipment_slot final {
    /// @brief 現在搭載数
    std::int32_t aircraft_current;

    /// @brief 最大搭載数
    std::int32_t aircraft_max;

    /// @brief 装備
    std::optional<kcv::eoen::database::sortie::sortie_equipment> equipment;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCV_EXTERNAL_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_SLOT_HPP_INCLUDED
