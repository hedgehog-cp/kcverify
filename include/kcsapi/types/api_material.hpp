#ifndef KCVERIFY_KCSAPI_TYPES_API_MATERIAL_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_API_MATERIAL_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

/// @brief 保有資源情報.
struct api_material final {
    /// @brief 1から 燃料, 弾薬, 鋼材, ボーキサイト, 高速建造材, 高速修復材, 開発資材, 改修資材.
    int api_id;

    /// @brief 提督ID.
    int api_member_id;

    /// @brief 保有数.
    int api_value;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_API_MATERIAL_HPP_INCLUDED
