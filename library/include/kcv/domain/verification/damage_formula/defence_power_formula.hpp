#ifndef KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_DEFENCE_POWER_FORMULA_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_DEFENCE_POWER_FORMULA_HPP_INCLUDED

// std
#include <optional>

// kcv
#include "kcv/core/context_data.hpp"
#include "kcv/core/numeric/composed_function.hpp"
#include "kcv/core/numeric/interval.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"

namespace kcv {

/// @brief 防御力式.
class defence_power_formula final {
   public:
    /// @brief 防御力補正関数.
    using modifier_function_t = kcv::functions::composed_function<
        kcv::functions::f3,                     // 第3種補正.
        kcv::functions::liner,                  // 改修補正.
        kcv::functions::liner,                  // 北方海域北方バルジ補正.
        kcv::functions::liner,                  // 爆雷装甲減少補正.
        kcv::functions::depth_armor_break_cap,  // 爆雷装甲減少補正キャップ.
        kcv::functions::aromor_rand,            // 装甲乱数.
        kcv::functions::f2,                     // 第2種補正.
        kcv::functions::liner                   // 装甲破砕効果.
        >;

    defence_power_formula(const kcv::number& base_value, const modifier_function_t& modifier_function) noexcept
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
    /// @brief 基本防御力.
    kcv::number base_value_;

    /// @brief 防御力補正関数.
    modifier_function_t modifier_function_;
};

/// @brief 防御力式を立式する.
auto formulate_defence_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::defence_power_formula;

namespace modifiers {

/// @brief 基本防御力.
auto basic_defence_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief 未知の第3種補正.
auto f3(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f3;

/// @brief 改修補正.
auto improvement(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner;

/// @brief 北方海域北方バルジ補正.
auto noth_bulge(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner;

/// @brief 爆雷装甲減少補正.
auto depth_charge_armor_break(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner;

/// @brief 爆雷装甲減少下限補正.
auto depth_charge_armor_break_cap(const kcv::context_data& ctx, const kcv::battlelog& data)
    -> kcv::functions::depth_armor_break_cap;

/// @brief 装甲乱数補正.
auto armor_rand(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::aromor_rand;

/// @brief 未知の第2種補正.
auto f2(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f2;

/// @brief 装甲破砕効果.
auto armor_break(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner;

}  // namespace modifiers
}  // namespace kcv

#endif  // KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_DEFENCE_POWER_FORMULA_HPP_INCLUDED
