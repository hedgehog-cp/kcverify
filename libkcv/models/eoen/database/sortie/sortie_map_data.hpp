#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_MAP_DATA_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_MAP_DATA_HPP_INCLUDED

#include <cstdint>

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `MapData`.
/// @brief namespace ElectronicObserver.Database.Sortie; public class SortieMapData { ... }
/// @see ElectronicObserver/Database/Sortie/SortieMapData.cs
struct sortie_map_data final {
    /// @brief 攻略に必要な撃破回数.
    std::int32_t required_defeat_count;

    /// @brief 海域HPの現在値.
    std::int32_t map_hp_current;

    /// @brief 海域HPの最大値.
    std::int32_t map_hp_max;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_MAP_DATA_HPP_INCLUDED
