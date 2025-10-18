#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_SUPPORT_AIRATACK_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_SUPPORT_AIRATACK_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <tuple>
#include <vector>

// kcv
#include "models/kcsapi/types/api_stage1.hpp"
#include "models/kcsapi/types/api_stage2.hpp"
#include "models/kcsapi/types/api_stage3.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 空撃もしくは対潜の時有効. それ以外はnull.
struct api_support_airatack final {
    /// @brief 支援艦隊の艦隊ID.
    std::int32_t api_deck_id;

    /// @brief 支援艦隊の編成艦ID. [6]. マスターIDではないので注意. 不在スロットは0.
    std::vector<std::int32_t> api_ship_id;

    /// @brief 中破グラフィックフラグ. [6]. 0=通常, 1=中破. 旗艦グラフィックは変化しない.
    std::vector<std::int32_t> api_undressing_flag;

    /// @brief 航空戦フラグ.
    std::tuple<std::int32_t, std::int32_t, std::int32_t> api_stage_flag;

    /// @brief 発艦可能艦. [2][]. [0]=味方, [1]=敵. いなければnull. 味方は常にnull?.
    std::vector<std::optional<std::vector<std::int32_t>>> api_plane_from;

    /// @brief 空対空戦闘.
    std::optional<kcv::kcsapi::api_stage1> api_stage1;

    /// @brief 艦対空戦闘.
    std::optional<kcv::kcsapi::api_stage2> api_stage2;

    /// @brief 航空攻撃　すべて[7].
    std::optional<kcv::kcsapi::api_stage3> api_stage3;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_SUPPORT_AIRATACK_HPP_INCLUDED
