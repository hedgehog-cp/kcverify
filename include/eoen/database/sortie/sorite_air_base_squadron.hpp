#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORITE_AIR_BASE_SQUADRON_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORITE_AIR_BASE_SQUADRON_HPP_INCLUDED

// std
#include <optional>

// kcv
#include "eoen/database/sortie/sortie_equipment_slot.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `Squadrons` の要素型.
/// /0/FleetData/AirBases/0/Squadrons/0
/// /0/FleetAfterSortieData/AirBases/0/Squadrons/0
/// @see namespace ElectronicObserver.Database.Sortie; public class SortieAirBaseSquadron { ... }
struct sorite_air_base_squadron final {
    std::optional<int> aircraft_current;
    int state;
    int condition;
    sortie_equipment_slot equipment_slot;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORITE_AIR_BASE_SQUADRON_HPP_INCLUDED
