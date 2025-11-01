#ifndef KCVERIFY_MODELS_KCSAPI_API_REQ_COMBINED_BATTLE_LD_AIRBATTLE_RESPONSE_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_API_REQ_COMBINED_BATTLE_LD_AIRBATTLE_RESPONSE_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <tuple>
#include <vector>

// kcv
#include "models/kcsapi/types/api_kouku.hpp"
#include "models/kcsapi/types/enum/detection_type.hpp"
#include "models/kcsapi/types/enum/engagement.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"
#include "models/kcsapi/types/enum/formation.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"
#include "models/kcsapi/types/number.hpp"

namespace kcv {
namespace kcsapi {
namespace api_req_combined_battle {
namespace ld_airbattle {

/// @brief api_req_combined_battle/ld_airbattle.json.
/// 連合艦隊 長距離空襲戦.
struct response final {
    /// @brief 自軍の出撃艦 隊ID.
    std::int32_t api_deck_id;

    /// @brief 陣形と交戦形態. [0]=自軍, [1]=敵軍, [2]=交戦形態.
    std::tuple<kcv::kcsapi::formation, kcv::kcsapi::formation, kcv::kcsapi::engagement> api_formation;

    /// @brief 自軍の現在耐久. [艦船数].
    std::vector<std::int32_t> api_f_nowhps;

    /// @brief 自軍の最大耐久. [艦船数].
    std::vector<std::int32_t> api_f_maxhps;

    /// @brief 自軍の現在耐久. [艦船数].
    std::vector<std::int32_t> api_f_nowhps_combined;

    /// @brief 自軍の最大耐久. [艦船数].
    std::vector<std::int32_t> api_f_maxhps_combined;

    /// @brief 自軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装 甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_fParam;

    /// @brief 自軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装 甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_fParam_combined;

    /// @brief 敵艦船ID. [艦船数].
    std::vector<kcv::kcsapi::ship_id> api_ship_ke;

    /// @brief 敵艦船Lv. [艦船数].
    std::vector<std::int32_t> api_ship_lv;

    /// @brief 敵軍の現在耐久. [艦船数].
    std::vector<kcv::kcsapi::number> api_e_nowhps;

    /// @brief 敵軍の最大耐久. [艦船数].
    std::vector<kcv::kcsapi::number> api_e_maxhps;

    /// @brief 敵軍の装備スロット. [艦船数][5]. 空きスロットには-1.
    std::vector<std::array<kcv::kcsapi::equipment_id, 5>> api_eSlot;

    /// @brief 敵軍の基礎ステータス. [艦船数]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_eParam;

    /// @brief 煙幕システム(2023/4/23~). 0=未 使用|不発, 1,2,3=濃度. 現在, 夜戦では煙幕を展開しない.
    std::optional<std::int32_t> api_smoke_type;

    /// @brief 阻塞気球マスフラグ.
    std::int32_t api_balloon_cell;

    /// @brief 環礁マスフラグ.
    std::optional<std::int32_t> api_atoll_cell;

    /// @brief 夜戦突入可否. 0=不可(昼戦で敵全滅など), 1=可能.
    std::int32_t api_midnight_flag;

    /// @brief 退避艦インデックス. [退避艦数]. 1基点.
    std::optional<std::vector<std::int32_t>> api_escape_idx;

    /// @brief 退避艦インデックス. [退避艦数]. 1基点.
    std::optional<std::vector<std::int32_t>> api_escape_idx_coombined;

    /// @brief 戦闘糧食補給. 発動時のみ存在. 艦船IDの配列
    std::optional<std::vector<kcv::kcsapi::ship_id>> api_combat_ration;

    /// @brief 戦闘糧食補給. 発動時のみ存在. 艦船IDの配列
    std::optional<std::vector<kcv::kcsapi::ship_id>> api_combat_ration_combined;

    /// @brief 索敵成否, [0]=自軍, [1]=敵軍. 1=成功, 2=成功(未帰還機あり), 3=未帰還 , 4=失敗, 5=発見, 6=発見できず.
    std::tuple<kcv::kcsapi::detection_type, kcv::kcsapi::detection_type> api_search;

    /// @brief 航空戦フラグ. [3].
    std::tuple<std::int32_t, std::int32_t, std::int32_t> api_stage_flag;

    /// @brief 航空戦情報.
    std::optional<kcv::kcsapi::api_kouku> api_kouku;
};

}  // namespace ld_airbattle
}  // namespace api_req_combined_battle
}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_API_REQ_COMBINED_BATTLE_LD_AIRBATTLE_RESPONSE_HPP_INCLUDED
