#ifndef KCVERIFY_KCSAPI_TYPES_API_SHIP_DATA_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_API_SHIP_DATA_HPP_INCLUDED

#include <cstdint>
#include <optional>
#include <tuple>
#include <vector>

#include "kcsapi/types/enum/ship_id.hpp"
#include "kcsapi/types/enum/sp_effect_item.hpp"

namespace kcv {
namespace kcsapi {

struct api_ship_data_value_t final {
    /// @brief レアリティ. 1=藍, 2=青, 3=水, 4=銀, 5=金, 6=虹, 7=輝虹, 8=桜虹
    int api_backs;

    /// @brief 搭載弾薬.
    int api_bull;

    /// @brief 疲労度.
    int api_cond;

    /// @brief 経験値. [0]=累積, [1]=次のレベルまで, [2]=経験値バー割合.
    /// @note intは16bit以上であるため, 32767を超える経験値を扱えない.
    std::tuple<std::int_least32_t, std::int_least32_t, int> api_exp;

    /// @brief 搭載燃料.
    int api_fuel;

    /// @brief 艦船固有ID. 着任順.
    std::int_least32_t api_id;

    /// @brief 回避.
    std::tuple<int, int> api_kaihi;

    /// @brief 火力.
    std::tuple<int, int> api_karyoku;

    /// @brief 近代化改修. [0]=火力, [1]=雷装, [2]=対空, [3]=装甲, [4]=運, [5]=耐久, [6]=対潜.
    std::tuple<int, int, int, int, int, int, int> api_kyouka;

    /// @brief 射程.
    int api_leng;

    /// ロックされているか.
    int api_locked;

    /// @brief ロックされている装備を装備しているか.
    int api_locked_equip;

    /// @brief 運.
    std::tuple<int, int> api_lucky;

    /// @brief レベル.
    int api_lv;

    /// @brief 最大耐久.
    int api_maxhp;

    /// @brief 入渠時の消費資源. [0]=燃料, [1]=鋼材.
    std::tuple<int, int> api_ndock_item;

    /// @brief 入渠時間(ミリ秒).
    /// @note 3day = 259200000ms
    std::int_least32_t api_ndock_time;

    /// @brief 現在耐久.
    int api_nowhp;

    /// @brief 艦載機搭載数.
    std::vector<int> api_onslot;

    /// @brief 雷装.
    std::tuple<int, int> api_raisou;

    /// @brief 索敵.
    std::tuple<int, int> api_sakuteki;

    /// @brief 出撃海域. イベント中のみ存在.
    std::optional<int> api_sally_area;

    /// @brief 艦船ID.
    kcsapi::ship_id api_ship_id;

    /// @brief 装備固有ID. -1=空き.
    std::vector<std::int_least32_t> api_slot;

    /// @brief 補強増設. 0=未解放, -1=未装備.
    std::int_least32_t api_slot_ex;

    /// @brief スロット数. 補強増設は含めない.
    int api_slotnum;

    /// @brief 速力. 0=基地, 5=低速, 10=高速, 15=高速+, 20=最速.
    int api_soku;

    /// @brief 図鑑番号.
    int api_sortno;

    /// @brief 装甲.
    std::tuple<int, int> api_soukou;

    /// @brief 近代化改修の達成度★?
    int api_srate;

    /// @brief 対空.
    std::tuple<int, int> api_taiku;

    /// @brief 対潜.
    std::tuple<int, int> api_taisen;

    /// @brief リボンや襷付与された場合のみ存在.
    std::vector<kcsapi::sp_effect_item> api_sp_effect_items;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_API_SHIP_DATA_HPP_INCLUDED
