#ifndef KCVERIFY_KCAPI_TYPES_API_SP_EFFECTITEMS_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_SP_EFFECTITEMS_HPP_INCLUDED

// std
#include <vector>

// kcv
#include "kcapi/types/enum/sp_effect_item.hpp"

namespace kcv {
namespace kcapi {

/// @brief 特注アイテム.
struct api_sp_effect_items_value_type final {
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

using api_sp_effect_items = std::vector<api_sp_effect_items_value_type>;

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_SP_EFFECTITEMS_HPP_INCLUDED
