#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FORMULA_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FORMULA_HPP_INCLUDED

#include "core/damage_formula/functions/function_composition.hpp"
#include "core/damage_formula/functions/modifier_functions.hpp"

namespace kcv {

using defence_power_formula = kcv::functions::function_composition<
    kcv::functions::liner,                  // 第3種補正.
    kcv::functions::liner,                  // 改修補正.
    kcv::functions::liner,                  // 北方海域北方バルジ補正.
    kcv::functions::liner,                  // 爆雷装甲減少補正.
    kcv::functions::depth_armor_break_cap,  // 爆雷装甲減少補正キャップ.
    kcv::functions::aromor_rand,            // 装甲乱数.
    kcv::functions::liner,                  // 第2種補正.
    kcv::functions::liner                   // 装甲破砕効果.
    >;

class damage_calculator final {
   public:
    using attack_power_formula  = void;
    using defence_power_formula = void;

   private:
};

class inverse_calculator final {
   public:
    using attack_power_formula  = void;
    using defence_power_formula = void;

   private:
};

}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FORMULA_HPP_INCLUDED
