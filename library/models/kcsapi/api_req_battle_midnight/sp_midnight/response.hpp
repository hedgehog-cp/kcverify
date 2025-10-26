#ifndef KCVERIFY_MODELS_KCSAPI_API_REQ_BATTLE_MIDNIGHT_SP_MIDNIGHT_RESPONSE_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_API_REQ_BATTLE_MIDNIGHT_SP_MIDNIGHT_RESPONSE_HPP_INCLUDED

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
#include "models/kcsapi/types/api_support_info.hpp"
#include "models/kcsapi/types/enum/engagement.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"
#include "models/kcsapi/types/enum/formation.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"
#include "models/kcsapi/types/enum/support_type.hpp"
#include "models/kcsapi/types/number.hpp"

namespace kcv {
namespace kcsapi {
namespace api_req_battle_midnight {
namespace sp_midnight {

/// @brief api_req_battle_midnight/sp_midnight.json
/// 通常艦隊開幕夜戦
struct response final {
    /// @brief 環礁マスフラグ.
    std::optional<std::int32_t> api_atoll_cell;

    /// @brief 阻塞気球マスフラグ.
    std::int32_t api_balloon_cell;

    /// @brief 戦闘糧食補給. 発動時のみ存在. 艦船IDの配列
    std::optional<std::vector<kcv::kcsapi::ship_id>> api_combat_ration;

    /// @brief 自軍の出撃艦隊ID. 取り得る値は{1, 2, 3, 4}など.
    std::int32_t api_deck_id;

    /// @brief 敵軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_eParam;

    /// @brief 退避艦インデックス. [退避艦数]. 1基点.
    std::optional<std::vector<std::int32_t>> api_escape_idx;

    /// @brief 敵軍の装備スロット. [艦船数][5]. 空きスロットには-1.
    std::vector<std::array<kcv::kcsapi::equipment_id, 5>> api_eSlot;

    /// @brief 敵軍の最大耐久. [艦船数].
    std::vector<kcv::kcsapi::number> api_e_maxhps;

    /// @brief 敵軍の現在耐久. [艦船数].
    std::vector<kcv::kcsapi::number> api_e_nowhps;

    /// @brief 友軍艦隊攻撃. 発動時のみ存在.
    std::optional<kcv::kcsapi::api_friendly_battle> api_friendly_battle;

    /// @brief 友軍艦隊攻撃情報. 発動時のみ存在.
    std::optional<kcv::kcsapi::api_friendly_info> api_friendly_info;

    /// @brief 自軍の最大耐久. [艦船数].
    std::vector<std::int32_t> api_f_maxhps;

    /// @brief 自軍の現在耐久. [艦船数].
    std::vector<std::int32_t> api_f_nowhps;

    /// @brief 照明弾投射艦インデックス. [2]. [0]=自軍, [1]=敵軍. 0基点. 投射しなければ-1.
    std::tuple<std::int32_t, std::int32_t> api_flare_pos;

    /// @brief 陣形と交戦形態. [0]=自軍, [1]=敵軍, [2]=交戦形態.
    std::tuple<kcv::kcsapi::formation, kcv::kcsapi::formation, kcv::kcsapi::engagement> api_formation;

    /// @brief 自軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_fParam;

    /// @brief 夜間砲雷撃戦.
    std::optional<kcv::kcsapi::api_hougeki> api_hougeki;

    /// @brief 支援艦隊フラグ. 0=なし, 1=空撃, 2=砲撃, 3=雷撃, 4=対潜.
    kcv::kcsapi::support_type api_n_support_flag;

    /// @brief 支援艦隊情報. api_support_flag==0のときnull.
    std::optional<kcv::kcsapi::api_support_info> api_n_support_info;

    /// @brief 敵艦船ID. [艦船数].
    std::vector<kcv::kcsapi::ship_id> api_ship_ke;

    /// @brief 敵艦船Lv. [艦船数].
    std::vector<std::int32_t> api_ship_lv;

    /// @brief 煙幕システム(2023/4/23~). 0=未使用|不発, 1,2,3=濃度. 現在, 夜戦では煙幕を展開しない.
    std::optional<std::int32_t> api_smoke_type;

    /// @brief 夜間触接機ID. [2]. [0]=自軍, [1]=敵軍. 触接しなければ-1.
    std::tuple<kcv::kcsapi::number, kcv::kcsapi::number> api_touch_plane;

    /// @brief 装甲破砕フラグ.
    std::optional<std::int32_t> api_x_al01;
};

}  // namespace sp_midnight
}  // namespace api_req_battle_midnight
}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_API_REQ_BATTLE_MIDNIGHT_SP_MIDNIGHT_RESPONSE_HPP_INCLUDED
