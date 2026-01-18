#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_MATERIAL_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_MATERIAL_HPP_INCLUDED

#include <cstdint>
namespace kcv {
namespace kcsapi {

/// @brief 保有資源情報.
struct api_material final {
    /// @brief 1から 燃料, 弾薬, 鋼材, ボーキサイト, 高速建造材, 高速修復材, 開発資材, 改修資材.
    std::int32_t api_id;

    /// @brief 提督ID.
    std::int32_t api_member_id;

    /// @brief 保有数.
    std::int32_t api_value;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_MATERIAL_HPP_INCLUDED
