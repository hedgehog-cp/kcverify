#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_AIR_BASE_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_AIR_BASE_HPP_INCLUDED

// std
#include <string>
#include <vector>

// kcv
#include "eoen/database/sortie/sorite_air_base_squadron.hpp"
#include "kcsapi/types/enum/air_base_action.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `AirBase` の要素型.
/// /0/FleetData/AirBases/0
/// /0/FleetAfterSortieData/AirBases/0
/// @see namespace ElectronicObserver.Database.Sortie; public class SortieAirBase { ... }
struct sortie_air_base final {
    std::string name;
    int map_area_id;
    int air_corps_id;
    kcsapi::air_base_action action_kind;
    int base_distance;
    int bonus_distance;
    std::vector<database::sortie::sorite_air_base_squadron> squadrons;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_AIR_BASE_HPP_INCLUDED
