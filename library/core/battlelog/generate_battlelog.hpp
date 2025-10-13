#ifndef KCVERIFY_CORE_BATTLELOG_GENERATE_BATTLELOG_HPP_INCLUDED
#define KCVERIFY_CORE_BATTLELOG_GENERATE_BATTLELOG_HPP_INCLUDED

// std
#include <vector>

// kcv
#include "core/battlelog/battlelog.hpp"
#include "models/eoen/database/sortie/sortie_record.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"

namespace kcv {

/// @brief 74式ENの出撃詳細からbattlelogを生成する.
/// @param api_mst_ship 艦船マスタ.
/// @param api_mst_slotitem 装備マスタ.
/// @param fit_bopnuses 74式EN固有の装備ボーナスオブジェクト.
/// @return battlelog.
/// @see ElectronicObserver/Window/Tools/SortieRecordViewer/DataExport/DataExportHelper.cs
auto generate_battlelog(
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    const kcv::eoen::database::sortie::sortie_record& sortie_record
) -> std::vector<kcv::battlelog>;

}  // namespace kcv

#endif  // KCVERIFY_CORE_BATTLELOG_GENERATE_BATTLELOG_HPP_INCLUDED
