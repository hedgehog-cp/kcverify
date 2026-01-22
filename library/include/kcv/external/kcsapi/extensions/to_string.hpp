#ifndef KCV_EXTERNAL_KCSAPI_EXTENSIONS_TO_STRING_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_EXTENSIONS_TO_STRING_HPP_INCLUDED

// std
#include <string_view>

// kcv
#include "kcv/external/kcsapi/extensions/damage_state.hpp"
#include "kcv/external/kcsapi/types/enum/engagement.hpp"
#include "kcv/external/kcsapi/types/enum/fleet_flag.hpp"
#include "kcv/external/kcsapi/types/enum/formation.hpp"
#include "kcv/external/kcsapi/types/enum/stype.hpp"

namespace kcv {

/// @brief 陣形を文字列に変換する.
constexpr auto to_string(kcv::kcsapi::formation v) noexcept -> std::string_view {
    switch (v) {
        case kcv::kcsapi::formation::line_ahead:
            return "単縦陣";

        case kcv::kcsapi::formation::double_line:
            return "複縦陣";

        case kcv::kcsapi::formation::diamond:
            return "輪形陣";

        case kcv::kcsapi::formation::echelon:
            return "梯形陣";

        case kcv::kcsapi::formation::line_abreast:
            return "単横陣";

        case kcv::kcsapi::formation::vanguard:
            return "警戒陣";

        case kcv::kcsapi::formation::Cruising1:
            return "第一警戒航行序列";

        case kcv::kcsapi::formation::Cruising2:
            return "第二警戒航行序列";

        case kcv::kcsapi::formation::Cruising3:
            return "第三警戒航行序列";

        case kcv::kcsapi::formation::Cruising4:
            return "第四警戒航行序列";
    }

    return "(未知の陣形)";
}

/// @brief 交戦形態を文字列に変換する.
constexpr auto to_string(kcv::kcsapi::engagement v) noexcept -> std::string_view {
    switch (v) {
        case kcv::kcsapi::engagement::parallel:
            return "同航戦";

        case kcv::kcsapi::engagement::head_on:
            return "反航戦";

        case kcv::kcsapi::engagement::green_t:
            return "T字有利";

        case kcv::kcsapi::engagement::red_t:
            return "T字不利";
    }

    return "(未知の交戦形態)";
}

/// @brief 艦隊フラグを文字列に変換する.
constexpr auto to_string(kcv::kcsapi::fleet_flag v) noexcept -> std::string_view {
    switch (v) {
        case kcv::kcsapi::fleet_flag::player:
            return "自軍";

        case kcv::kcsapi::fleet_flag::enemy:
            return "敵軍";
    }

    return "(未知の艦隊フラグ)";
}

/// @brief 艦種IDを文字列に変換する.
constexpr auto to_string(kcv::kcsapi::stype v) noexcept -> std::string_view {
    switch (v) {
        case kcv::kcsapi::stype::de:
            return "海防艦";

        case kcv::kcsapi::stype::dd:
            return "駆逐艦";

        case kcv::kcsapi::stype::cl:
            return "軽巡洋艦";

        case kcv::kcsapi::stype::clt:
            return "重雷装巡洋艦";

        case kcv::kcsapi::stype::ca:
            return "重巡洋艦";

        case kcv::kcsapi::stype::cav:
            return "航空巡洋艦";

        case kcv::kcsapi::stype::cvl:
            return "軽空母";

        case kcv::kcsapi::stype::fbb:
            return "戦艦";

        case kcv::kcsapi::stype::bb:
            return "戦艦";

        case kcv::kcsapi::stype::bbv:
            return "航空戦艦";

        case kcv::kcsapi::stype::cv:
            return "正規空母";

        case kcv::kcsapi::stype::xbb:
            return "超弩級戦艦";

        case kcv::kcsapi::stype::ss:
            return "潜水艦";

        case kcv::kcsapi::stype::ssv:
            return "潜水空母";

        case kcv::kcsapi::stype::ap:
            return "補給艦";

        case kcv::kcsapi::stype::av:
            return "水上機母艦";

        case kcv::kcsapi::stype::lha:
            return "揚陸艦";

        case kcv::kcsapi::stype::cvb:
            return "装甲空母";

        case kcv::kcsapi::stype::ar:
            return "工作艦";

        case kcv::kcsapi::stype::as:
            return "潜水母艦";

        case kcv::kcsapi::stype::ct:
            return "練習巡洋艦";

        case kcv::kcsapi::stype::ao:
            return "補給艦";
    }

    return "(未知の艦種ID)";
}

}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_EXTENSIONS_TO_STRING_HPP_INCLUDED
