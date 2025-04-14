#ifndef KCVERIFY_KCSAPI_TYPES_API_SP_EFFECTITEMS_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_API_SP_EFFECTITEMS_HPP_INCLUDED

// std
#include <vector>

// kcv
#include "models/kcsapi/types/enum/sp_effect_item.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 特注アイテム.
struct api_sp_effect_items_value_t final {
    /// @brief 特注アイテム.
    sp_effect_item api_kind;

    /// @brief 火力.
    int api_houg;

    /// @brief 雷装.
    int api_raig;

    /// @brief 装甲.
    int api_soku;

    /// @brief 回避.
    int api_kaihi;
};

using api_sp_effect_items = std::vector<api_sp_effect_items_value_t>;

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_API_SP_EFFECTITEMS_HPP_INCLUDED
