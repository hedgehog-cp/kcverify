#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_MAP_SQUADRON_PLANE_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_MAP_SQUADRON_PLANE_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

/// @brief 基地航空隊攻撃 参加機リスト.
/// @todo 命名規則違反に対応する.
struct api_map_squadron_plane final {
    // <index>    ：防空状態の基地インデックス（1基点）[参加機数]. 具体的には "3" など. 命名規則違反なので読み取り時注意.
    // api_mst_id ：参加機の装備ID
    // api_count  ：参加機数
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_MAP_SQUADRON_PLANE_HPP_INCLUDED
