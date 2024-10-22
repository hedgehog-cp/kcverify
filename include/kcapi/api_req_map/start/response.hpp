#ifndef KCVERIFY_KCAPI_API_REQ_MAP_START_RESPONSE_HPP_INCLUDED
#define KCVERIFY_KCAPI_API_REQ_MAP_START_RESPONSE_HPP_INCLUDED

// std
#include <optional>

// kcv
#include "kcapi/types/api_airsearch.hpp"
#include "kcapi/types/api_cell_data.hpp"
#include "kcapi/types/api_cell_flavor.hpp"
#include "kcapi/types/api_e_deck_info.hpp"
#include "kcapi/types/api_eventmap.hpp"
#include "kcapi/types/api_happening.hpp"
#include "kcapi/types/api_select_route.hpp"
#include "kcapi/types/enum/cell_type.hpp"

namespace kcv {
namespace kcapi {
namespace api_req_map {
namespace start {

/// @brief api_req_map/start.json
struct response final {
    /// @brief 航空偵察.
    kcapi::api_airsearch api_airsearch;

    /// @brief ボスセルID.
    int api_bosscell_no;

    /// @brief ボス到達済みフラグ.
    int api_bosscomp;

    /// @brief 当該海域の全セルデータ.
    kcapi::api_cell_data api_cell_data;

    /// @brief セル到達時のフレーバーテキスト.
    std::optional<kcapi::api_cell_flavor> api_cell_flavor;

    /// @brief セルタイプ.
    cell_type api_color_no;

    /// @brief 敵艦隊プレビュー. 通常艦隊のとき[1], 連合艦隊のとき[2].
    kcapi::api_e_deck_info api_e_deck_info;

    /// @brief イベント.
    int api_event_id;

    /// @brief イベント種別.
    int api_event_kind;

    /// @brief 期間限定海域ゲージ情報.
    std::optional<kcapi::api_eventmap> api_eventmap;

    /// @brief スタート地点のセルID.
    int api_from_no;

    /// @brief 煙幕使用制限. 1=使用不可.
    std::optional<int> api_limit_state;

    /// @brief 次が渦潮マスのときのみ存在
    std::optional<kcapi::api_happeing> api_happeing;

    /// @brief 海域カテゴリID. #5-3-Pに対する5.
    int api_maparea_id;

    /// @brief 海域カテゴリ内番号. #5-3-Pに対する3.
    int api_mapinfo_no;

    /// @brief 次のマスでのルート分岐の本数. 0=行き止まり.
    int api_next;

    /// @brief 次に向かうセルのID.
    int api_no;

    /// @brief 羅針盤表示フラグ. 羅針盤を表示するか.
    int api_rashin_flg;

    /// @brief 妖精さん. 0=なし, 1=眠そう, 2=桃の髪飾り, 3=ひよこ, 4=魔法使い.
    int api_rashin_id;

    /// @brief 次が能動分岐マスのときのみ存在.
    std::optional<kcapi::api_select_route> api_select_route;
};

}  // namespace start
}  // namespace api_req_map
}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_API_REQ_MAP_START_RESPONSE_HPP_INCLUDED
