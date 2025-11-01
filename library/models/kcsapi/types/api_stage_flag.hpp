#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_STAGE_FLAG_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_STAGE_FLAG_HPP_INCLUDED

#include <cstddef>
#include <cstdint>
#include <tuple>

namespace kcv {
namespace kcsapi {

namespace detail {

/// @brief `api_stage_flag` の要素アクセス用の疑似scoped enum.
struct idx_stage_flag final {
    enum _ : std::size_t {
        /// @brief 空対空戦闘.
        stage1 = 0,

        /// @brief 対空砲火.
        stage2 = 1,

        /// @brief 航空攻撃.
        stage3 = 2,
    };
};

}  // namespace detail

/// @brief `api_stage_flag` の要素アクセス用の疑似scoped enum.
using idx_stage_flag = detail::idx_stage_flag::_;

/// @brief 航空戦フラグ. [0]=api_stage1, [1]=api_stage2, [2]=api_stage3. 1または0.
using api_stage_flag = std::tuple<std::int32_t, std::int32_t, std::int32_t>;

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_STAGE_FLAG_HPP_INCLUDED
