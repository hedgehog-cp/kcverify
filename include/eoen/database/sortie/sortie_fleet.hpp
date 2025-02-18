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
/// @brief namespace ElectronicObserver.Database.Sortie; public class SortieFleet { ... }
/// @see ElectronicObserver/Database/Sortie/SortieFleet.cs
struct sortie_fleet final {
    /// @brief 艦隊名.
    std::string name;

    /// @brief 艦船.
    std::vector<kcv::eoen::database::sortie::sortie_ship> ships;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_FLEET_HPP_INCLUDED
