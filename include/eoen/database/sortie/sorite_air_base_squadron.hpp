#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORITE_AIR_BASE_SQUADRON_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORITE_AIR_BASE_SQUADRON_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>

// kcv
#include "eoen/database/sortie/sortie_equipment_slot.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `Squadrons` の要素型.
/// @brief namespace ElectronicObserver.Database.Sortie; public class SortieAirBaseSquadron { ... }
/// @see ElectronicObserver/Database/Sortie/SortieAirBaseSquadron.cs
struct sorite_air_base_squadron final {
    /// @brief 現在搭載数.
    std::optional<std::int32_t> aircraft_current;

    std::int32_t state;
    std::int32_t condition;

    /// @brief 装備スロット.
    kcv::eoen::database::sortie::sortie_equipment_slot equipment_slot;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORITE_AIR_BASE_SQUADRON_HPP_INCLUDED
