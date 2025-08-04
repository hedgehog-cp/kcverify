#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_RAIGEKI_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_RAIGEKI_HPP_INCLUDED

#include <cstdint>
#include <vector>

namespace kcv {
namespace kcsapi {

/// @brief 雷撃戦.
struct api_raigeki final {
    /// @brief 敵軍cLiticalフラグ.
    std::vector<std::int32_t> api_ecl;

    /// @brief 敵軍被ダメージ.
    std::vector<double> api_edam;

    /// @brief 敵軍雷撃ターゲットのインデックス.
    std::vector<std::int32_t> api_erai;

    /// @brief 敵軍与ダメージ.
    std::vector<std::int32_t> api_eydam;

    /// @brief 自軍cLiticalフラグ.
    std::vector<std::int32_t> api_fcl;

    /// @brief 自軍被ダメージ.
    std::vector<double> api_fdam;

    /// @brief 自軍雷撃ターゲットのインデックス.
    std::vector<std::int32_t> api_frai;

    /// @brief 自軍与ダメージ.
    std::vector<std::int32_t> api_fydam;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_RAIGEKI_HPP_INCLUDED
