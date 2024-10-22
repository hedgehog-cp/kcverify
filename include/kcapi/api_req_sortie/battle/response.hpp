#ifndef KCVERIFY_KCAPI_API_REQ_SORTIE_BATTLE_RESPONSE_HPP_INCLUDED
#define KCVERIFY_KCAPI_API_REQ_SORTIE_BATTLE_RESPONSE_HPP_INCLUDED

// std
#include <optional>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

// kcv
#include "kcapi/types/api_air_base_attack.hpp"
#include "kcapi/types/api_air_base_injection.hpp"
#include "kcapi/types/api_flavor_info.hpp"
#include "kcapi/types/api_friendly_battle.hpp"
#include "kcapi/types/api_friendly_info.hpp"
#include "kcapi/types/api_hougeki1.hpp"
#include "kcapi/types/api_injection_kouku.hpp"
#include "kcapi/types/api_kouku.hpp"
#include "kcapi/types/api_opening_atack.hpp"
#include "kcapi/types/api_raigeki.hpp"
#include "kcapi/types/api_support_info.hpp"
#include "kcapi/types/enum/detection_type.hpp"
#include "kcapi/types/enum/engagement.hpp"
#include "kcapi/types/enum/formation.hpp"
#include "kcapi/types/enum/ship_id.hpp"
#include "kcapi/types/enum/support_type.hpp"

namespace kcv {
namespace kcapi {
namespace api_req_sortie {
namespace battle {

/// @brief api_req_sortie/battle.json
struct response final {
    std::optional<int> api_atoll_cell;

    /// @brief 基地航空隊噴式強襲.
    std::optional<kcapi::api_air_base_injection> api_air_base_injection;

    /// @brief 基地航空隊攻撃.
    std::optional<kcapi::api_air_base_attack> api_air_base_attack;

    /// @brief 自軍の出撃艦隊ID.
    int api_deck_id;

    /// @brief 敵軍の基礎ステータス. [艦船数]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
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

    /// @brief 自軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<int, int, int, int>> api_fParam;

    /// @brief 友軍艦隊攻撃情報. 発動時のみ存在.
    std::optional<kcapi::api_friendly_info> api_friendly_info;

    /// @brief 友軍艦隊攻撃. 発動時のみ存在.
    std::optional<kcapi::api_friendly_battle> api_friendly_battle;

    /// @brief 自軍の最大耐久. [艦船数].
    std::vector<int> api_f_maxhps;

    /// @brief 自軍の現在耐久. [艦船数].
    std::vector<int> api_f_nowhps;

    /// @brief 友軍艦隊航空攻撃.
    std::optional<kcapi::api_kouku> api_friendly_kouku;

    /// @brief 敵ボス艦の情報とフレーバーテキスト. [1].
    std::optional<std::vector<kcapi::api_flavor_info>> api_flavor_info;

    /// @brief 陣形と交戦形態. [0]=自軍, [1]=敵軍, [2]=交戦形態.
    std::tuple<formation, formation, engagement> api_formation;

    /// @brief 阻塞気球マスフラグ.
    int api_balloon_cell;

    /// @brief 砲撃戦1巡目. api_hourai_flag[0]==0のときnull. メンバの配列長はすべて攻撃フェイズの回数.
    std::optional<kcapi::api_hougeki1> api_hougeki1;

    /// @brief 砲撃戦2巡目. api_hourai_flag[1]==0のときnull. メンバの配列長はすべて攻撃フェイズの回数.
    std::optional<kcapi::api_hougeki1> api_hougeki2;

    /// @brief 砲撃戦3巡目. api_hourai_flag[2]==0のときnull. メンバの配列長はすべて攻撃フェイズの回数.
    std::optional<kcapi::api_hougeki1> api_hougeki3;

    /// @brief 砲雷撃戦フラグ. [0]=砲撃戦1巡目, [1]=砲撃戦2巡目, [2]=砲撃戦3巡目, [3]=雷撃戦.
    std::tuple<int, int, int, int> api_hourai_flag;

    /// @brief 噴式強襲航空攻撃.
    std::optional<kcapi::api_injection_kouku> api_injection_kouku;

    /// @brief 航空戦情報.
    std::optional<kcapi::api_kouku> api_kouku;

    /// @brief 夜戦突入可否. 0=不可(昼戦で敵全滅など), 1=可能.
    int api_midnight_flag;

    /// @brief 開幕雷撃戦. api_opening_flag==0のときnull.
    std::optional<kcapi::api_opening_atack> api_opening_atack;

    /// @brief 開幕雷撃フラグ. 0=発動せず, 1=発動.
    int api_opening_flag;

    /// @brief TSBK
    std::optional<kcapi::api_hougeki1> api_opening_taisen;

    /// @brief TSBKフラグ. 0=なし 1=あり.
    int api_opening_taisen_flag;

    /// @brief 雷撃戦. api_hourai_flag[3]==0のときnull.
    std::optional<kcapi::api_raigeki> api_raigeki;

    /// @brief 索敵成否, [0]=自軍, [1]=敵軍. 1=成功, 2=成功(未帰還機あり), 3=未帰還, 4=失敗, 5=発見, 6=発見できず.
    std::tuple<detection_type, detection_type> api_search;

    /// @brief 敵艦船ID. [艦船数].
    std::vector<ship_id> api_ship_ke;

    /// @brief 敵艦船Lv. [艦船数].
    std::vector<int> api_ship_lv;

    /// @brief 航空戦フラグ. [n]==0のときapi_stage{n+1}==null (航空戦力なし, 艦戦のみなど).
    std::vector<int> api_stage_flag;

    /// @brief 支援艦隊フラグ. 0=なし, 1=空撃, 2=砲撃, 3=雷撃, 4=対潜.
    support_type api_support_flag;

    /// @brief 支援艦隊情報. api_support_flag==0のときnull.
    std::optional<kcapi::api_support_info> api_support_info;
};

}  // namespace battle
}  // namespace api_req_sortie
}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_API_REQ_SORTIE_BATTLE_RESPONSE_HPP_INCLUDED
