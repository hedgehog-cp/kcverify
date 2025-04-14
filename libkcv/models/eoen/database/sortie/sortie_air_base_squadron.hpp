#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_AIR_BASE_SQUADRON_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_AIR_BASE_SQUADRON_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>

// kcv
#include "models/eoen/database/sortie/sortie_equipment_slot.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `Squadrons` の要素型.
/// @brief namespace ElectronicObserver.Database.Sortie; public class SortieAirBaseSquadron { ... }
/// @see ElectronicObserver/Database/Sortie/SortieAirBaseSquadron.cs
struct sortie_air_base_squadron final {
    /// @brief 現在搭載数.
    std::optional<std::int32_t> aircraft_current;

    /// @brief 0=未配属, 1=配属済み, 2=配置転換中.
    std::int32_t state;

    /// @brief 疲労度. 1=通常, 2=黄疲労, 3=赤疲労. 未配属なら存在しない.
    std::int32_t condition;

    /// @brief 装備スロット.
    kcv::eoen::database::sortie::sortie_equipment_slot equipment_slot;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_AIR_BASE_SQUADRON_HPP_INCLUDED
