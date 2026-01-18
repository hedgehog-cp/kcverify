#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_OPENING_ATACK_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_OPENING_ATACK_HPP_INCLUDED

#include <cstdint>
#include <optional>
#include <vector>

namespace kcv {
namespace kcsapi {

/// @brief 開幕雷撃戦.
struct api_opening_atack final {
    /// @brief 敵軍被ダメージ.
    std::vector<double> api_edam;

    /// @brief 自軍被ダメージ.
    std::vector<double> api_fdam;

    /// @brief 味方雷撃ターゲットのインデックス. [7][]. 特四式内火艇の2回攻撃に対応させるため. 不発はnull.
    std::vector<std::optional<std::vector<std::int32_t>>> api_frai_list_items;

    /// @brief 味方クリティカルフラグ. [7][]. 特四式内火艇の2回攻撃に対応させるため. null=ミス, 1=命中, 2=クリティカル.
    std::vector<std::optional<std::vector<std::int32_t>>> api_fcl_list_items;

    /// @brief 味方与ダメージ. [7][攻撃回数]. 特四式内火艇の2回攻撃に対応させるため.
    std::vector<std::optional<std::vector<std::int32_t>>> api_fydam_list_items;

    /// @brief 敵雷撃ターゲットのインデックス. [7].
    std::vector<std::optional<std::vector<std::int32_t>>> api_erai_list_items;

    /// @brief 敵クリティカルフラグ. [7].
    std::vector<std::optional<std::vector<std::int32_t>>> api_ecl_list_items;

    /// @brief 敵与ダメージ. [7].
    std::vector<std::optional<std::vector<std::int32_t>>> api_eydam_list_items;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_OPENING_ATACK_HPP_INCLUDED
