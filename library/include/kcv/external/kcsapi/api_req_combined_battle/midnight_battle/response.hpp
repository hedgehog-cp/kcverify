#ifndef KCV_EXTERNAL_KCSAPI_API_REQ_COMBINED_BATTLE_MIDNIGHT_BATTLE_RESPONSE_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_API_REQ_COMBINED_BATTLE_MIDNIGHT_BATTLE_RESPONSE_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <tuple>
#include <vector>

// kcv
#include "kcv/external/kcsapi/types/api_hougeki.hpp"
#include "kcv/external/kcsapi/types/enum/engagement.hpp"
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"
#include "kcv/external/kcsapi/types/enum/formation.hpp"
#include "kcv/external/kcsapi/types/enum/ship_id.hpp"
#include "kcv/external/kcsapi/types/number.hpp"

namespace kcv {
namespace kcsapi {
namespace api_req_combined_battle {
namespace midnight_battle {

/// @brief api_req_combined_battle/midnight_battle.json.
/// 連合艦隊 vs 通常艦隊 夜戦.
struct response final {
    /// @brief 自軍の出撃艦隊ID. 1.
    std::int32_t api_deck_id;

    /// @brief 陣形と交戦形態. [0]=自軍, [1]=敵軍, [2]=交戦形態.
    std::tuple<kcv::kcsapi::formation, kcv::kcsapi::formation, kcv::kcsapi::engagement> api_formation;

    /// @brief 味方主力艦隊現在HP. [艦船数].
    std::vector<std::int32_t> api_f_nowhps;

    /// @brief 味方主力艦隊現在HP. [艦船数].
    std::vector<std::int32_t> api_f_maxhps;

    /// @brief 味方随伴艦隊現在HP. [艦船数].
    std::vector<std::int32_t> api_f_nowhps_combined;

    /// @brief 味方随伴艦隊現在HP. [艦船数].
    std::vector<std::int32_t> api_f_maxhps_combined;

    /// @brief 自軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_fParam;

    /// @brief 自軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_fParam_combined;

    /// @brief 敵主力艦隊艦船ID. [艦船数].
    std::vector<kcv::kcsapi::ship_id> api_ship_ke;

    /// @brief 敵主力艦隊Lv. [艦船数].
    std::vector<std::int32_t> api_ship_lv;

    /// @brief 敵主力艦隊現在HP. [艦船数].
    std::vector<std::int32_t> api_e_maxhps;

    /// @brief 敵主力艦隊現在HP. [艦船数].
    std::vector<std::int32_t> api_e_nowhps;

    /// @brief 敵主力艦隊装備IDリスト [艦船数][5]
    std::vector<std::array<kcv::kcsapi::equipment_id, 5>> api_eSlot;

    /// @brief 敵軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_eParam;

    /// @brief 退避艦インデックス. [退避艦数]. 1基点.
    std::optional<std::vector<std::int32_t>> api_escape_idx;

    /// @brief 退避艦インデックス. [退避艦数]. 1基点.
    std::optional<std::vector<std::int32_t>> api_escape_idx_combined;

    /// @brief 煙幕システム(2023/4/23~). 0=未使用|不発, 1,2,3=濃度. 現在, 夜戦では煙幕を展開しない.
    std::optional<std::int32_t> api_smoke_type;

    /// @brief 阻塞気球マスフラグ.
    std::int32_t api_balloon_cell;

    /// @brief 環礁マスフラグ.
    std::optional<std::int32_t> api_atoll_cell;

    /// @brief 夜間触接機ID. [2]. [0]=自軍, [1]=敵軍. 触接しなければ-1.
    std::tuple<kcv::kcsapi::number, kcv::kcsapi::number> api_touch_plane;

    /// @brief 照明弾投射艦インデックス. [2]. [0]=自軍, [1]=敵軍. 0基点. 投射しなければ-1.
    std::tuple<std::int32_t, std::int32_t> api_flare_pos;

    /// @brief 夜間砲雷撃戦.
    std::optional<kcv::kcsapi::api_hougeki> api_hougeki;
};

}  // namespace midnight_battle
}  // namespace api_req_combined_battle
}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_API_REQ_COMBINED_BATTLE_MIDNIGHT_BATTLE_RESPONSE_HPP_INCLUDED
