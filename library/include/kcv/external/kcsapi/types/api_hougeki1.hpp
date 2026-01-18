#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_HOUGEKI1_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_HOUGEKI1_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "kcv/external/kcsapi/types/enum/day_attack_kind.hpp"
#include "kcv/external/kcsapi/types/enum/fleet_flag.hpp"
#include "kcv/external/kcsapi/types/number.hpp"

namespace kcv {
namespace kcsapi {

struct api_hougeki1 final {
    /// @brief 行動陣営フラグ. 0=自軍, 1=敵軍.
    std::vector<kcv::kcsapi::fleet_flag> api_at_eflag;

    /// @brief 攻撃艦のインデックス. 0基点.
    std::vector<std::int32_t> api_at_list;

    /// @brief 攻撃種別.
    std::vector<kcv::kcsapi::day_attack_kind> api_at_type;

    /// @brief cLiticalフラグ. [][攻撃回数]. 0=miss, 1=命中, 2=cLitical. 単発CIでは[フラグ, -1, -1].
    std::vector<std::vector<std::int32_t>> api_cl_list;

    /// @brief 与ダメージ. [][攻撃回数]. 単発CIでは[ダメージ, -1, -1]. かばいのとき, (ダメージ += 0.1).
    std::vector<std::vector<double>> api_damage;

    /// @brief 防御艦のインデックス. [][攻撃回数]. 0基点. 単発CIでは[防御艦, -1, -1].
    std::vector<std::vector<std::int32_t>> api_df_list;

    /// @brief 表示装備ID. [][装備数].
    std::optional<std::vector<std::vector<kcv::kcsapi::number>>> api_si_list;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_HOUGEKI1_HPP_INCLUDED
