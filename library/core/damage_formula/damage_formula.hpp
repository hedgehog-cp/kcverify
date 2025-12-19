#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_DAMAGE_FORMULA_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_DAMAGE_FORMULA_HPP_INCLUDED

#include "core/battlelog/battlelog.hpp"
#include "core/context_data.hpp"

namespace kcv {

template <typename AttackPowerForluma, typename DefencePowerForluma>
class damage_formula final {
   public:
    using attack_power_formula  = AttackPowerForluma;
    using defence_power_formula = DefencePowerForluma;

    damage_formula(const kcv::context_data& ctx, const kcv::battlelog& data)
        : attack_power_formula_{ctx, data}
        , defence_power_formula_{ctx, data} {}

    auto evaluate() const;

    auto inverse() const;

   private:
    attack_power_formula attack_power_formula_;
    defence_power_formula defence_power_formula_;
};

}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_DAMAGE_FORMULA_HPP_INCLUDED
