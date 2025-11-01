#ifndef KCVERIFY_CORE_ATTRIBUTES_EQUIPMENT_HPP_INCLUDED
#define KCVERIFY_CORE_ATTRIBUTES_EQUIPMENT_HPP_INCLUDED

#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"

namespace kcv {

/// @brief 電探であるかを検証する.
bool is_radar(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 対空電探であるかを検証する.
bool is_anti_air_radar(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 水上電探であるかを検証する.
bool is_surface_radar(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 命中電探であるかを検証する.
bool is_accuracy_radar(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 夜間作戦航空要員であるかを検証する.
bool is_night_operation_aviation_personnel(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 艦攻Swordfishであるかを検証する.
bool is_cb_swordfish(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 夜間機であるかを検証する.
bool is_night_plane(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 準夜間機であるかを検証する.
bool is_semi_night_plane(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

}  // namespace kcv

#endif  // KCVERIFY_CORE_ATTRIBUTES_EQUIPMENT_HPP_INCLUDED
