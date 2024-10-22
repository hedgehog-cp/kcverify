#ifndef KCVERIFY_API_API_REQ_BATTLE_MIDNIGHT_BATTLE_RESPONSE_HPP_INCLUDED
#define KCVERIFY_API_API_REQ_BATTLE_MIDNIGHT_BATTLE_RESPONSE_HPP_INCLUDED

// std
#include <array>
#include <optional>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

// kcv
#include "kcapi/types/api_friendly_battle.hpp"
#include "kcapi/types/api_friendly_info.hpp"
#include "kcapi/types/api_hougeki.hpp"
#include "kcapi/types/enum/engagement.hpp"
#include "kcapi/types/enum/formation.hpp"
#include "kcapi/types/enum/ship_id.hpp"

namespace kcv {
namespace kcapi {
namespace api_req_battle_midnight {
namespace battle {

/// @brief api_req_battle_midnight/battle.json
struct response final {
    /// @brief 自軍の出撃艦隊ID. 取り得る値は{1, 2, 3, 4}など.
    int api_deck_id;

    /// @brief 敵軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<int, int, int, int>> api_eParam;

    /// @brief 退避艦インデックス. [退避艦数]. 1基点.
    std::optional<std::vector<int>> api_escape_idx;

    /// @brief 装甲破砕フラグ.
    std::optional<int> api_x_al01;

    /// @brief 戦闘糧食補給. 発動時のみ存在. 艦船IDの配列
    std::optional<std::vector<ship_id>> api_combat_ration;

    /// @brief 煙幕システム(2023/4/23~). 0=未使用|不発, 1,2,3=濃度. 現在, 夜戦では煙幕を展開しない.
    std::optional<int> api_smoke_type;

    /// @brief 敵軍の装備スロット. [艦船数][5]. 空きスロットには-1.
    std::vector<std::array<int, 5>> api_eSlot;

    /// @brief 敵軍の最大耐久. [艦船数].
    std::vector<std::variant<int, std::string>> api_e_maxhps;

    /// @brief 敵軍の現在耐久. [艦船数].
    std::vector<std::variant<int, std::string>> api_e_nowhps;

    /// @brief 友軍艦隊攻撃情報. 発動時のみ存在.
    std::optional<kcapi::api_friendly_info> api_friendly_info;

    /// @brief 友軍艦隊攻撃. 発動時のみ存在.
    std::optional<kcapi::api_friendly_battle> api_friendly_battle;

    /// @brief 自軍の最大耐久. [艦船数].
    std::vector<int> api_f_maxhps;

    /// @brief 自軍の現在耐久. [艦船数].
    std::vector<int> api_f_nowhps;

    /// @brief 照明弾投射艦インデックス. [2]. [0]=自軍, [1]=敵軍. 0基点. 投射しなければ-1.
    std::tuple<int, int> api_flare_pos;

    /// @brief 陣形と交戦形態. [0]=自軍, [1]=敵軍, [2]=交戦形態.
    std::tuple<formation, formation, engagement> api_formation;

    /// @brief 夜間砲雷撃戦.
    std::optional<kcapi::api_hougeki> api_hougeki;

    /// @brief 敵艦船ID. [艦船数].
    std::vector<ship_id> api_ship_ke;

    /// @brief 敵艦船Lv. [艦船数].
    std::vector<int> api_ship_lv;

    /// @brief 自軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<int, int, int, int>> api_fParam;

    /// @brief 夜間触接機ID. [2]. [0]=自軍, [1]=敵軍. 触接しなければ-1.
    std::tuple<std::variant<int, std::string>, std::variant<int, std::string>> api_touch_plane;

    /// @brief 阻塞気球マスフラグ.
    int api_balloon_cell;

    /// @brief 環礁マスフラグ.
    std::optional<int> api_atoll_cell;
};

}  // namespace battle
}  // namespace api_req_battle_midnight
}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_API_API_REQ_BATTLE_MIDNIGHT_BATTLE_RESPONSE_HPP_INCLUDED
