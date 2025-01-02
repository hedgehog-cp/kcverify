#ifndef KCVERIFY_kcsapi_TYPES_API_KYOUKA_HPP_INCLUDED
#define KCVERIFY_kcsapi_TYPES_API_KYOUKA_HPP_INCLUDED

#include <cstddef>
#include <tuple>

namespace kcv {
namespace kcsapi {

namespace detail {

/// @brief `api_kyouka` の要素アクセス用の疑似scoped enum.
struct idx_kyouka final {
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

        /// @brief 運.
        luck,

        /// @brief 耐久.
        taik,

        /// @brief 対潜.
        tais,
    };
};

}  // namespace detail

/// @brief api_kyoukaの要素アクセス用の疑似scoped enum.
using idx_kyouka = detail::idx_kyouka::_;

/// @brief [0]=火力, [1]=雷装, [2]=対空, [3]=装甲, [4]=運, [5]=耐久, [6]=対潜.
using api_kyouka = std::tuple<int, int, int, int, int, int, int>;

static_assert(std::tuple_size_v<api_kyouka> == 7);

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_kcsapi_TYPES_API_KYOUKA_HPP_INCLUDED
