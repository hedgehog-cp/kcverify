#ifndef KCVERIFY_KCSAPI_TYPES_API_RESOURCE_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_API_RESOURCE_HPP_INCLUDED

#include <array>
#include <cstddef>

namespace kcv {
namespace kcsapi {

namespace detail {

/// @brief `api_resource` の要素アクセス用scoped enum.
struct idx_resource final {
    enum _ : std::size_t {
        /// @brief 燃料.
        fule,

        /// @brief 弾薬.
        ammo,

        /// @brief 鋼材.
        steel,

        /// @brief ボーキサイト.
        bauxite,
    };
};

}  // namespace detail

/// @brief `api_resource` の要素アクセス用scoped enum.
using idx_resource = detail::idx_resource::_;

/// @brief [0]=燃料. [1]=弾薬. [2]=鋼材. [3]=ボーキサイト.
/// @note std::tupleにするとclangでコンパイルできない.
using api_resource = std::array<int, 4>;

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_API_RESOURCE_HPP_INCLUDED
