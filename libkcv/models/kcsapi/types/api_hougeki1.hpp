#ifndef KCVERIFY_KCSAPI_TYPES_API_HOUGEKI1_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_API_HOUGEKI1_HPP_INCLUDED

// std
#include <optional>
#include <string>
#include <variant>
#include <vector>

// kcv
#include "models/kcsapi/types/enum/day_attack_kind.hpp"
#include "models/kcsapi/types/enum/fleet_flag.hpp"

namespace kcv {
namespace kcsapi {

struct api_hougeki1 final {
    /// @brief 行動陣営フラグ. 0=自軍, 1=敵軍.
    std::vector<fleet_flag> api_at_eflag;

    /// @brief 攻撃艦のインデックス. 0基点.
    std::vector<int> api_at_list;

    /// @brief 攻撃種別.
    std::vector<day_attack_kind> api_at_type;

    /// @brief cLiticalフラグ. [][攻撃回数]. 0=miss, 1=命中, 2=cLitical. 単発CIでは[フラグ, -1, -1].
    std::vector<std::vector<int>> api_cl_list;

    /// @brief 与ダメージ. [][攻撃回数]. 単発CIでは[ダメージ, -1, -1]. かばいのとき, (ダメージ += 0.1).
    std::vector<std::vector<double>> api_damage;

    /// @brief 防御艦のインデックス. [][攻撃対象数]. 0基点. 単発CIでは[防御艦, -1, -1].
    std::vector<std::vector<int>> api_df_list;

    /// @brief 表示装備ID. [][装備数].
    std::optional<std::vector<std::vector<std::variant<int, std::string>>>> api_si_list;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_API_HOUGEKI1_HPP_INCLUDED
