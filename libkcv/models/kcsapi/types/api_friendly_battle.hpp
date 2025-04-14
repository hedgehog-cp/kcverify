#ifndef KCVERIFY_KCSAPI_TYPES_API_FRIENDLY_BATTLE_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_API_FRIENDLY_BATTLE_HPP_INCLUDED

// std
#include <tuple>

// kcv
#include "models/kcsapi/types/api_hougeki.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 友軍艦隊砲撃. 発動時のみ存在.
struct api_friendly_battle {
    /// @brief 照明弾投射艦インデックス. [2]. [0]=自軍, [1]=敵軍. 0基点. 投射しなければ-1.
    std::tuple<int, int> api_flare_pos;

    /// @brief 夜間砲雷撃戦.
    kcsapi::api_hougeki api_hougeki;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_API_FRIENDLY_BATTLE_HPP_INCLUDED
