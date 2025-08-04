#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_FRIENDLY_INFO_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_FRIENDLY_INFO_HPP_INCLUDED

// std
#include <cstdint>
#include <tuple>
#include <vector>

// kcv
#include "models/kcsapi/types/enum/ship_id.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 友軍艦隊攻撃情報. 発動時のみ存在.
struct api_friendly_info {
    /// @brief 艦隊ID?. 1=英仏艦隊, 2=第十九駆逐隊, 挺身部隊, 3=第四戦隊.
    std::int32_t api_production_type;

    /// @brief 友軍の艦船ID. [艦船数].
    std::vector<ship_id> api_ship_id;

    /// @brief 友軍のLv. [艦船数].
    std::vector<std::int32_t> api_ship_lv;

    /// @brief 友軍の現在HP. [艦船数].
    std::vector<std::int32_t> api_nowhps;

    /// @brief 友軍の最大HP. [艦船数].
    std::vector<std::int32_t> api_maxhps;

    /// @brief 友軍の装備スロット. [艦船数][5]. 空きロットのとき-1.
    std::vector<std::vector<std::int32_t>> api_Slot;

    /// @brief 友軍の装備(拡張スロット). [艦船数].
    std::vector<std::int32_t> api_slot_ex;

    /// @brief 友軍の基礎ステータス. [艦船数][4]. [][0]=火力, [][1]=雷装, [][2]=対空, [][3]=装甲.
    std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>> api_Param;

    /// @brief 再生されるボイスID?. [艦船数].
    std::vector<std::int32_t> api_voice_id;

    /// @brief 1>=戦闘前口上あり(口上の順番?), 0=なし. [艦船数].
    std::vector<std::int32_t> api_voice_p_no;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_FRIENDLY_INFO_HPP_INCLUDED
