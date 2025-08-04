#ifndef KCVERIFY_MODELS_EOEN_DATABASE_SORTIE_SORTIE_RECORD_HPP_INCLUDED
#define KCVERIFY_MODELS_EOEN_DATABASE_SORTIE_SORTIE_RECORD_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "models/eoen/database/kancolle_api/api_files.hpp"
#include "models/eoen/database/sortie/sortie_fleet_data.hpp"
#include "models/eoen/database/sortie/sortie_map_data.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace sortie {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される配列の要素型.
/// @brief namespace ElectronicObserver.Database.Sortie; public class SortieRecord { ... }
/// @see ElectronicObserver/Database/Sortie/SortieRecord.cs
struct sortie_record final {
    /// @brief 74式ENの何某かの管理用ID.
    std::int32_t id;

    /// @brief 74式ENの何某かの管理用Version.
    std::int32_t version;

    /// @brief 海域. #5-3-Pに対する5.
    std::int32_t world;

    /// @brief 海域. #5-3-Pに対する3.
    std::int32_t map;

    /// @brief この出撃中に送受信したAPI
    std::vector<kcv::eoen::database::kancolle_api::api_files> api_files;

    /// @brief 出撃前艦隊データ.
    kcv::eoen::database::sortie::sortie_fleet_data fleet_data;

    /// @brief 出撃後艦隊データ.
    std::optional<kcv::eoen::database::sortie::sortie_fleet_data> fleet_after_sortie_data;

    /// @brief 海域攻略進捗データ.
    kcv::eoen::database::sortie::sortie_map_data map_data;
};

}  // namespace sortie
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_MODELS_EOEN_DATABASE_SORTIE_SORTIE_RECORD_HPP_INCLUDED
