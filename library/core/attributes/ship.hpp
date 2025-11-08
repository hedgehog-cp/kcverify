#ifndef KCVERIFY_CORE_ATTRIBUTES_SHIP_HPP_INCLUDED
#define KCVERIFY_CORE_ATTRIBUTES_SHIP_HPP_INCLUDED

// kcv
#include "models/kcsapi/api_start2/api_mst_ship.hpp"

namespace kcv {

/// @brief 深海棲艦であるかを検証する.
bool is_abyssal_ship(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept;

/// @brief 陸上型であるかを検証する.
bool is_installation(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept;

/// @brief 砲台小鬼あるいはトーチカであるかを検証する.
bool is_pillbox(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept;

/// @brief 離島棲姫であるかを検証する.
bool is_isolated_island(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept;

/// @brief 港湾棲姫であるかを検証する.
bool is_harbour_summer_princess(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept;

/// @brief ソフトスキンであるかを検証する.
bool is_soft_skin(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept;

/// @brief PT小鬼群であるかを検証する.
bool is_pt_imp(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept;

/// @brief 潜水艦であるかを検証する.
bool is_submarine(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept;

/// @brief 航空母艦であるかを検証する.
bool is_aircraft_carrier(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept;

/// @brief 夜間作戦空母であるかを検証する.
bool is_night_operation_aircraft_carrier(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept;

/// @brief 夜間砲撃可能空母であるかを検証する.
bool is_night_shellable_aircraft_carrier(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept;

/// @brief アークロイヤルであるかを検証する.
bool is_ark_royal(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept;

}  // namespace kcv

#endif  // KCVERIFY_CORE_ATTRIBUTES_SHIP_HPP_INCLUDED
