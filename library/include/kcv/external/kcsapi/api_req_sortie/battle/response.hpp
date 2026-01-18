#ifndef KCV_EXTERNAL_KCSAPI_API_REQ_SORTIE_BATTLE_RESPONSE_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_API_REQ_SORTIE_BATTLE_RESPONSE_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <tuple>
#include <vector>

// kcv
#include "kcv/external/kcsapi/types/api_air_base_attack.hpp"
#include "kcv/external/kcsapi/types/api_air_base_injection.hpp"
#include "kcv/external/kcsapi/types/api_flavor_info.hpp"
#include "kcv/external/kcsapi/types/api_friendly_battle.hpp"
#include "kcv/external/kcsapi/types/api_friendly_info.hpp"
#include "kcv/external/kcsapi/types/api_hougeki1.hpp"
#include "kcv/external/kcsapi/types/api_injection_kouku.hpp"
#include "kcv/external/kcsapi/types/api_kouku.hpp"
#include "kcv/external/kcsapi/types/api_opening_atack.hpp"
#include "kcv/external/kcsapi/types/api_raigeki.hpp"
#include "kcv/external/kcsapi/types/api_stage_flag.hpp"
#include "kcv/external/kcsapi/types/api_support_info.hpp"
#include "kcv/external/kcsapi/types/enum/detection_type.hpp"
#include "kcv/external/kcsapi/types/enum/engagement.hpp"
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"
#include "kcv/external/kcsapi/types/enum/formation.hpp"
#include "kcv/external/kcsapi/types/enum/ship_id.hpp"
#include "kcv/external/kcsapi/types/enum/support_type.hpp"
#include "kcv/external/kcsapi/types/number.hpp"

namespace kcv {
namespace kcsapi {
namespace api_req_sortie {
namespace battle {

/// @brief api_req_sortie/battle.json
/// 昼戦.
struct response final {
    /// @brief 環礁マスフラグ.
    std::optional<std::int32_t> api_atoll_cell;

    /// @brief 基地航空隊噴式強襲.
    std::optional<kcv::kcsapi::api_air_base_injection> api_air_base_injection;

    /// @brief 基地航空隊攻撃.
    std::optional<kcv::kcsapi::api_air_base_attack> api_air_base_attack;

    /// @brief 自軍の出撃艦隊ID.
    std::int32_t api_deck_id;

    /// @brief 敵軍の基礎ステータス. [艦船数]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_eParam;

    /// @brief 退避艦インデックス. [退避艦数]. 1基点.
    std::optional<std::vector<std::int32_t>> api_escape_idx;

    /// @brief 装甲破砕フラグ.
    std::optional<std::int32_t> api_x_al01;

    /// @brief 戦闘糧食補給. 発動時のみ存在. 艦船IDの配列
    std::optional<std::vector<kcv::kcsapi::ship_id>> api_combat_ration;

    /// @brief 煙幕システム(2023/4/23~). 0=未使用|不発, 1,2,3=濃度. 現在, 夜戦では煙幕を展開しない.
    std::optional<std::int32_t> api_smoke_type;

    /// @brief 敵軍の装備スロット. [艦船数][5]. 空きスロットには-1.
    std::vector<std::array<kcv::kcsapi::equipment_id, 5>> api_eSlot;

    /// @brief 敵軍の最大耐久. [艦船数].
    std::vector<kcv::kcsapi::number> api_e_maxhps;

    /// @brief 敵軍の現在耐久. [艦船数].
    std::vector<kcv::kcsapi::number> api_e_nowhps;

    /// @brief 自軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_fParam;

    /// @brief 友軍艦隊攻撃情報. 発動時のみ存在.
    std::optional<kcv::kcsapi::api_friendly_info> api_friendly_info;

    /// @brief 友軍艦隊攻撃. 発動時のみ存在.
    std::optional<kcv::kcsapi::api_friendly_battle> api_friendly_battle;

    /// @brief 自軍の最大耐久. [艦船数].
    std::vector<std::int32_t> api_f_maxhps;

    /// @brief 自軍の現在耐久. [艦船数].
    std::vector<std::int32_t> api_f_nowhps;

    /// @brief 友軍艦隊航空攻撃.
    std::optional<kcv::kcsapi::api_kouku> api_friendly_kouku;

    /// @brief 敵ボス艦の情報とフレーバーテキスト. [1].
    std::optional<std::vector<kcv::kcsapi::api_flavor_info>> api_flavor_info;

    /// @brief 陣形と交戦形態. [0]=自軍, [1]=敵軍, [2]=交戦形態.
    std::tuple<kcv::kcsapi::formation, kcv::kcsapi::formation, kcv::kcsapi::engagement> api_formation;

    /// @brief 阻塞気球マスフラグ.
    std::int32_t api_balloon_cell;

    /// @brief 砲撃戦1巡目. api_hourai_flag[0]==0のときnull. メンバの配列長はすべて攻撃フェイズの回数.
    std::optional<kcv::kcsapi::api_hougeki1> api_hougeki1;

    /// @brief 砲撃戦2巡目. api_hourai_flag[1]==0のときnull. メンバの配列長はすべて攻撃フェイズの回数.
    std::optional<kcv::kcsapi::api_hougeki1> api_hougeki2;

    /// @brief 砲撃戦3巡目. api_hourai_flag[2]==0のときnull. メンバの配列長はすべて攻撃フェイズの回数.
    std::optional<kcv::kcsapi::api_hougeki1> api_hougeki3;

    /// @brief 砲雷撃戦フラグ. [0]=砲撃戦1巡目, [1]=砲撃戦2巡目, [2]=砲撃戦3巡目, [3]=雷撃戦.
    std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t> api_hourai_flag;

    /// @brief 噴式強襲航空攻撃.
    std::optional<kcv::kcsapi::api_injection_kouku> api_injection_kouku;

    /// @brief 航空戦情報.
    std::optional<kcv::kcsapi::api_kouku> api_kouku;

    /// @brief 夜戦突入可否. 0=不可(昼戦で敵全滅など), 1=可能.
    std::int32_t api_midnight_flag;

    /// @brief 開幕雷撃戦. api_opening_flag==0のときnull.
    std::optional<kcv::kcsapi::api_opening_atack> api_opening_atack;

    /// @brief 開幕雷撃フラグ. 0=発動せず, 1=発動.
    std::int32_t api_opening_flag;

    /// @brief TSBK
    std::optional<kcv::kcsapi::api_hougeki1> api_opening_taisen;

    /// @brief TSBKフラグ. 0=なし 1=あり.
    std::int32_t api_opening_taisen_flag;

    /// @brief 雷撃戦. api_hourai_flag[3]==0のときnull.
    std::optional<kcv::kcsapi::api_raigeki> api_raigeki;

    /// @brief 索敵成否, [0]=自軍, [1]=敵軍. 1=成功, 2=成功(未帰還機あり), 3=未帰還, 4=失敗, 5=発見, 6=発見できず.
    std::tuple<kcv::kcsapi::detection_type, kcv::kcsapi::detection_type> api_search;

    /// @brief 敵艦船ID. [艦船数].
    std::vector<kcv::kcsapi::ship_id> api_ship_ke;

    /// @brief 敵艦船Lv. [艦船数].
    std::vector<std::int32_t> api_ship_lv;

    /// @brief 航空戦フラグ. [0]=api_stage1, [1]=api_stage2, [2]=api_stage3.
    kcv::kcsapi::api_stage_flag api_stage_flag;

    /// @brief 支援艦隊フラグ. 0=なし, 1=空撃, 2=砲撃, 3=雷撃, 4=対潜.
    kcv::kcsapi::support_type api_support_flag;

    /// @brief 支援艦隊情報. api_support_flag==0のときnull.
    std::optional<kcv::kcsapi::api_support_info> api_support_info;
};

}  // namespace battle
}  // namespace api_req_sortie
}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_API_REQ_SORTIE_BATTLE_RESPONSE_HPP_INCLUDED
