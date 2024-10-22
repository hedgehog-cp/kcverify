#ifndef KCVERIFY_KCAPI_TYPES_API_RAIGEKI_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_RAIGEKI_HPP_INCLUDED

#include <vector>

namespace kcv {
namespace kcapi {

/// @brief 雷撃戦.
struct api_raigeki final {
    /// @brief 敵軍cLiticalフラグ.
    std::vector<int> api_ecl;

    /// @brief 敵軍被ダメージ.
    std::vector<double> api_edam;

    /// @brief 敵軍雷撃ターゲットのインデックス.
    std::vector<int> api_erai;

    /// @brief 敵軍与ダメージ.
    std::vector<int> api_eydam;

    /// @brief 自軍cLiticalフラグ.
    std::vector<int> api_fcl;

    /// @brief 自軍被ダメージ.
    std::vector<double> api_fdam;

    /// @brief 自軍雷撃ターゲットのインデックス.
    std::vector<int> api_frai;

    /// @brief 自軍与ダメージ.
    std::vector<int> api_fydam;
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_RAIGEKI_HPP_INCLUDED
