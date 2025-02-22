#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_AIR_BASE_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_AIR_BASE_HPP_INCLUDED

// std
#include <cstdint>
#include <string>
#include <vector>

// kcv
#include "eoen/database/sortie/sortie_air_base_squadron.hpp"
#include "kcsapi/types/enum/air_base_action.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `AirBase` の要素型.
/// @brief namespace ElectronicObserver.Database.Sortie; public class SortieAirBase { ... }
/// @see ElectronicObserver/Database/Sortie/SortieAirBase.cs
struct sortie_air_base final {
    /// @brief 航空隊名.
    std::string name;

    /// @brief 所属海域ID.
    std::int32_t map_area_id;

    std::int32_t air_corps_id;

    /// @brief 行動指示.
    kcv::kcsapi::air_base_action action_kind;

    /// @brief 戦闘行動半径.
    std::int32_t base_distance;

    /// @brief 偵察機などによる戦闘行動半径のボーナス.
    std::int32_t bonus_distance;

    /// @brief 第N中隊.
    std::vector<kcv::eoen::database::sortie::sortie_air_base_squadron> squadrons;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_AIR_BASE_HPP_INCLUDED
