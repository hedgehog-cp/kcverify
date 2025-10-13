#ifndef KCVERIFY_MODELS_KCSAPI_API_REQ_COMBINED_BATTLE_EC_MIDNIGHT_BATTLE_RESPONSE_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_API_REQ_COMBINED_BATTLE_EC_MIDNIGHT_BATTLE_RESPONSE_HPP_INCLUDED

// std
#include <array>
#include <cstdint>
#include <optional>
#include <tuple>
#include <vector>

// kcv
#include "models/kcsapi/types/api_friendly_battle.hpp"
#include "models/kcsapi/types/api_friendly_info.hpp"
#include "models/kcsapi/types/api_hougeki.hpp"
#include "models/kcsapi/types/enum/engagement.hpp"
#include "models/kcsapi/types/enum/formation.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"
#include "models/kcsapi/types/number.hpp"

namespace kcv {
namespace kcsapi {
namespace api_req_combined_battle {
namespace ec_midnight_battle {

/// @brief api_req_combined_battle/ec_midnight_battle.json
/// 通常艦隊/連合艦隊夜戦（敵連合艦隊）
struct response final {
    /// @brief 戦闘参加艦隊フラグ. [2]. [0]=味方側, [1]=敵側. 1=主力艦隊, 2=随伴艦隊.
    std::tuple<std::int32_t, std::int32_t> api_active_deck;

    /// @brief 環礁マスフラグ.
    std::optional<std::int32_t> api_atoll_cell;

    /// @brief 阻塞気球マスフラグ.
    std::int32_t api_balloon_cell;

    /// @brief 自軍の出撃艦隊ID. 取り得る値は{1, 2, 3, 4}など.
    std::int32_t api_deck_id;

    /// @brief 陣形と交戦形態. [0]=自軍, [1]=敵軍, [2]=交戦形態.
    std::tuple<kcv::kcsapi::formation, kcv::kcsapi::formation, kcv::kcsapi::engagement> api_formation;

    /// @brief 自軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_fParam;

    /// @brief 自軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_fParam_combined;

    /// @brief 自軍の最大耐久. [艦船数].
    std::vector<std::int32_t> api_f_maxhps;

    /// @brief 自軍の現在耐久. [艦船数].
    std::vector<std::int32_t> api_f_nowhps;

    /// @brief 自軍の最大耐久. [艦船数].
    std::vector<std::int32_t> api_f_maxhps_combined;

    /// @brief 自軍の現在耐久. [艦船数].
    std::vector<std::int32_t> api_f_nowhps_combined;

    /// @brief 敵主力艦隊現在HP [13] (-1から始まる)
    std::vector<std::int32_t> api_e_nowhps;

    /// @brief 敵主力艦隊現在HP [13] (-1から始まる)
    std::vector<std::int32_t> api_e_nowhps_combined;

    /// @brief 敵主力艦隊現在HP [13] (-1から始まる)
    std::vector<std::int32_t> api_e_maxhps;

    /// @brief 敵主力艦隊現在HP [13] (-1から始まる)
    std::vector<std::int32_t> api_e_maxhps_combined;

    /// @brief 敵軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_eParam;

    /// @brief 敵軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_eParam_combined;

    /// @brief 退避艦インデックス. [退避艦数]. 1基点.
    std::optional<std::vector<std::int32_t>> api_escape_idx;

    /// @brief 敵主力艦隊装備IDリスト [6][5]
    std::vector<std::array<std::int32_t, 5>> api_eSlot;

    /// @brief 敵随伴艦隊装備IDリスト [6][5]
    std::vector<std::array<std::int32_t, 5>> api_eSlot_combined;

    /// @brief 退避艦インデックス. [退避艦数]. 1基点.
    std::optional<std::vector<std::int32_t>> api_escape_idx_combined;

    /// @brief 照明弾投射艦インデックス. [2]. [0]=自軍, [1]=敵軍. 0基点. 投射しなければ-1.
    std::tuple<std::int32_t, std::int32_t> api_flare_pos;

    /// @brief 友軍艦隊攻撃. 発動時のみ存在.
    std::optional<kcv::kcsapi::api_friendly_battle> api_friendly_battle;

    /// @brief 友軍艦隊攻撃情報. 発動時のみ存在.
    std::optional<kcv::kcsapi::api_friendly_info> api_friendly_info;

    /// @brief 夜間砲雷撃戦.
    std::optional<kcv::kcsapi::api_hougeki> api_hougeki;

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

    /// @brief 夜間触接機ID. [2]. [0]=自軍, [1]=敵軍. 触接しなければ-1.
    std::tuple<kcv::kcsapi::number, kcv::kcsapi::number> api_touch_plane;
};

}  // namespace ec_midnight_battle
}  // namespace api_req_combined_battle
}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_API_REQ_COMBINED_BATTLE_EC_MIDNIGHT_BATTLE_RESPONSE_HPP_INCLUDED
