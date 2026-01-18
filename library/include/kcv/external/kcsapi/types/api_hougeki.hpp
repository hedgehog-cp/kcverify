#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_HOUGEKI_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_HOUGEKI_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "kcv/external/kcsapi/types/enum/fleet_flag.hpp"
#include "kcv/external/kcsapi/types/enum/night_attack_kind.hpp"
#include "kcv/external/kcsapi/types/number.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 夜間砲雷撃戦. 彼我ともに攻撃しなければ, 全てのメンバはnullつまりstd::nullopt保持する.
/// 全てのメンバの有効値の1次元目の配列サイズは, 攻撃回数.
struct api_hougeki final {
    /// @brief 行動陣営フラグ. 0=自軍, 1=敵軍.
    std::optional<std::vector<kcv::kcsapi::fleet_flag>> api_at_eflag;

    /// @brief 攻撃艦のインデックス. 0基点.
    std::optional<std::vector<std::int32_t>> api_at_list;

    /// @brief cLiticalフラグ. [][攻撃回数]. 0=miss, 1=命中, 2=cLitical. 単発CIでは[フラグ, -1, -1].
    std::optional<std::vector<std::vector<std::int32_t>>> api_cl_list;

    /// @brief 与ダメージ. [][攻撃回数]. 単発CIでは[ダメージ, -1, -1]. かばいのとき, (ダメージ += 0.1).
    std::optional<std::vector<std::vector<double>>> api_damage;

    /// @brief 防御艦のインデックス. [][攻撃対象数]. 0基点. 単発CIでは[防御艦, -1, -1].
    std::optional<std::vector<std::vector<std::int32_t>>> api_df_list;

    /// @brief 夜間空母攻撃フラグ.
    std::optional<std::vector<std::int32_t>> api_n_mother_list;

    /// @brief 表示装備ID. [][装備数].
    std::optional<std::vector<std::vector<kcv::kcsapi::number>>> api_si_list;

    /// @brief 攻撃種別. 所謂カットインやタッチ.
    std::optional<std::vector<kcv::kcsapi::night_attack_kind>> api_sp_list;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_HOUGEKI_HPP_INCLUDED
