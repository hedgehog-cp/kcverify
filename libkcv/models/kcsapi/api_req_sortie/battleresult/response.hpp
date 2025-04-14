#ifndef KCVERIFY_KCSAPI_API_REQ_SORTIE_BATTLERESULT_RESPONSE_HPP_INCLUDED
#define KCVERIFY_KCSAPI_API_REQ_SORTIE_BATTLERESULT_RESPONSE_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <string>
#include <variant>
#include <vector>

// kcv
#include "models/kcsapi/types/api_enemy_info.hpp"
#include "models/kcsapi/types/api_escape.hpp"
#include "models/kcsapi/types/api_get_eventitem.hpp"
#include "models/kcsapi/types/api_get_ship.hpp"
#include "models/kcsapi/types/api_get_useitem.hpp"
#include "models/kcsapi/types/api_landing_hp.hpp"

namespace kcv {
namespace kcsapi {
namespace api_req_sortie {
namespace battleresult {

/// @brief api_req_sortie/battleresult.json
struct response final {
    /// @brief 敵艦撃沈数
    std::int32_t api_dests;

    /// @brief 敵旗艦撃沈フラグ
    std::int32_t api_destsf;

    /// @brief 敵艦隊情報
    kcv::kcsapi::api_enemy_info api_enemy_info;

    /// @brief 退避艦. api_escape==0のときnull.
    std::optional<kcv::kcsapi::api_escape> api_escape;

    /// @brief 退避可能艦の有無. 0=なし, 1=あり.
    std::int32_t api_escape_flag;

    /// 初回クリアフラグ(EO海域攻略時も1)
    std::int32_t api_first_clear;

    /// @brief 獲得基本経験値
    std::int32_t api_get_base_exp;

    /// @brief api_get_eventitem存在時に消滅.
    std::optional<std::int32_t> api_get_eventflag;

    /// @brief 海域攻略報酬. 期間限定海域突破時のみ存在.
    std::optional<std::vector<kcv::kcsapi::api_get_eventitem>> api_get_eventitem;

    /// @brief EO海域攻略時: 獲得戦果(文字列). それ以外は0(数値).
    std::variant<std::int32_t, std::string> api_get_exmap_rate;

    /// @brief EO海域攻略時: 取得アイテムID(文字列). "57"=勲章. それ以外は0(数値).
    std::variant<std::int32_t, std::string> api_get_exmap_useitem_id;

    /// @brief 獲得提督経験値
    std::int32_t api_get_exp;

    // [味方艦船数][]
    // [][0]=獲得前経験値
    // [][1]=次のレベルの経験値(レベルキャップ到達時存在せず)
    // [][2](レベルアップしたなら)その次のレベルの経験値, ...
    std::vector<std::vector<std::int32_t>> api_get_exp_lvup;

    /// @brief 入手フラグ. [0]=アイテム, [1]=艦娘.
    std::vector<std::int32_t> api_get_flag;

    /// @brief ドロップ艦情報. api_get_flag[1]==1のとき存在.
    std::optional<kcv::kcsapi::api_get_ship> api_get_ship;

    /// @brief 各艦の獲得経験値. [7] | [8] 7番艦が経験値入手可能な状況((空き/撃沈/退避中)ではないとき)のみ
    /// [1]が旗艦 [0]と(空き/撃沈/退避)は -1
    std::vector<std::int32_t> api_get_ship_exp;

    /// @brief ドロップアイテム情報. api_get_flag[0]=1のときのみ存在.
    std::optional<kcv::kcsapi::api_get_useitem> api_get_useitem;

    /// @brief イベントの輸送作戦時のみ存在.
    std::optional<kcv::kcsapi::api_landing_hp> api_landing_hp;

    std::optional<std::int32_t> api_m1;
    std::optional<std::int32_t> api_m2;
    std::optional<std::int32_t> api_m10;
    std::optional<std::string> api_m_suffix;

    /// @brief 航空偵察作戦報酬獲得フラグ. 0=なし, 1=獲得.
    std::int32_t api_mapcell_incentive;

    /// @brief 提督経験値
    std::int32_t api_member_exp;

    /// @brief 艦隊司令部レベル
    std::int32_t api_member_lv;

    /// @brief MVP. 1基点. -1=なし.
    std::int32_t api_mvp;

    /// @brief 次に出撃可能になった海域ID[]. 海域解放時のみ存在. 通常海域は数値、イベント海域は文字列.
    std::optional<std::vector<std::variant<std::int32_t, std::string>>> api_next_map_ids;

    /// @brief 難易度
    std::int32_t api_quest_level;

    /// @brief 出撃海域名
    std::string api_quest_name;

    /// @brief 敵艦船ID. [艦船数].
    std::vector<std::int32_t> api_ship_id;

    /// @brief 勝利ランク.
    std::string api_win_rank;
};

}  // namespace battleresult
}  // namespace api_req_sortie
}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_API_REQ_SORTIE_BATTLERESULT_RESPONSE_HPP_INCLUDED
