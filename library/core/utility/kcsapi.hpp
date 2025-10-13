#ifndef KCVERIFY_CORE_UTILITY_KCSAPI_HPP_INCLUDED
#define KCVERIFY_CORE_UTILITY_KCSAPI_HPP_INCLUDED

#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"
#include "models/kcsapi/types/enum/nationality.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"
#include "models/kcsapi/types/number.hpp"

namespace kcv {

/// @brief 艦船IDに一致する艦船マスタを二分探索で取得する.
/// @param api_mst_ship 艦船マスタ.
/// @param id 艦船ID.
/// @return 艦船IDに一致する艦船マスタ.
auto find_mst(const kcv::kcsapi::api_mst_ship& api_mst_ship, kcv::kcsapi::ship_id id)
    -> const kcv::kcsapi::api_mst_ship::value_type&;

/// @brief 装備IDに一致する装備マスタを二分探索で取得する.
/// @param api_mst_ship 装備マスタ.
/// @param id 装備ID.
/// @return 装備IDに一致する装備マスタ.
auto find_mst(const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem, kcv::kcsapi::equipment_id id)
    -> const kcv::kcsapi::api_mst_slotitem::value_type&;

/// @brief 艦娘の未改造IDを取得する. 存在しなければ例外を送出する.
/// @param api_mst_ship 艦船マスタ.
/// @param mst 艦船マスタ.
/// @return 艦娘の未改造ID.
auto base_id(const kcv::kcsapi::api_mst_ship& api_mst_ship, const kcv::kcsapi::api_mst_ship::value_type& mst)
    -> kcv::kcsapi::ship_id;

/// @brief 艦娘の国籍を返す.
/// @param mst 艦船マスタ.
/// @return 国籍.
auto nationality(const kcv::kcsapi::api_mst_ship::value_type& mst) noexcept -> kcv::kcsapi::nationality;

/// @brief 数値にする.
auto to_integer(const kcv::kcsapi::number& v) noexcept -> std::optional<std::int32_t>;

/// @brief 装備IDにする.
auto to_equipment_id(const kcv::kcsapi::number& v) noexcept -> kcv::kcsapi::equipment_id;

}  // namespace kcv

#endif  // KCVERIFY_CORE_UTILITY_KCSAPI_HPP_INCLUDED
