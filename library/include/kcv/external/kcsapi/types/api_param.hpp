#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_PARAM_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_PARAM_HPP_INCLUDED

#include <cstddef>
#include <cstdint>
#include <tuple>

namespace kcv {
namespace kcsapi {

namespace detail {

/// @brief `api_param` の要素アクセス用の疑似scoped enum.
struct idx_param final {
    /// @note api_mst_shipの対応するメンバ名に倣った.
    enum _ : std::size_t {
        /// @brief 火力.
        houg,

        /// @brief 雷装.
        raig,

        /// @brief 対空.
        tyku,

        /// @brief 装甲.
        souk,
    };
};

}  // namespace detail

/// @brief api_paramの要素アクセス用の疑似scoped enum.
using idx_param = detail::idx_param::_;

/// @brief [0]=火力, [1]=雷装, [2]=対空, [3]=装甲.
using api_param = std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>;

static_assert(std::tuple_size_v<api_param> == 4);

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_PARAM_HPP_INCLUDED
