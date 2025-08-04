#ifndef KCVERIFY_CORE_CONSTANTS_EQUIPMENT_HPP_INCLUDED
#define KCVERIFY_CORE_CONSTANTS_EQUIPMENT_HPP_INCLUDED

// std
#include <cstddef>
#include <string_view>
#include <type_traits>

// kcv
#include "extensions/exception.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"

namespace kcv {
namespace detail {

#include "core/constants/equipment.hpp.inc"

}  // namespace detail
}  // namespace kcv

namespace kcv {

/// @brief 装備名から装備IDを取得する.
consteval auto equipment_id(std::string_view name) -> kcv::kcsapi::equipment_id {
    for (const auto &[api_id, api_name] : kcv::detail::api_mst_slotitem) {
        if (api_name == name) {
            return api_id;
        }
    }

    throw kcv::exception{std::format("equipment id is not uniquely determined. [name = {}]", name)};
}

inline namespace literals {
inline namespace equipment_literals {

/// @brief 文字列リテラルから装備IDを取得する.
consteval auto operator""_id(const char *str, std::size_t size) -> kcv::kcsapi::equipment_id {
    return equipment_id(std::string_view{str, size});
}

}  // namespace equipment_literals
}  // namespace literals
}  // namespace kcv

namespace kcv {

/// @brief 電探であるかを検証する.
bool is_radar(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept;

/// @brief 対空電探であるかを検証する.
bool is_anti_air_radar(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept;

/// @brief 水上電探であるかを検証する.
bool is_surface_radar(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept;

/// @brief 命中電探であるかを検証する.
bool is_accuracy_radar(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept;

/// @brief 夜間作戦航空要員であるかを検証する.
bool is_night_operation_aviation_personnel(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept;

/// @brief 艦攻Swordfishであるかを検証する.
bool is_cb_swordfish(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept;

/// @brief 夜間機であるかを検証する.
bool is_night_plane(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept;

/// @brief 準夜間機であるかを検証する.
bool is_semi_night_plane(const kcv::kcsapi::api_mst_slotitem_value_t &mst) noexcept;

}  // namespace kcv

#endif  // KCVERIFY_CORE_CONSTANTS_EQUIPMENT_HPP_INCLUDED
