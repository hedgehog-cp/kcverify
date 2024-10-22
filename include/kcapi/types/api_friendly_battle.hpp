#ifndef KCVERIFY_KCAPI_TYPES_API_FRIENDLY_BATTLE_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_FRIENDLY_BATTLE_HPP_INCLUDED

// std
#include <tuple>

// kcv
#include "kcapi/types/api_hougeki.hpp"

namespace kcv {
namespace kcapi {

/// @brief 友軍艦隊砲撃. 発動時のみ存在.
struct api_friendly_battle {
    /// @brief 照明弾投射艦インデックス. [2]. [0]=自軍, [1]=敵軍. 0基点. 投射しなければ-1.
    std::tuple<int, int> api_flare_pos;

    /// @brief 夜間砲雷撃戦.
    kcapi::api_hougeki api_hougeki;
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_FRIENDLY_BATTLE_HPP_INCLUDED
