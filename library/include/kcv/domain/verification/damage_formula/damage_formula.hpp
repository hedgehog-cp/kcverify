#ifndef KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_DAMAGE_FORMULA_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_DAMAGE_FORMULA_HPP_INCLUDED

// std
#include <optional>

// kcv
#include "kcv/core/context_data.hpp"
#include "kcv/core/numeric/composed_function.hpp"
#include "kcv/core/numeric/interval.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"
#include "kcv/domain/verification/damage_formula/defence_power_formula.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"

namespace kcv {

/// @brief ダメージ式.
class damage_formula final {
   public:
    /// @brief ダメージ補正関数.
    using modifier_function_t = kcv::functions::composed_function<
        kcv::functions::liner,    // 弾薬量補正.
        kcv::functions::liner,    // 第1種補正.
        kcv::functions::floor_if  // 切り捨て.
        >;

    damage_formula(
        const kcv::attack_power_formula& attack_power_formula,
        const kcv::defence_power_formula& defence_power_formula,
        const modifier_function_t& modifier_function
    ) noexcept
        : attack_power_formula_{attack_power_formula}
        , attack_power_{attack_power_formula.evaluate()}
        , defence_power_formula_{defence_power_formula}
        , defence_power_{defence_power_formula.evaluate()}
        , base_value_{
            this->attack_power_.has_value() and this->defence_power_.has_value()  //
            ? std::make_optional(*this->attack_power_ - *this->defence_power_)    //
            : std::nullopt                                                        //
          }
        , modifier_function_{modifier_function} {}

    auto evaluate() const noexcept -> std::optional<kcv::number> {
        return this->modifier_function_(this->base_value_);
    }

    auto attack_power_formula() const noexcept -> const kcv::attack_power_formula& {
        return this->attack_power_formula_;
    }

    auto attack_power() const noexcept -> const std::optional<kcv::number>& {
        return this->attack_power_;
    }

    auto defence_power_formula() const noexcept -> const kcv::defence_power_formula& {
        return this->defence_power_formula_;
    }

    auto defence_power() const noexcept -> const std::optional<kcv::number>& {
        return this->defence_power_;
    }

    auto base_value() const noexcept -> const std::optional<kcv::number>& {
        return this->base_value_;
    }

    auto modifier_function() const noexcept -> const modifier_function_t& {
        return this->modifier_function_;
    }

   private:
    /// @brief 攻撃力式.
    kcv::attack_power_formula attack_power_formula_;

    /// @brief 攻撃力.
    std::optional<kcv::number> attack_power_;

    /// @brief 防御力式.
    kcv::defence_power_formula defence_power_formula_;

    /// @brief 防御力.
    std::optional<kcv::number> defence_power_;

    /// @brief 攻撃力 - 防御力.
    std::optional<kcv::number> base_value_;

    /// @brief ダメージ補正関数.
    modifier_function_t modifier_function_;
};

/// @brief ダメージ式を立式する.
auto formulate_damage(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::damage_formula;

namespace modifiers {

/// @brief 弾薬量補正.
auto ammo(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner;

/// @brief 未知の第1種補正.
auto f1(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner;

/// @brief 切り捨て補正.
auto floor_damage(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::floor_if;

}  // namespace modifiers
}  // namespace kcv

#endif  // KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_DAMAGE_FORMULA_HPP_INCLUDED
