#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_AIR_FIRE_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_AIR_FIRE_HPP_INCLUDED

#include <vector>

namespace kcv {
namespace kcsapi {

struct api_air_fire final {
    /// @brief 発動艦のインデックス. 0基点.
    int api_idx;

    /// @brief 対空CI種別.
    ///
    ///  34ｼｭｶｯﾄｲﾝﾊｯｼｬ!
    ///
    /// \   /      \   /
    ///  \ /        \ /
    ///   V          V
    ///   凸٩(◦`꒳´◦)۶凸
    /// @note ちなみにあ
    int api_kind;

    /// @brief 表示装備ID. [装備数].
    std::vector<int> api_use_items;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_AIR_FIRE_HPP_INCLUDED
