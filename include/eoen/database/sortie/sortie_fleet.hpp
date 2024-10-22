#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_FLEET_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_FLEET_HPP_INCLUDED

// std
#include <string>
#include <vector>

// kcv
#include "eoen/database/sortie/sortie_ship.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `Fleets` の要素型.
/// /0/FleetData/Fleets/0
/// /0/FleetAfterSortieData/Fleets/0
/// @see namespace ElectronicObserver.Database.Sortie; public class SortieFleet { ... }
struct sortie_fleet final {
    std::string name;
    std::vector<sortie_ship> ships;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_FLEET_HPP_INCLUDED
