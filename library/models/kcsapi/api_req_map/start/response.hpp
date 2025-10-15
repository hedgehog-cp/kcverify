#ifndef KCVERIFY_MODELS_KCSAPI_API_REQ_MAP_START_RESPONSE_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_API_REQ_MAP_START_RESPONSE_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <variant>

// kcv
#include "models/kcsapi/types/api_airsearch.hpp"
#include "models/kcsapi/types/api_cell_data.hpp"
#include "models/kcsapi/types/api_cell_flavor.hpp"
#include "models/kcsapi/types/api_e_deck_info.hpp"
#include "models/kcsapi/types/api_eventmap.hpp"
#include "models/kcsapi/types/api_happening.hpp"
#include "models/kcsapi/types/api_itemget.hpp"
#include "models/kcsapi/types/api_select_route.hpp"
#include "models/kcsapi/types/enum/cell_type.hpp"

namespace kcv {
namespace kcsapi {
namespace api_req_map {
namespace start {

/// @brief api_req_map/start.json
struct response final {
    /// @brief 航空偵察.
    kcv::kcsapi::api_airsearch api_airsearch;

    /// @brief ボスセルID.
    std::int32_t api_bosscell_no;

    /// @brief ボス到達済みフラグ.
    std::int32_t api_bosscomp;

    /// @brief 当該海域の全セルデータ.
    kcv::kcsapi::api_cell_data api_cell_data;

    /// @brief セル到達時のフレーバーテキスト.
    std::optional<kcv::kcsapi::api_cell_flavor> api_cell_flavor;

    /// @brief セルタイプ.
    kcv::kcsapi::cell_type api_color_no;

    /// @brief 敵艦隊プレビュー. 通常艦隊のとき[1], 連合艦隊のとき[2].
    kcv::kcsapi::api_e_deck_info api_e_deck_info;

    /// @brief イベント.
    std::int32_t api_event_id;

    /// @brief イベント種別.
    std::int32_t api_event_kind;

    /// @brief 期間限定海域ゲージ情報.
    std::optional<kcv::kcsapi::api_eventmap> api_eventmap;

    /// @brief スタート地点のセルID.
    std::int32_t api_from_no;

    /// @brief 海域突破報酬一覧[]. 海域突破時に最終セルが非戦闘系イベント(輸送セルなど)だった場合存在.
    std::optional<std::variant<kcv::kcsapi::api_itemget, std::vector<kcv::kcsapi::api_itemget>>> api_itemget;

    /// @brief 煙幕使用制限. 1=使用不可.
    std::optional<std::int32_t> api_limit_state;

    /// @brief 次が渦潮マスのときのみ存在
    std::optional<kcv::kcsapi::api_happeing> api_happening;

    /// @brief 海域カテゴリID. #5-3-Pに対する5.
    std::int32_t api_maparea_id;

    /// @brief 海域カテゴリ内番号. #5-3-Pに対する3.
    std::int32_t api_mapinfo_no;

    /// @brief 次のマスでのルート分岐の本数. 0=行き止まり.
    std::int32_t api_next;

    /// @brief 次に向かうセルのID.
    std::int32_t api_no;

    /// @brief 羅針盤表示フラグ. 羅針盤を表示するか.
    std::int32_t api_rashin_flg;

    /// @brief 妖精さん. 0=なし, 1=眠そう, 2=桃の髪飾り, 3=ひよこ, 4=魔法使い.
    std::int32_t api_rashin_id;

    /// @brief 次が能動分岐マスのときのみ存在.
    std::optional<kcv::kcsapi::api_select_route> api_select_route;
};

}  // namespace start
}  // namespace api_req_map
}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_API_REQ_MAP_START_RESPONSE_HPP_INCLUDED
