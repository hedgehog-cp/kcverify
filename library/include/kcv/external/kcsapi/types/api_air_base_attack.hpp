#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_AIR_BASE_ATTACK_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_AIR_BASE_ATTACK_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <tuple>
#include <vector>

// kcv
#include "kcv/external/kcsapi/types/api_map_squadron_plane.hpp"
#include "kcv/external/kcsapi/types/api_squadron_plane.hpp"
#include "kcv/external/kcsapi/types/api_stage1.hpp"
#include "kcv/external/kcsapi/types/api_stage2.hpp"
#include "kcv/external/kcsapi/types/api_stage3.hpp"
#include "kcv/external/kcsapi/types/api_stage3_combined.hpp"
#include "kcv/external/kcsapi/types/api_stage_flag.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 基地航空隊攻撃.
struct api_air_base_attack_value_t final {
    /// @brief 航空隊ID.
    std::int32_t api_base_id;

    /// @brief 航空戦フラグ. [0]=api_stage1, [1]=api_stage2, [2]=api_stage3.
    kcv::kcsapi::api_stage_flag api_stage_flag;

    /// @brief 航空機発艦可能艦インデックス. [2][]. [0]=味方, [1]=敵. なければ null. 味方は常に null ?.
    std::tuple<std::optional<std::vector<std::int32_t>>, std::optional<std::vector<std::int32_t>>> api_plane_from;

    /// @brief 参加機リスト. 防空状態の基地が存在しない場合 null.
    std::optional<kcv::kcsapi::api_map_squadron_plane> api_map_squadron_plane;

    /// @brief 参加中隊情報. [参加中隊数].
    std::vector<kcv::kcsapi::api_squadoron_plane> api_squadron_plane;

    /// @brief 航空戦st.1.
    std::optional<kcv::kcsapi::api_stage1> api_stage1;

    /// @brief 航空戦st.2.
    std::optional<kcv::kcsapi::api_stage2> api_stage2;

    /// @brief 航空戦st.3.
    std::optional<kcv::kcsapi::api_stage3> api_stage3;

    /// @brief 航空戦st.3. 対随伴艦.
    std::optional<kcv::kcsapi::api_stage3_combined> api_stage3_combined;
};

/// @brief 基地航空隊攻撃. [攻撃回数].
using api_air_base_attack = std::vector<api_air_base_attack_value_t>;

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_AIR_BASE_ATTACK_HPP_INCLUDED
