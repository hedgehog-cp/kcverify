#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_LANDING_HP_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_LANDING_HP_HPP_INCLUDED

// std
#include <string>

// kcv
#include "kcv/external/kcsapi/types/number.hpp"

namespace kcv {
namespace kcsapi {

/// @brief TP輸送量.
struct api_landing_hp final {
    /// @brief 現在のTP(減少前).
    std::string api_now_hp;

    /// @brief 最大TP.
    std::string api_max_hp;

    /// @brief 減少したTP.
    kcv::kcsapi::number api_sub_value;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_LANDING_HP_HPP_INCLUDED
