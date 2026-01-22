#ifndef KCV_CORE_CONSTANTS_EQUIPMENT_ATTRIBUTES_HPP_INCLUDED
#define KCV_CORE_CONSTANTS_EQUIPMENT_ATTRIBUTES_HPP_INCLUDED

#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"

namespace kcv {

/// @brief 電探であるかを検証する.
bool is_radar(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 対空電探であるかを検証する.
bool is_anti_air_radar(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 水上電探であるかを検証する.
bool is_surface_radar(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 命中電探であるかを検証する.
bool is_accuracy_radar(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief ソナーであるかを検証する.
bool is_sonor(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 爆雷であるかを検証する.
bool is_depth_charge(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 爆雷投射機であるかを検証する.
bool is_depth_charge_projector(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief シナジー爆雷であるかを検証する.
bool is_synergistic_depth_charge(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 軽巡軽量主砲であるかを検証する.
bool is_cl_fit_main_gun(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 軽巡軽量副砲であるかを検証する.
bool is_cl_fit_secondary_gun(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 軽巡軽量主砲であるかを検証する.
bool is_italian_fit_main_gun(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 夜間作戦航空要員であるかを検証する.
bool is_night_operation_aviation_personnel(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 艦攻Swordfishであるかを検証する.
bool is_cb_swordfish(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 夜間機であるかを検証する.
bool is_night_plane(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

/// @brief 準夜間機であるかを検証する.
// bool is_semi_night_plane(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept;

}  // namespace kcv

#endif  // KCV_CORE_CONSTANTS_EQUIPMENT_ATTRIBUTES_HPP_INCLUDED
