#ifndef KCVERIFY_KCAPI_TYPES_API_STAGE1_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_STAGE1_HPP_INCLUDED

// std
#include <tuple>

// kcv
#include "kcapi/types/enum/air_state.hpp"
#include "kcapi/types/enum/equipment_id.hpp"

namespace kcv {
namespace kcapi {

/// @brief 航空戦st.1
struct api_stage1 final {
    /// @brief 制空状態
    air_state api_disp_seiku;

    /// @brief 敵軍参加機数
    int api_e_count;

    /// @brief 敵軍被撃墜数
    int api_e_lostcount;

    /// @brief 自軍参加機数
    int api_f_count;

    /// @brief 自軍被撃墜数
    int api_f_lostcount;

    /// @brief 触接機装備ID
    std::tuple<equipment_id, equipment_id> api_touch_plane;
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_STAGE1_HPP_INCLUDED
