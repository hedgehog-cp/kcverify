#ifndef KCV_VERIFICATION_DAMAGE_FORMULA_ATTACK_POWER_FORMULA_FLEET_CUTIN_HPP_INCLUDED
#define KCV_VERIFICATION_DAMAGE_FORMULA_ATTACK_POWER_FORMULA_FLEET_CUTIN_HPP_INCLUDED

// 攻撃力式の実装詳細として, 艦隊特殊攻撃の補正値を返す関数群を提供する.
// 第11種補正または第14種補正にて適用する.

#include "kcv/core/context_data.hpp"
#include "kcv/core/numeric/interval.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"

namespace kcv {
namespace modifiers {

/// @brief Nelson Touch.
auto special_nelson(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief 一斉射かッ…胸が熱いな！.
auto special_nagato(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief 長門、いい？ いくわよ！ 主砲一斉射ッ！.
auto special_mutsu(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief 「Colorado」戦隊、全力斉射ッ！.
auto special_colorado(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief 僚艦夜戦突撃.
auto special_kongou(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief Richelieuよ！圧倒しなさいっ！.
auto special_richelieu(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief Queen Elizabeth Class special attack
auto special_queen_elizabeth_class(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief 潜水艦隊攻撃.
auto special_submarine_tender_23(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief 潜水艦隊攻撃.
auto special_submarine_tender_34(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief 潜水艦隊攻撃.
auto special_submarine_tender_24(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief 大和、突撃します！二番艦も続いてください！
auto special_yamato_3_ships(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief 第一戦隊、突撃！主砲、全力斉射ッ！
auto special_yamato_2_ships(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

}  // namespace modifiers
}  // namespace kcv

#endif  // KCV_VERIFICATION_DAMAGE_FORMULA_ATTACK_POWER_FORMULA_FLEET_CUTIN_HPP_INCLUDED
