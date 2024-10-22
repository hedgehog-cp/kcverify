#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_MAP_DATA_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_MAP_DATA_HPP_INCLUDED

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `MapData`.
/// /0/MapData
/// @see namespace ElectronicObserver.Database.Sortie; public class SortieMapData { ... }
struct sortie_map_data final {
    int required_defeated_count;
    int map_hp_current;
    int map_hp_max;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_MAP_DATA_HPP_INCLUDED
