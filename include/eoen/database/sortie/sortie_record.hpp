#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_RECORD_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_RECORD_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "eoen/database/kancolle_api/api_files.hpp"
#include "eoen/database/sortie/sortie_fleet_data.hpp"
#include "eoen/database/sortie/sortie_map_data.hpp"
// #include "eoen/database/sortie/calculated_sortie_cost.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される配列の要素型.
/// /0
/// @see namespace ElectronicObserver.Database.Sortie; public class SortieRecord { ... }
struct sortie_record final {
    /// @note 74式ENがint型で定義しており, C#のint型は32bit保証だが, C++のint型は16bit以上保証であるため.
    std::int32_t id;
    int version;
    int world;
    int map;
    std::vector<kancolle_api::api_files> api_files;
    sortie_fleet_data fleet_data;
    std::optional<sortie_fleet_data> fleet_after_sortie_data;
    sortie_map_data map_data;

    // 未使用につきskip.
    // calculated_sortie_cost_t calculated_sortie_cost;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_SORTIE_RECORD_HPP_INCLUDED
