#ifndef KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_ATTACK_POWER_FORMULA_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_ATTACK_POWER_FORMULA_HPP_INCLUDED

// std
#include <optional>

// kcv
#include "kcv/core/context_data.hpp"
#include "kcv/core/numeric/composed_function.hpp"
#include "kcv/core/numeric/interval.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"

namespace kcv {

/// @brief 攻撃力式.
class attack_power_formula final {
   public:
    /// @brief 攻撃力補正関数.
    using modifier_function_t = kcv::functions::composed_function<
        kcv::functions::f0,            // 第0種補正.
        kcv::functions::engagement,    // 交戦形態補正.
        kcv::functions::formation,     // 攻撃側陣形補正.
        kcv::functions::damage_state,  // 損傷状態補正.
        kcv::functions::pre_asw,       // 前対潜シナジー補正.
        kcv::functions::post_asw,      // 後対潜シナジー補正.
        kcv::functions::f14,           // 第14種補正.
        kcv::functions::fit_gun,       // フィット砲補正.
        kcv::functions::softcap,       // ソフトキャップ.
        kcv::functions::f5,            // 第5種補正.
        kcv::functions::floor_if,      // 切り捨て.
        kcv::functions::f6,            // 第6種補正.
        kcv::functions::f7,            // 第7種補正.
        kcv::functions::floor_if,      // 切り捨て.
                                       // 昼間特殊攻撃補正.
                                       // 徹甲弾補正.
                                       // 第11種補正.
                                       // 艦種補正.
        kcv::functions::map,           // 海域補正.
        kcv::functions::event,         // 期間限定海域.
        kcv::functions::f8,            // 第8種補正.
        kcv::functions::pt_imp,        // PT.
                                       // PT装備補正は多層の乗算...
        kcv::functions::critical,      // 急所補正.
        kcv::functions::floor_if       // 切り捨て.
        >;

    attack_power_formula(const kcv::number& base_value, const modifier_function_t& modifier_function) noexcept
        : base_value_{base_value}
        , modifier_function_{modifier_function} {}

    auto evaluate() const noexcept -> std::optional<kcv::number> {
        return this->modifier_function_(this->base_value_);
    }

    auto base_value() const noexcept -> const kcv::number& {
        return this->base_value_;
    }

    auto modifier_function() const noexcept -> const modifier_function_t& {
        return this->modifier_function_;
    }

   private:
    /// @brief 基本攻撃力.
    kcv::number base_value_;

    /// @brief 攻撃力補正関数.
    modifier_function_t modifier_function_;
};

/// @brief 攻撃力式を立式する.
auto formulate_attack_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::attack_power_formula;

namespace modifiers {

/// @brief 基本攻撃力.
auto basic_attack_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief 未知の第0種補正.
auto f0(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f0;

/// @brief 交戦形態補正.
auto engagement(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::engagement;

/// @brief 攻撃側陣形補正.
auto formation(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::formation;

/// @brief 損傷状態補正.
auto damage_state(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::damage_state;

/// @brief 前対潜シナジー補正.
auto pre_asw(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::pre_asw;

/// @brief 後対潜シナジー補正.
auto post_asw(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::post_asw;

/// @brief 未知の第14種補正.
auto f14(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f14;

/// @brief フィット砲補正.
auto fit_gun(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::fit_gun;

/// @brief ソフトキャップ補正.
auto softcap(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::softcap;

/// @brief 未知の第5種補正.
auto f5(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f5;

/// @brief 切り捨て補正.
auto floor_f5(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::floor_if;

/// @brief 未知の第6種補正.
auto f6(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f6;

/// @brief 未知の第7種補正.
auto f7(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f7;

/// @brief 切り捨て補正.
auto floor_f7(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::floor_if;

/// @brief 自艦隊阻塞気球補正.
/// @brief 敵艦隊阻塞気球補正.
/// @brief 戦爆連合補正.
/// @brief 昼間特殊攻撃補正.
/// @brief 徹甲弾補正.
/// @brief 未知の第11種補正.
/// @brief 対集積地棲姫.
/// @brief 対戦艦夏姫.
/// @brief 対重巡夏姫.
/// @brief 対空母夏鬼.
/// @brief 対北端上陸姫.
/// @brief 対戦艦仏棲姫.
/// @brief 対泊地水鬼 バカンスmode.
/// @brief 対船渠棲姫.

/// @brief 海域補正.
auto map(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::map;

/// @brief 期間限定海域補正.
auto event(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::event;

/// @brief 未知の第8種補正.
auto f8(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f8;

/// @brief 対PT小鬼群補正.
auto pt_imp(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::pt_imp;

/// @brief 対PT小鬼群 装備補正.
auto pt_imp_equipment(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::composed_function<
    kcv::functions::liner,  // 小口径主砲 [1]
    kcv::functions::liner,  // 小口径主砲 [2]
    kcv::functions::liner,  // 対空機銃 [1]
    kcv::functions::liner,  // 対空機銃 [2]
    kcv::functions::liner,  // 副砲
    kcv::functions::liner,  // 艦上爆撃機 | 噴式戦闘爆撃機 [1]
    kcv::functions::liner,  // 艦上爆撃機 | 噴式戦闘爆撃機 [2]
    kcv::functions::liner,  // 水上爆撃機 | 水上戦闘機
    kcv::functions::liner,  // 装甲艇(AB艇) & 武装大発
    kcv::functions::liner   // 装甲艇(AB艇) & 武装大発 ★
    >;

/// @brief 対PT小鬼群 夜戦補正.
auto pt_imp_midnight(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner;

/// @brief 急所弾補正.
auto critical(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::critical;

/// @brief 急所弾切り捨て補正.
auto floor_if_critical(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::floor_if;

}  // namespace modifiers
}  // namespace kcv

#endif  // KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_ATTACK_POWER_FORMULA_HPP_INCLUDED
