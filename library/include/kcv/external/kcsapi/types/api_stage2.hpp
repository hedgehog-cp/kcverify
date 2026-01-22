#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_STAGE2_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_STAGE2_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>

// kcv
#include "kcv/external/kcsapi/types/api_air_fire.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 航空戦st.2
struct api_stage2 final {
    /// @brief 対空CI. 発動時のみ存在.
    std::optional<kcv::kcsapi::api_air_fire> api_air_fire;

    /// @brief 敵軍参加機数
    std::int32_t api_e_count;

    /// @brief 敵軍被撃墜数
    std::int32_t api_e_lostcount;

    /// @brief 自軍参加機数
    std::int32_t api_f_count;

    /// @brief 自軍被撃墜数
    std::int32_t api_f_lostcount;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_STAGE2_HPP_INCLUDED
