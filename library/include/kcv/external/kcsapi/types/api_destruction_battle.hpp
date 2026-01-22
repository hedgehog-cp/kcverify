#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_DESTRUCTION_BATTLE_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_DESTRUCTION_BATTLE_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <tuple>
#include <vector>

// kcv
#include "kcv/external/kcsapi/types/api_air_base_attack.hpp"
#include "kcv/external/kcsapi/types/enum/engagement.hpp"
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"
#include "kcv/external/kcsapi/types/enum/formation.hpp"
#include "kcv/external/kcsapi/types/enum/lost_kind.hpp"
#include "kcv/external/kcsapi/types/enum/ship_id.hpp"
#include "kcv/external/kcsapi/types/number.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 基地防空戦.
struct api_destruction_battle final {
    /// @brief 陣形と交戦形態. [0]=自軍, [1]=敵軍, [2]=交戦形態.
    std::tuple<kcv::kcsapi::formation, kcv::kcsapi::formation, kcv::kcsapi::engagement> api_formation;

    /// @brief 敵艦船ID. [艦船数].
    std::vector<kcv::kcsapi::ship_id> api_ship_ke;

    /// @brief 敵艦船Lv. [艦船数].
    std::vector<std::int32_t> api_ship_lv;

    /// @brief 敵軍の最大耐久. [艦船数].
    std::vector<kcv::kcsapi::number> api_e_maxhps;

    /// @brief 敵軍の現在耐久. [艦船数].
    std::vector<kcv::kcsapi::number> api_e_nowhps;

    // 存在しない.
    // 敵軍の基礎ステータス. [艦船数]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    // std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_eParam;

    /// @brief 敵軍の装備スロット. [艦船数][5]. 空きスロットには-1.
    std::vector<std::array<kcv::kcsapi::equipment_id, 5>> api_eSlot;

    /// @brief 自軍の最大耐久. [艦船数].
    std::vector<std::int32_t> api_f_maxhps;

    /// @brief 自軍の現在耐久. [艦船数].
    std::vector<std::int32_t> api_f_nowhps;

    /// @brief 基地航空隊攻撃.
    std::optional<kcv::kcsapi::api_air_base_attack_value_t> api_air_base_attack;

    /// @brief 基地被害状況.
    kcv::kcsapi::lost_kind api_lost_kind;

    /// @brief ('16秋イベ)ギミック解除フラグ. 1=解除(段階によって1以外の場合もある). それ以外の場合存在しない.
    std::optional<std::int32_t> api_m1;

    /// @brief ('19夏イベ)ギミック解除フラグ. 1=解除(〃). それ以外の場合存在しない.
    std::optional<std::int32_t> api_m2;

    /// @brief ('22冬イベ)基地航空隊の位置ギミックフラグ. EventMapUtil.getCellOpenOptionによるとapi_m1も一緒に基地位置を決めるっぽい?
    std::optional<std::int32_t> api_m10;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_DESTRUCTION_BATTLE_HPP_INCLUDED
