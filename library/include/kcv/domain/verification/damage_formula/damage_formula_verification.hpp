#ifndef KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_DAMAGE_FORMULA_VERIFICATION_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_DAMAGE_FORMULA_VERIFICATION_HPP_INCLUDED

#include <optional>
#include <vector>

#include "kcv/core/context_data.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/damage_formula/damage_formula.hpp"
#include "kcv/domain/verification/damage_formula/inverse_formula.hpp"

namespace kcv {

/// @brief ダメージ説明結果.
struct explain_damage_result final {
    /// @brief ダメージ式.
    kcv::damage_formula damage_formula;

    /// @brief 逆算可能判定.
    bool is_invertible_damage_formula;

    /// @brief 説明可能判定.
    bool explainable_damage;

    /// @brief 逆算結果 攻撃力式.
    std::optional<kcv::inverse_attack_formula_result_t> inversed_attack_modifiers;

    /// @brief 逆算結果 防御力式.
    std::optional<kcv::inverse_defence_formula_result_t> inversed_defence_modifiers;
};

/// @brief 観測したダメージを, その状況化でのダメージ式で説明する.
auto explain_damage(const kcv::context_data& ctx, const kcv::battlelogs_t& battlelogs)
    -> std::vector<explain_damage_result>;

/// @brief 逆算可能判定.
bool is_invertible_damage_formula(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief miss判定.
bool is_miss(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 割合置換判定.
bool is_scratch_damage(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 致死置換判定. 第1種致死置換, 第2種致死置換, 第3種致死置換のいずれかであるかを検証する.
bool is_lethal_replacement_damage(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 第1種致死置換判定. このとき, [floor(hp*0.5), floor(hp*0.5)+floor((1-eps)*hp)*0.3]に置換される.
bool is_lethal_replaced_damage_on_normal_condition(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 第2種致死置換判定. 赤疲労致死置換. このとき, hp-1に置換される.
bool is_lethal_replaced_damage_on_very_tired(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 第3種致死置換判定. 友軍艦隊対深海棲艦終局阻止生存保証. このとき, floor(hp*0.5)に置換される.
bool is_lethal_replaced_damage_by_friendly_attack(const kcv::context_data& ctx, const kcv::battlelog& data);

//-------------

/// @brief 夜襲CI種別判別不可能判定.
bool is_night_air_attack_ci_type_indeterminable(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 戦爆連合熟練急所弾判定.
bool is_fba_combined_critical_air_attack(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 攻撃艦轟沈判定. 不要.
/// @brief 防御艦轟沈判定. 不要.

/// @brief 攻撃種別判定. おそらくこの判定自体を定義できない.
bool is_undefined_attack(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 敵空母戦闘後搭載数不明攻撃判定.
bool is_undefined_slot_num_air_attack(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 説明可能判定
/// 逆算可能判定に依存する.
// bool explainable_damage(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 理論範囲内判定.
// 観測ダメージと理論ダメージを引数にとるので、このシグネチャでは大きすぎる.
// bool is_theoretical_damage(const kcv::context_data& ctx, const kcv::battlelog& data);

}  // namespace kcv

#endif  // KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_DAMAGE_FORMULA_VERIFICATION_HPP_INCLUDED
