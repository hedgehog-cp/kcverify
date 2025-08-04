#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_HAPPENING_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_HAPPENING_HPP_INCLUDED

#include <cstdint>

#include "models/kcsapi/types/enum/maelstrom.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 渦潮マス.
struct api_happeing final {
    // 1
    std::int32_t api_type;

    /// @brief 落とした資源の量.
    std::int32_t api_count;

    // 4
    std::int32_t api_usemst;

    /// @brief 渦潮. 落とした資源の種類.
    kcv::kcsapi::maelstrom api_mst_id;

    /// @brief 表示アイコンID. 2=弾薬.
    std::int32_t api_icon_id;

    /// @brief 電探による被害軽減フラグ. 1=軽減.
    std::int32_t api_dentan;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_HAPPENING_HPP_INCLUDED
