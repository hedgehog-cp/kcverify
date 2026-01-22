#ifndef KCV_CORE_CONSTANTS_EQUIPMENT_HPP_INCLUDED
#define KCV_CORE_CONSTANTS_EQUIPMENT_HPP_INCLUDED

// std
#include <algorithm>
#include <cstddef>
#include <string_view>
#include <type_traits>

// kcv
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"
#include "kcv/std_ext/exception.hpp"

namespace kcv {
namespace detail {

/// @brief コンパイル時装備マスタ.
struct api_mst_slotitem_value_t final {
    /// @brief .incファイルおよびその生成ファイルがkcv::kcsapi::equipment_idに依存しないようにコンストラクタを定義する.
    consteval api_mst_slotitem_value_t(std::underlying_type_t<kcv::kcsapi::equipment_id> api_id, const char* api_name)
        : api_id{api_id}
        , api_name{api_name} {}

    /// @brief 装備ID.
    kcv::kcsapi::equipment_id api_id;

    /// @brief 艦名.
    std::string_view api_name;
};

/// @brief コンパイル時装備マスタ. このコンパイル時定数は実行時に持ち込まない.
inline constexpr api_mst_slotitem_value_t api_mst_slotitem[] = {
#include "kcv/core/constants/equipment.hpp.inc"
};

static_assert(std::ranges::is_sorted(api_mst_slotitem, {}, &api_mst_slotitem_value_t::api_id));

}  // namespace detail
}  // namespace kcv

namespace kcv {

/// @brief 装備名から装備IDを取得する.
consteval auto equipment_id(std::string_view name) -> kcv::kcsapi::equipment_id {
    for (const auto& [api_id, api_name] : kcv::detail::api_mst_slotitem) {
        if (api_name == name) {
            return api_id;
        }
    }

    throw kcv::exception{std::format("equipment id is not uniquely determined. [name = {}]", name)};
}

inline namespace literals {
inline namespace equipment_literals {

/// @brief 文字列リテラルから装備IDを取得する.
consteval auto operator""_id(const char* str, std::size_t size) -> kcv::kcsapi::equipment_id {
    return equipment_id(std::string_view{str, size});
}

}  // namespace equipment_literals
}  // namespace literals
}  // namespace kcv

#endif  // KCV_CORE_CONSTANTS_EQUIPMENT_HPP_INCLUDED
