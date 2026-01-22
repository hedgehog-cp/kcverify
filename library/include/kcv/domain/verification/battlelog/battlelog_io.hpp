#ifndef KCV_DOMAIN_VERIFICATION_BATTLELOG_BATTLELOG_IO_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_BATTLELOG_BATTLELOG_IO_HPP_INCLUDED

// std
#include <filesystem>

// kcv
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/external/eoen/database/sortie/sortie_record.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_ship.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"

namespace kcv {

/// @brief 74式ENの出撃詳細からbattlelogを生成する.
/// @param sortie_record 74式ENの出撃詳細.
/// @param api_mst_ship 艦船マスタ.
/// @param api_mst_slotitem 装備マスタ.
/// @return battlelog.
/// @see ElectronicObserver/Window/Tools/SortieRecordViewer/DataExport/DataExportHelper.cs
/// @todo 戻り値のコンテナ型を検討する. push_backの再配置コストが大きい?
void generate_battlelog(
    kcv::battlelogs_t& battlelogs,
    const kcv::eoen::database::sortie::sortie_record& sortie_record,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
);

/// @brief 赤仮.csvでbattlelogを書き出す.
void write_akakari(
    const kcv::battlelogs_t& battlelogs,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::filesystem::path& fname
);

}  // namespace kcv

#endif  // KCV_DOMAIN_VERIFICATION_BATTLELOG_BATTLELOG_IO_HPP_INCLUDED
