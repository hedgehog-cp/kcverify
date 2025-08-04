#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_TYPE_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_TYPE_HPP_INCLUDED

// std
#include <cstddef>
#include <cstdint>
#include <tuple>

// kcv
#include "models/kcsapi/types/enum/category.hpp"
#include "models/kcsapi/types/enum/icon.hpp"

namespace kcv {
namespace kcsapi {

namespace detail {

/// @brief `api_mst_slotitem` の `api_type` の要素アクセス用の疑似scoped enum.
struct idx_type final {
    /// @note 意訳.
    enum _ : std::size_t {
        /// @brief 大分類.
        broad,

        /// @brief 図鑑表示.
        catalog,

        /// @brief カテゴリ.
        category,

        /// @brief アイコン.
        icon,

        /// @brief 航空機グラフィック.
        aircraft_graphic,
    };
};

}  // namespace detail

/// @brief `api_mst_slotitem` の `api_kyouka` の要素アクセス用の疑似scoped enum.
using idx_type = detail::idx_type::_;

/// @brief `api_mst_slotitem` の `api_type`.
using api_type = std::tuple<std::int32_t, std::int32_t, category, icon, std::int32_t>;

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_TYPE_HPP_INCLUDED
