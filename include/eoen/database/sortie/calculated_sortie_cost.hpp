#ifndef KCVERIFY_EOEN_DATABASE_SORTIE_CALCULATED_SORTIE_COST_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_SORTIE_CALCULATED_SORTIE_COST_HPP_INCLUDED

#include <cstddef>
#include <optional>

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `CalculatedSortieCost`.
/// /0/CalculatedSortieCost
/// @see namespace ElectronicObserver.Database.Sortie; public class CalculatedSortieCost { ... }
/// @note この型は使用されていません.
struct calculated_sortie_cost final {
    std::optional<std::nullptr_t> sortie_fleet_supply_cost;
    std::optional<std::nullptr_t> sortie_fleet_repair_cost;
    std::optional<std::nullptr_t> node_support_supply_cost;
    std::optional<std::nullptr_t> boss_support_supply_cost;
    std::optional<std::nullptr_t> total_air_base_sortie_cost;
    std::optional<std::nullptr_t> total_air_base_supply_cost;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_SORTIE_CALCULATED_SORTIE_COST_HPP_INCLUDED
