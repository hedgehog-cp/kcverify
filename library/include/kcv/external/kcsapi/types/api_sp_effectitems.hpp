#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_SP_EFFECTITEMS_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_SP_EFFECTITEMS_HPP_INCLUDED

// std
#include <cstdint>
#include <vector>

// kcv
#include "kcv/external/kcsapi/types/enum/sp_effect_item.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 特注アイテム.
struct api_sp_effect_items_value_t final {
    /// @brief 特注アイテム.
    kcv::kcsapi::sp_effect_item api_kind;

    /// @brief 火力.
    std::int32_t api_houg;

    /// @brief 雷装.
    std::int32_t api_raig;

    /// @brief 装甲.
    std::int32_t api_soku;

    /// @brief 回避.
    std::int32_t api_kaihi;
};

using api_sp_effect_items = std::vector<api_sp_effect_items_value_t>;

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_SP_EFFECTITEMS_HPP_INCLUDED
