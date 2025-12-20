#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_DAMAGE_FORMULA_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_DAMAGE_FORMULA_HPP_INCLUDED

#include "core/battlelog/battlelog.hpp"
#include "core/context_data.hpp"
#include "core/damage_formula/functions/composed_function.hpp"
#include "core/damage_formula/functions/modifier_functions.hpp"
#include "extensions/interval.hpp"
#include "extensions/interval/basic_interval.hpp"

namespace kcv {

/// @brief ダメージ式.
/// @tparam AttackPowerFormula 攻撃力式.
/// @tparam DefencePowerFormula 防御力式.
template <typename AttackPowerFormula, typename DefencePowerFormula>
class damage_formula final {
   public:
    using modifier_function_t = kcv::functions::composed_function<
        kcv::functions::liner,  // 弾薬量補正.
        kcv::functions::liner,  // 第1種補正.
        kcv::functions::floor   // 切り捨て.
        >;

    /// @brief 攻撃力式.
    using attack_power_formula_t = AttackPowerFormula;

    /// @brief 防御力式.
    using defence_power_formula_t = DefencePowerFormula;

    damage_formula(const kcv::context_data& ctx, const kcv::battlelog& data)
        : attack_power_formula_{ctx, data}
        , defence_power_formula_{ctx, data}
        , base_value_{}
        , function_{ammo(ctx, data) | f1(ctx, data) | floor(ctx, data)} {}

    auto evaluate() const {
        const auto attack_power  = this->attack_power_formula_.evaluate();
        const auto defence_power = this->defence_power_formula_.evaluate();
        const auto x             = attack_power - defence_power;
        return this->function_(x);
    }

    auto attack_power_formula() const noexcept -> const attack_power_formula_t& {
        return this->attack_power_formula_;
    }

    auto defence_power_formula() const noexcept -> const defence_power_formula_t& {
        return this->defence_power_formula_;
    }

    auto modifier_function() const noexcept -> const modifier_function_t& {
        return this->function_;
    }

    auto base_value() const -> kcv::number;

   private:
    static auto ammo(const kcv::context_data& ctx, const kcv::battlelog& data) noexcept -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    static auto f1(const kcv::context_data& ctx, const kcv::battlelog& data) noexcept -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    static auto floor(const kcv::context_data& ctx, const kcv::battlelog& data) noexcept -> kcv::functions::floor {
        return kcv::functions::floor{};
    }

   private:
    /// @brief 攻撃力式.
    attack_power_formula_t attack_power_formula_;

    /// @brief 防御力式.
    defence_power_formula_t defence_power_formula_;

    /// @brief
    kcv::number base_value_;

    /// @brief ダメージ補正関数.
    modifier_function_t function_;
};

}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_DAMAGE_FORMULA_HPP_INCLUDED
