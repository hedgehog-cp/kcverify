#ifndef KCVERIFY_CORE_CONSTANTS_SHIP_HPP_INCLUDED
#define KCVERIFY_CORE_CONSTANTS_SHIP_HPP_INCLUDED

// std
#include <algorithm>
#include <cstddef>
#include <string_view>
#include <type_traits>

// kcv
#include "extensions/exception.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"

namespace kcv {
namespace detail {

/// @brief コンパイル時艦船マスタ.
struct api_mst_ship_value_t final {
    /// @brief .incファイルおよびその生成ファイルがkcv::kcsapi::ship_idに依存しないようにコンストラクタを定義する.
    consteval api_mst_ship_value_t(std::underlying_type_t<kcv::kcsapi::ship_id> api_id, const char* api_name)
        : api_id{api_id}
        , api_name{api_name} {}

    /// @brief 艦船ID.
    kcv::kcsapi::ship_id api_id;

    /// @brief 艦名.
    std::string_view api_name;
};

/// @brief コンパイル時艦船マスタ. このコンパイル時定数は実行時に持ち込まない.
inline constexpr api_mst_ship_value_t api_mst_ship[] = {
#include "core/constants/ship.hpp.inc"
};

static_assert(std::ranges::is_sorted(api_mst_ship, {}, &api_mst_ship_value_t::api_id));

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

#endif  // KCVERIFY_CORE_CONSTANTS_SHIP_HPP_INCLUDED
