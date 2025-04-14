#ifndef KCVERIFY_KCSAPI_TYPES_API_AIRSEARCH_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_API_AIRSEARCH_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

/// @brief 航空偵察.
struct api_airsearch final {
    /// @brief 発艦した索敵機の種別. 0=なし, 1=大型飛行艇, 2=水上偵察機.
    int api_plane_type;

    /// @brief 偵察結果. 0=失敗, 1=成功, 2=大成功.
    int api_result;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_API_AIRSEARCH_HPP_INCLUDED
