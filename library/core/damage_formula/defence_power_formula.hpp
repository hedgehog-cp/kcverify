#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_DEFENCE_POWER_FORMULA_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_DEFENCE_POWER_FORMULA_HPP_INCLUDED

#include "core/battlelog/battlelog.hpp"
#include "core/context_data.hpp"
#include "core/damage_formula/functions/composed_function.hpp"
#include "core/damage_formula/functions/modifier_functions.hpp"

namespace kcv {

/// @brief 防御力式.
class defence_power_formula final {
   public:
    using formula_type = kcv::functions::composed_function<
        kcv::functions::liner,                  // 第3種補正.
        kcv::functions::liner,                  // 改修補正.
        kcv::functions::liner,                  // 北方海域北方バルジ補正.
        kcv::functions::liner,                  // 爆雷装甲減少補正.
        kcv::functions::depth_armor_break_cap,  // 爆雷装甲減少補正キャップ.
        kcv::functions::aromor_rand,            // 装甲乱数.
        kcv::functions::liner,                  // 第2種補正.
        kcv::functions::liner                   // 装甲破砕効果.
        >;

    defence_power_formula(const kcv::context_data& ctx, const kcv::battlelog& data)
        : formula_{
              f3(ctx, data)                       //
              | improvement(ctx, data)            //
              | noth_bulge(ctx, data)             //
              | depth_armor_break(ctx, data)      //
              | depth_armor_break_cap(ctx, data)  //
              | armor_rand(ctx, data)             //
              | f2(ctx, data)                     //
              | armor_break(ctx, data)            //
          } {}

    static auto f3(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    static auto improvement(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    static auto noth_bulge(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    static auto depth_armor_break(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    static auto depth_armor_break_cap(const kcv::context_data& ctx, const kcv::battlelog& data)
        -> kcv::functions::depth_armor_break_cap {
        return kcv::functions::depth_armor_break_cap{};
    }

    static auto armor_rand(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::aromor_rand {
        return kcv::functions::aromor_rand{};
    }

    static auto f2(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    static auto armor_break(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

   private:
    formula_type formula_;
};

}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_DEFENCE_POWER_FORMULA_HPP_INCLUDED
