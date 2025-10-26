#ifndef KCVERIFY_MODELS_KCSAPI_API_REQ_MAP_NEXT_RESPONSE_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_API_REQ_MAP_NEXT_RESPONSE_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <variant>
#include <vector>

// kcv
#include "models/kcsapi/types/api_airsearch.hpp"
#include "models/kcsapi/types/api_cell_flavor.hpp"
#include "models/kcsapi/types/api_destruction_battle.hpp"
#include "models/kcsapi/types/api_e_deck_info.hpp"
#include "models/kcsapi/types/api_eventmap.hpp"
#include "models/kcsapi/types/api_happening.hpp"
#include "models/kcsapi/types/api_itemget.hpp"
#include "models/kcsapi/types/api_select_route.hpp"
#include "models/kcsapi/types/enum/cell_type.hpp"

namespace kcv {
namespace kcsapi {
namespace api_req_map {
namespace next {

/// @brief api_req_map/next.json
/// 進撃.
struct response final {
    /// @brief 次が航空偵察マスのときのみ存在.
    kcv::kcsapi::api_airsearch api_airsearch;

    // 泊地セルでのみ存在. 0=修理不可 1=修理可能.
    // api_anchorage_flag

    /// @brief ボスセルID.
    std::int32_t api_bosscell_no;

    /// @brief ボス到達済みフラグ? コード中にスペルミスがあり未使用.
    std::int32_t api_bosscomp;

    /// @brief 「気のせいだった」特殊メッセージ. 必要な時のみ存在.
    std::optional<kcv::kcsapi::api_cell_flavor> api_cell_flavor;

    /// @brief 次のセルの色. api_req_map/start.api_cell_data.api_color_no と同じ.
    kcv::kcsapi::cell_type api_color_no;

    /// @brief 0=なし 1=<敵艦隊発見!> 2=<攻撃目標発見!>? 3=<針路哨戒!>?. startにはないので注意.
    std::int32_t api_comment_kind;

    /// Enemy fleet preview. Only one element against single fleet. Two elements if fighting combined fleet.
    /// @brief 会敵時の敵艦隊「大まかな陣容」シルエット情報[1か連合艦隊2]. 航空戦と空襲戦(第6海域除く)には存在しない.
    /// 払暁戦とレーダー射撃戦は不明.
    std::optional<kcv::kcsapi::api_e_deck_info> api_e_deck_info;

    /// @brief 超重爆迎撃戦QTEイベントフラグ. 発生した時のみ存在.
    std::optional<std::int32_t> api_destruction_flag;

    /// @brief 基地防空戦データ. ほぼ戦闘APIに準じる. 発生した時のみ存在. 超重爆迎撃の場合は存在しない.
    std::optional<kcv::kcsapi::api_destruction_battle> api_destruction_battle;

    /// @brief イベント.
    std::int32_t api_event_id;

    /// @brief イベント種別.
    std::int32_t api_event_kind;

    /// @brief イベント海域ゲージ情報.
    std::optional<kcv::kcsapi::api_eventmap> api_eventmap;

    /// @brief 獲得戦果. 次が船団護衛成功マスのときのみ存在(ゲージ破壊時追加で).
    std::optional<std::int32_t> api_get_eo_rate;

    /// @brief 次が渦潮マスのときのみ存在.
    std::optional<kcv::kcsapi::api_happeing> api_happening;

    /// Element type is <see cref="Models.ApiItemget"/> or <see cref="List{T}"/> of <see cref="Models.ApiItemget"/>s.
    /// @brief
    std::optional<std::variant<kcv::kcsapi::api_itemget, std::vector<kcv::kcsapi::api_itemget>>> api_itemget;

    /// @brief
    // std::optional<kcv::kcsapi::api_itemget_eo> api_itemget_eo_comment;

    /// @brief
    // std::optional<kcv::kcsapi::api_itemget_eo> api_itemget_eo_result;

    /// @brief 煙幕使用制限. 1=使用不可(煙幕UI出現しない). 現時点1出撃に煙幕1回使用可能なので,
    /// 展開後のマスにはこれによる制限される. あと CellTaskBattle._isEnabledSmoke によると,
    /// 夜戦開始マスと払暁戦マスも使用不可. もちろん, 未退避の発煙装置装備艦がない場合も.
    std::optional<std::int32_t> api_limit_state;

    /// @brief 海域カテゴリID(2-3でいう2).
    std::int32_t api_maparea_id;

    /// @brief 海域カテゴリ内番号(2-3でいう3).
    std::int32_t api_mapinfo_no;

    /// @brief 次のマスでのルート分岐の本数 0=行き止まり.
    std::int32_t api_next;

    /// @brief 次に向かうセルのID.
    std::int32_t api_no;

    /// @brief 洋上補給. ボス前で発動した場合は確認される? 発動しなければ存在しない.
    // std::optional<kcv::kcsapi::api_offshore_supply> api_offshore_supply;

    /// @brief 0=なし 1=索敵機発艦. startにはないので注意.
    std::int32_t api_production_kind;

    /// @brief 羅針盤を表示するか.
    std::int32_t api_rashin_flg;

    /// @brief 妖精さん. 0=なし, 1=眠そう, 2=桃の髪飾り, 3=ひよこ, 4=魔法使い.
    std::int32_t api_rashin_id;

    /// @brief 戦闘糧食使用確認フラグ. 0=表示しない, 1=表示する. ボス前以外では存在しない.
    std::optional<std::int32_t> api_ration_flag;

    /// @brief 次が能動分岐マスのときのみ存在
    std::optional<kcv::kcsapi::api_select_route> api_select_route;
};

}  // namespace next
}  // namespace api_req_map
}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_API_REQ_MAP_NEXT_RESPONSE_HPP_INCLUDED
