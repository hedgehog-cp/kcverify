#include "kcv/core/constants/ship_attributes.hpp"
#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"

// -----------------------------------------------------------------------------
// 攻撃力式のうち前対潜シナジー補正, 後対潜シナジー補正の実装をここに分離する.
// -----------------------------------------------------------------------------

// kcv
#include "kcv/core/constants/equipment_attributes.hpp"
#include "kcv/core/context_data.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"
#include "kcv/domain/verification/logic/logic.hpp"
#include "kcv/external/kcsapi/types/enum/category.hpp"

// 長いのでエイリアス.
namespace mod = kcv::modifiers;

auto mod::pre_asw(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::pre_asw {
    // if (ctx.既存補正をoff) { return ctx.置換; }

    if (kcv::is_submarine(kcv::get_defender(data).mst())) {
        const auto& attacker        = kcv::get_attacker(data);
        const bool has_sonor        = kcv::has_equipment(attacker, &kcv::is_sonor);
        const bool has_depth_charge = kcv::has_equipment(attacker, &kcv::is_depth_charge);
        if (has_sonor and has_depth_charge) {
            return kcv::functions::pre_asw{.a = 1.15};
        }
    }

    return kcv::functions::pre_asw{.a = 1.0};
}

auto mod::post_asw(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::post_asw {
    // if (ctx.既存補正をoff) { return ctx.置換; }

    if (kcv::is_submarine(kcv::get_defender(data).mst())) {
        const auto& attacker                    = kcv::get_attacker(data);
        const bool has_depth_charge_projector   = kcv::has_equipment(attacker, &kcv::is_depth_charge_projector);
        const bool has_synergistic_depth_charge = kcv::has_equipment(attacker, &kcv::is_synergistic_depth_charge);
        if (has_depth_charge_projector and has_synergistic_depth_charge) {
            const bool has_small_sonor = kcv::has_equipment(attacker, kcv::kcsapi::category::sonar);
            if (has_small_sonor) {
                return kcv::functions::post_asw{.a = 1.25};
            } else {
                return kcv::functions::post_asw{.a = 1.1};
            }
        }
    }

    return kcv::functions::post_asw{.a = 1.0};
}