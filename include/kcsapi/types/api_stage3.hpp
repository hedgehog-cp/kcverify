#ifndef KCVERIFY_kcsapi_TYPES_API_STAGE3_HPP_INCLUDED
#define KCVERIFY_kcsapi_TYPES_API_STAGE3_HPP_INCLUDED

// std
#include <optional>
#include <vector>

// kcv
#include "kcsapi/types/enum/air_hit_type.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 航空戦st.3
struct api_stage3 final {
    /// @brief 敵軍被爆撃フラグ.
    std::vector<int> api_ebak_flag;

    /// @brief 敵軍被cLiticalフラグ.
    std::vector<air_hit_type> api_ecl_flag;

    /// @brief 敵軍被ダメージ.
    std::vector<double> api_edam;

    /// @brief 敵軍被雷撃フラグ.
    std::vector<int> api_erai_flag;

    // ?
    // 敵喰らった特殊攻撃種類[]. null / [0] = なし, [1] = 反跳爆撃. 同時に ebak_flag も立つ.
    std::vector<std::optional<int>> api_e_sp_list;

    /// @brief 自軍被爆撃フラグ.
    std::vector<std::optional<int>> api_fbak_flag;

    /// @brief 自軍被cLiticalフラグ.
    std::vector<air_hit_type> api_fcl_flag;

    /// @brief 自軍被ダメージ.
    std::vector<double> api_fdam;

    /// @brief 自軍被雷撃フラグ.
    std::vector<int> api_frai_flag;

    // ?
    // 味方喰らった特殊攻撃種類[]. null/[0]=なし, [1]=反跳爆撃. 同時に fbak_flag も立つ.
    std::vector<std::optional<int>> api_f_sp_list;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_kcsapi_TYPES_API_STAGE3_HPP_INCLUDED
