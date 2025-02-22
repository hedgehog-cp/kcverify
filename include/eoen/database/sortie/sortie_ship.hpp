#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_SHIP_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_SHIP_HPP_INCLUDED

// std
#include <array>
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "eoen/database/sortie/sortie_equipment_slot.hpp"
#include "kcsapi/types/enum/ship_id.hpp"
#include "kcsapi/types/enum/sp_effect_item.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `Ships` の要素型.
/// @brief namespace ElectronicObserver.Database.Sortie; public class SortieShip { ... }
/// @see ElectronicObserver/Database/Sortie/SortieShip.cs
struct sortie_ship final {
    /// @brief 艦船ID.
    kcv::kcsapi::ship_id id;

    /// @brief 着任順の固有ID.
    /// nullopt for older data.
    std::optional<std::int32_t> drop_id;

    /// @brief レベル.
    std::int32_t level;

    /// @brief 疲労度.
    std::int32_t condition;

    /// @brief 近代化改修. 0=火力, 1=雷装, 2=対空, 3=装甲, 4=運, 5=耐久, 6=対潜.
    std::array<std::int32_t, 7> kyouka;

    /// @brief 搭載燃料.
    std::int32_t fuel;

    /// @brief 搭載弾薬量.
    std::int32_t ammo;

    /// @brief 耐久.
    std::int32_t hp;

    /// @brief 装甲.
    /// nullopt for older data.
    std::optional<std::int32_t> armor;

    /// @brief 回避.
    /// nullopt for older data.
    std::optional<std::int32_t> evasion;

    /// @brief 搭載数.
    /// nullopt for older data.
    std::optional<std::vector<std::int32_t>> aircraft;

    /// @brief 射程.
    std::int32_t range;

    /// @brief 速度.
    std::int32_t speed;

    /// @brief 火力.
    /// nullopt for older data.
    std::optional<std::int32_t> firepower;

    /// @brief 雷装.
    /// nullopt for older data.
    std::optional<std::int32_t> torpedo;

    /// @brief 対空.
    /// nullopt for older data.
    std::optional<std::int32_t> aa;

    /// @brief 対潜.
    /// nullopt for older data.
    std::optional<std::int32_t> asw;

    /// @brief 索敵.
    /// nullopt for older data.
    std::optional<std::int32_t> search;

    /// @brief 運.
    /// nullopt for older data.
    std::optional<std::int32_t> luck;

    /// @brief 装備スロット.
    std::vector<kcv::eoen::database::sortie::sortie_equipment_slot> equipment_slots;

    /// @brief 増設スロット.
    /// null = expansion slot not available.
    std::optional<kcv::eoen::database::sortie::sortie_equipment_slot> expansion_slot;

    /// @brief 特注アイテム.
    /// nullopt for older data.
    std::optional<std::vector<kcv::kcsapi::sp_effect_item>> special_effect_items;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_SHIP_HPP_INCLUDED
