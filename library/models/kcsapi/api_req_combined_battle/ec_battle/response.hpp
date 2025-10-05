#ifndef KCVERIFY_MODELS_KCSAPI_API_REQ_COMBINED_BATTLE_EC_BATTLE_RESPONSE_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_API_REQ_COMBINED_BATTLE_EC_BATTLE_RESPONSE_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "models/kcsapi/types/api_air_base_attack.hpp"
#include "models/kcsapi/types/api_air_base_rescue_type.hpp"
#include "models/kcsapi/types/api_flavor_info.hpp"
#include "models/kcsapi/types/api_hougeki1.hpp"
#include "models/kcsapi/types/api_kouku.hpp"
#include "models/kcsapi/types/api_opening_atack.hpp"
#include "models/kcsapi/types/api_raigeki.hpp"
#include "models/kcsapi/types/api_support_info.hpp"
#include "models/kcsapi/types/enum/detection_type.hpp"
#include "models/kcsapi/types/enum/engagement.hpp"
#include "models/kcsapi/types/enum/formation.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"
#include "models/kcsapi/types/enum/support_type.hpp"

namespace kcv {
namespace kcsapi {
namespace api_req_combined_battle {
namespace ec_battle {

/// @brief api_req_combined_battle/ec_battle.json
/// 通常艦隊 vs 敵連合艦隊 昼戦.
struct response final {
    /// @brief 環礁マスフラグ.
    std::optional<std::int32_t> api_atoll_cell;

    /// @brief 基地航空隊攻撃.
    std::optional<kcv::kcsapi::api_air_base_attack> api_air_base_attack;

    /// @brief 基地航空隊カタリナ救助活動フラグ. 1～3. (吹き出しの数). 発生しなかった場合は存在しない.
    kcv::kcsapi::api_air_base_rescue_type api_air_base_rescue_type;

    /// @brief 阻塞気球マスフラグ.
    std::int32_t api_balloon_cell;

    /// @brief 戦闘糧食補給. 発動時のみ存在. 艦船IDの配列
    std::optional<std::vector<kcv::kcsapi::ship_id>> api_combat_ration;

    /// @brief 自軍の出撃艦隊ID. 取り得る値は{1, 2, 3, 4}など.
    std::int32_t api_deck_id;

    /// @brief 敵主力艦隊現在HP [13] (-1から始まる)
    std::vector<std::int32_t> api_e_maxhps;

    /// @brief 敵主力艦隊現在HP [13] (-1から始まる)
    std::vector<std::int32_t> api_e_maxhps_combined;

    /// @brief 敵主力艦隊現在HP [13] (-1から始まる)
    std::vector<std::int32_t> api_e_nowhps;

    /// @brief 敵主力艦隊現在HP [13] (-1から始まる)
    std::vector<std::int32_t> api_e_nowhps_combined;

    /// @brief 敵軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_eParam;

    /// @brief 敵軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_eParam_combined;

    /// @brief 退避艦インデックス. [退避艦数]. 1基点. いなければ存在しない.
    std::optional<std::vector<std::int32_t>> api_escape_idx;

    /// @brief 敵主力艦隊装備IDリスト [6][5]
    std::vector<std::array<std::int32_t, 5>> api_eSlot;

    /// @brief 敵随伴艦隊装備IDリスト [6][5]
    std::vector<std::array<std::int32_t, 5>> api_eSlot_combined;

    /// @brief 敵ボス艦の情報とフレーバーテキスト[1]
    kcv::kcsapi::api_flavor_info api_flavor_info;

    /// @brief 陣形と交戦形態. [0]=自軍, [1]=敵軍, [2]=交戦形態.
    std::tuple<kcv::kcsapi::formation, kcv::kcsapi::formation, kcv::kcsapi::engagement> api_formation;

    /// @brief 自軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_fParam;

    /// @brief 自軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_fParam_combined;

    /// @brief 味方主力艦隊現在HP [13] (-1から始まる)
    std::vector<std::int32_t> api_f_nowhps;

    /// @brief 味方主力艦隊現在HP [13] (-1から始まる)
    std::vector<std::int32_t> api_f_maxhps;

    /// @brief 砲雷撃戦フラグ. [0]=砲撃戦1巡目, [1]=砲撃戦2巡目, [2]=砲撃戦3巡目, [3]=雷撃戦.
    std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t> api_hourai_flag;

    /// @brief 砲撃戦1巡目. api_hourai_flag[0]==0のときnull. メンバの配列長はすべて攻撃フェイズの回数.
    std::optional<kcv::kcsapi::api_hougeki1> api_hougeki1;

    /// @brief 砲撃戦2巡目. api_hourai_flag[1]==0のときnull. メンバの配列長はすべて攻撃フェイズの回数.
    std::optional<kcv::kcsapi::api_hougeki1> api_hougeki2;

    /// @brief 砲撃戦3巡目. api_hourai_flag[2]==0のときnull. メンバの配列長はすべて攻撃フェイズの回数.
    std::optional<kcv::kcsapi::api_hougeki1> api_hougeki3;

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

    /// @brief 敵主力艦隊艦船ID [7] (-1から始まる).
    std::vector<kcv::kcsapi::ship_id> api_ship_ke;

    /// @brief 敵随伴艦隊艦船ID [7] (-1から始まる).
    std::vector<kcv::kcsapi::ship_id> api_ship_ke_combined;

    /// @brief 敵主力艦隊Lv [7] (-1から始まる).
    std::vector<std::int32_t> api_ship_lv;

    /// @brief 敵随伴艦隊Lv [7] (-1から始まる)
    std::vector<std::int32_t> api_ship_lv_combined;

    /// @brief 煙幕システム(2023/4/23~). 0=未使用|不発, 1,2,3=濃度. 現在, 夜戦では煙幕を展開しない.
    std::optional<std::int32_t> api_smoke_type;

    /// @brief 航空戦フラグ. [n]==0のときapi_stage{n+1}==null (航空戦力なし, 艦戦のみなど).
    std::vector<std::int32_t> api_stage_flag;

    /// @brief 支援艦隊フラグ. 0=なし, 1=空撃, 2=砲撃, 3=雷撃, 4=対潜.
    kcv::kcsapi::support_type api_support_flag;

    /// @brief 支援艦隊情報. api_support_flag==0のときnull.
    std::optional<kcv::kcsapi::api_support_info> api_support_info;

    /// @brief 装甲破砕フラグ.
    std::optional<std::int32_t> api_x_al01;
};

}  // namespace ec_battle
}  // namespace api_req_combined_battle
}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_API_REQ_COMBINED_BATTLE_EC_BATTLE_RESPONSE_HPP_INCLUDED
