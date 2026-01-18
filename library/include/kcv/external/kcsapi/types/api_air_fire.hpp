#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_AIR_FIRE_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_AIR_FIRE_HPP_INCLUDED

#include <cstdint>
#include <vector>

namespace kcv {
namespace kcsapi {

struct api_air_fire final {
    /// @brief 発動艦のインデックス. 0基点.
    std::int32_t api_idx;

    /// @brief 対空CI種別.
    ///
    ///  34ｼｭｶｯﾄｲﾝﾊｯｼｬ!
    ///
    /// \   /      \   /
    ///  \ /        \ /
    ///   V          V
    ///   凸٩(◦`꒳´◦)۶凸
    /// @note ちなみにあ
    std::int32_t api_kind;

    /// @brief 表示装備ID. [装備数].
    std::vector<std::int32_t> api_use_items;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_AIR_FIRE_HPP_INCLUDED
