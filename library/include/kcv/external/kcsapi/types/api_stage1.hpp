#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_STAGE1_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_STAGE1_HPP_INCLUDED

// std
#include <cstdint>
#include <tuple>

// kcv
#include "kcv/external/kcsapi/types/enum/air_state.hpp"
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 航空戦st.1
struct api_stage1 final {
    /// @brief 制空状態
    air_state api_disp_seiku;

    /// @brief 敵軍参加機数
    std::int32_t api_e_count;

    /// @brief 敵軍被撃墜数
    std::int32_t api_e_lostcount;

    /// @brief 自軍参加機数
    std::int32_t api_f_count;

    /// @brief 自軍被撃墜数
    std::int32_t api_f_lostcount;

    /// @brief 触接機装備ID
    std::tuple<kcv::kcsapi::equipment_id, kcv::kcsapi::equipment_id> api_touch_plane;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_STAGE1_HPP_INCLUDED
