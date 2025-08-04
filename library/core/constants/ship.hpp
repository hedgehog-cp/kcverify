#ifndef KCVERIFY_CORE_CONSTANTS_SHIP_HPP_INCLUDED
#define KCVERIFY_CORE_CONSTANTS_SHIP_HPP_INCLUDED

// std
#include <cstddef>
#include <string_view>
#include <type_traits>

// kcv
#include "extensions/exception.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"

namespace kcv {
namespace detail {

#include "core/constants/ship.hpp.inc"

}  // namespace detail
}  // namespace kcv

namespace kcv {

/// @brief 深海棲艦であるかを検証する.
/// @note IDの拡張により変更を要求される. 深海棲艦であるかの検証は, api_sortno == 0; などでも定義できる.
constexpr bool is_abyssal_ship_id(kcv::kcsapi::ship_id id) noexcept {
    return id > kcv::kcsapi::ship_id{1500};
}

/// @brief 艦名から艦船IDを取得する.
/// @throw kcv::exception  宗谷および深海棲艦は, その艦船IDを一意に決定できないため例外を送出する.
consteval auto ship_id(std::string_view name) -> kcv::kcsapi::ship_id {
    if (name == "宗谷") {
        throw kcv::exception{std::format("ship id is not uniquely determined. [name = {}]", name)};
    }

    for (const auto& [api_id, api_name] : kcv::detail::api_mst_ship) {
        if (api_name == name) {
            if (is_abyssal_ship_id(api_id)) {
                throw kcv::exception{std::format("ship id is not uniquely determined. [name = {}]", name)};
            } else {
                return api_id;
            }
        }
    }

    throw kcv::exception{std::format("ship id is not uniquely determined. [name = {}]", name)};
}

inline namespace literals {
inline namespace ship_literals {

/// @brief 文字列リテラルから艦船IDを取得する.
consteval auto operator""_id(const char* str, std::size_t size) -> kcv::kcsapi::ship_id {
    return ship_id(std::string_view{str, size});
}

}  // namespace ship_literals
}  // namespace literals
}  // namespace kcv

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

#endif  // KCVERIFY_CORE_CONSTANTS_SHIP_HPP_INCLUDED
