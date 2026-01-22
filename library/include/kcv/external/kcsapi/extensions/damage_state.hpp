#ifndef KCV_EXTERNAL_KCSAPI_EXTENSIONS_DAMAGE_STATE_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_EXTENSIONS_DAMAGE_STATE_HPP_INCLUDED

#include <cstdint>
#include <string_view>

namespace kcv {

/// @brief 損傷状態.
enum class damage_state {
    /// @brief 小破未満.
    healthy,

    /// @brief 小破.
    light,

    /// @brief 中破.
    medium,

    /// @brief 大破.
    heavy,

    /// @brief 轟沈.
    sunk,
};

/// @brief 耐久値を損傷状態にする.
constexpr auto to_damage_state(std::int32_t hp, std::int32_t maxhp) noexcept -> damage_state {
    const double ratio = static_cast<double>(hp) / maxhp;
    if (ratio > 0.75) {
        return damage_state::healthy;
    } else if (ratio > 0.5) {
        return damage_state::light;
    } else if (ratio > 0.25) {
        return damage_state::medium;
    } else if (ratio > 0) {
        return damage_state::heavy;
    } else {
        return damage_state::sunk;
    }
}

/// @brief 損傷状態を文字列に変換する.
constexpr auto to_string(damage_state v) noexcept -> std::string_view {
    switch (v) {
        case kcv::damage_state::healthy:
            return "小破未満";

        case kcv::damage_state::light:
            return "小破";

        case kcv::damage_state::medium:
            return "中破";

        case kcv::damage_state::heavy:
            return "大破";

        case kcv::damage_state::sunk:
            return "轟沈";
    }

    return "(未知の損傷状態)";
}

}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_EXTENSIONS_DAMAGE_STATE_HPP_INCLUDED
