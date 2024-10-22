#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_SHIP_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_SHIP_HPP_INCLUDED

// std
#include <optional>
#include <vector>

// kcv
#include "eoen/database/sortie/sortie_equipment_slot.hpp"
#include "kcapi/types/enum/sp_effect_item.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `Ships` の要素型.
/// /0/FleetData/Fleets/0/Ships/0
/// /0/FleetAfterSortieData/Fleets/0/Ships/0
/// @see namespace ElectronicObserver.Database.Sortie; public class SortieShip { ... }
struct sortie_ship final {
    int id;

    /// @brief nullopt for older data.
    std::optional<int> drop_id;

    int level;
    int condition;
    std::vector<int> kyouka;
    int fuel;
    int ammo;
    int hp;

    /// @brief nullopt for older data.
    std::optional<int> armor;

    /// @brief nullopt for older data.
    std::optional<int> evasion;

    /// @brief nullopt for older data.
    std::optional<std::vector<int>> aircraft;

    int range;
    int speed;

    /// @brief nullopt for older data.
    std::optional<int> firepower;

    /// @brief nullopt for older data.
    std::optional<int> torpedo;

    /// @brief nullopt for older data.
    std::optional<int> aa;

    /// @brief nullopt for older data.
    std::optional<int> asw;

    /// @brief nullopt for older data.
    std::optional<int> search;

    /// @brief nullopt for older data.
    std::optional<int> luck;

    std::vector<sortie_equipment_slot> equipment_slots;

    /// @brief null = expansion slot not available.
    std::optional<sortie_equipment_slot> expansion_slot;

    /// @brief nullopt for older data.
    std::optional<std::vector<kcapi::sp_effect_item>> special_effect_items;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_SHIP_HPP_INCLUDED
