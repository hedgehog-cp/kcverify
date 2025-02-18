#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_HPP_INCLUDED

// std
#include <cstdint>

// kcv
#include "kcsapi/types/enum/equipment_id.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `Equipment`.
/// @brief namespace ElectronicObserver.Database.Sortie; public class SortieEquipment { ... }
/// @see ElectronicObserver/Database/Sortie/SortieAirBaseSquadron.cs
struct sortie_equipment final {
    /// @brief 装備ID
    kcv::kcsapi::equipment_id id;

    /// @brief 改修値
    std::int32_t level;

    /// @brief 熟練度
    std::int32_t aircraft_level;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_EQUIPMENT_HPP_INCLUDED
