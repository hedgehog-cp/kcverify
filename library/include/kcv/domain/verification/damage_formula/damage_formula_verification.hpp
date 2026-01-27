#ifndef KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_DAMAGE_FORMULA_VERIFICATION_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_DAMAGE_FORMULA_VERIFICATION_HPP_INCLUDED

// std
#include <iostream>
#include <ostream>
#include <utility>

// kcv
#include "kcv/core/context_data.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"

namespace kcv {

/// @brief kcv::verify_damage_formula関数の書き出し操作を制御する.
/// メンバがtrueのとき, その項目の計算結果を書き出す.
struct vdf_output_policy final {
    // -------------------------------------------------------------------------
    // 順算:
    //   順向きのダメージ計算.
    // -------------------------------------------------------------------------

    /// @brief 順算: 基本攻撃力を書き出す.
    bool base_attack_power = true;

    /// @brief 順算: 交戦形態補正を書き出す.
    bool engagement = true;

    /// @brief 順算: 攻撃側陣形補正を書き出す.
    bool formation = true;

    /// @brief 順算: 損傷状態補正を書き出す.
    bool damage_state = true;

    /// @brief 順算: 前対潜シナジー補正を書き出す.
    bool pre_asw = true;

    /// @brief 順算: 後対潜シナジー補正を書き出す.
    bool post_asw = true;

    /// @brief 順算: 装甲減少補正を書き出す.
    bool ap_depth_charge = true;

    /// @brief 順算: 最終攻撃力を書き出す.
    bool attack_power = true;

    /// @brief 順算: 最終防御力を書き出す.
    bool defence_power = true;

    /// @brief 順算: ダメージを書き出す.
    bool damage = true;

    // -------------------------------------------------------------------------
    // 逆算:
    //   観測したダメージおよびダメージ式を用いて各補正値を解く計算.
    // -------------------------------------------------------------------------

    /// @brief 逆算: 未知の第0種補正.
    /// firstがtrueのとき各値を書き出す. secondがtrueのとき集計値を書き出す.
    std::pair<bool, bool> inversed_f0 = {true, true};

    /// @brief 逆算: 未知の第14種補正.
    /// firstがtrueのとき各値を書き出す. secondがtrueのとき集計値を書き出す.
    std::pair<bool, bool> inversed_f14 = {true, true};

    /// @brief 逆算: 未知の第3種補正.
    /// firstがtrueのとき各値を書き出す. secondがtrueのとき集計値を書き出す.
    std::pair<bool, bool> inversed_f3 = {true, true};

    /// @brief 逆算: 未知の第2種補正.
    /// firstがtrueのとき各値を書き出す. secondがtrueのとき集計値を書き出す.
    std::pair<bool, bool> inversed_f2 = {true, true};
};

/// @brief ダメージ式を検証する.
/// @param ctx マスタを含む背景情報.
/// @param battlelogs 検証対象の全戦闘ログ.
/// @param output_policy 書き出し制御ポリシー.
/// @param os 検証結果の書き出し先.
/// @details 検証対象の全戦闘ログそれぞれに対してダメージ式を立式･評価し, 観測されたダメージの説明可能性を検証する.
/// 逆算可能である場合は, 観測ダメージおよびダメージ式から補正値の逆算を行う.
/// 検証結果を`output_policy`に従って`os`に書き出す.
void verify_damage_formula(
    const kcv::context_data& ctx,
    const kcv::battlelogs_t& battlelogs,
    const kcv::vdf_output_policy& output_policy = {},
    std::ostream& os                            = std::cout
);

/// @brief 逆算可能判定.
/// 理論上または実装上, ダメージ式の各補正値を逆算できるかを検証する. 逆算可能ならばtrueを返す.
/// この関数は`kcv::verify_damage_formula`の内部で呼ばれる.
/// @details 以下の判定いずれにおいても偽であるならば逆算可能.
/// @see `is_miss`
/// @see `is_scratch_damage`
/// @see `is_lethal_replacement_damage`
/// @see     `is_lethal_replaced_damage_on_normal_condition`
/// @see     `is_lethal_replaced_damage_on_very_tired`
/// @see     `is_lethal_replaced_damage_by_friendly_attack`
/// @see `is_night_air_attack_ci_type_indeterminable`
/// @see `is_fba_combined_critical_air_attack`
/// @see `is_undefined_slot_num_air_attack`
bool is_invertible_damage_formula(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief miss判定.
/// missのとき, ダメージは0または割合置換となるため逆算できない.
bool is_miss(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 割合置換判定.
/// 割合置換のとき, 攻撃力および防御力によらないダメージに置換されるため逆算できない.
bool is_scratch_damage(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 致死置換判定. 第1種致死置換, 第2種致死置換, 第3種致死置換のいずれかであるかを検証する.
/// 致死置換のとき, 攻撃力および防御力によらないダメージに置換されるため逆算できない.
bool is_lethal_replacement_damage(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 第1種致死置換判定.
/// 第1種致死置換のとき, ダメージが[floor(hp*0.5), floor(hp*0.5+max(hp-1,0)*0.3)]に置換される.
bool is_lethal_replaced_damage_on_normal_condition(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 第2種致死置換判定.
/// 第2種致死置換のとき, ダメージがhp-1に置換される.
bool is_lethal_replaced_damage_on_very_tired(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 第3種致死置換判定
/// 第3種致死置換のとき, ダメージがfloor(hp*0.5)に置換される.
bool is_lethal_replaced_damage_by_friendly_attack(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 夜襲CI種別判別不可能判定.
/// 夜襲CIの種別を表示装備などから判別できないため攻撃力を決定できない.
bool is_night_air_attack_ci_type_indeterminable(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 戦爆連合熟練急所弾判定.
/// 空母によるFBAなどの戦爆連合の攻撃において熟練急所弾の補正値が未詳であるため攻撃力を決定できない.
bool is_fba_combined_critical_air_attack(const kcv::context_data& ctx, const kcv::battlelog& data);

/// @brief 敵空母戦闘後搭載数不明攻撃判定.
/// ある時期以降に追加された深海棲艦の各スロットの搭載数が不明であるため攻撃力を決定できない.
bool is_unknown_slot_air_attack(const kcv::context_data& ctx, const kcv::battlelog& data);

// ダメージ検証用スプレで扱う以下の判定は, 未使用または定義できないため未定義.
//   `攻撃艦轟沈判定`
//   `防御艦轟沈判定`
//   `攻撃種別判定`
// ダメージ検証用スプレで扱う以下の判定は, 実装上の都合で関数化していない.
//   `説明可能判定`

}  // namespace kcv

#endif  // KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_DAMAGE_FORMULA_VERIFICATION_HPP_INCLUDED
