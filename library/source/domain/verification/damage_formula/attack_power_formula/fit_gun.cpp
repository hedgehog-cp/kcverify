#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"

// -----------------------------------------------------------------------------
// 攻撃力式のうちフィット砲補正の実装をここに分離する.
// -----------------------------------------------------------------------------

// std
#include <concepts>

// kcv
#include "kcv/core/constants/equipment_attributes.hpp"
#include "kcv/core/constants/ship_attributes.hpp"
#include "kcv/core/context_data.hpp"
#include "kcv/core/numeric/interval.hpp"
#include "kcv/core/numeric/interval/basic_interval.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"
#include "kcv/domain/verification/entity/ship.hpp"
#include "kcv/domain/verification/logic/logic.hpp"

namespace kcv::modifiers {
namespace {
namespace impl {

/// @brief 整数を区間に変換する.
auto make_number(std::integral auto n) noexcept -> kcv::number {
    return kcv::number{static_cast<kcv::number::base_type>(n)};
}

/// @brief 伊重巡伊重巡砲補正を返す.
auto italian_fit_gun_modifier(const kcv::ship& attacker) -> kcv::functions::fit_gun {
    const auto italian_gun_num = kcv::count_equipment(attacker, &kcv::is_italian_fit_main_gun);
    return kcv::functions::fit_gun{.b = kcv::sqrt(make_number(italian_gun_num))};
}

/// @brief 軽巡軽量砲補正を返す.
auto cl_fit_gun_modifier(const kcv::ship& attacker) -> kcv::functions::fit_gun {
    const auto main_gun_num      = kcv::count_equipment(attacker, &kcv::is_cl_fit_main_gun);
    const auto secondary_gun_num = kcv::count_equipment(attacker, &kcv::is_cl_fit_secondary_gun);
    return kcv::functions::fit_gun{
        .b = 2 * kcv::sqrt(make_number(main_gun_num)) + kcv::sqrt(make_number(secondary_gun_num))
    };
}

/// @brief フィット砲補正を返す.
auto fit_gun_modifier(const kcv::battlelog& data) -> kcv::functions::fit_gun {
    const auto& attacker = kcv::get_attacker(data);

    if (kcv::is_cl(attacker.mst())) {
        return cl_fit_gun_modifier(attacker);
    }

    if (kcv::is_italian_ca(attacker.mst())) {
        return italian_fit_gun_modifier(attacker);
    }

    return kcv::functions::fit_gun{.b = 0};
}

}  // namespace impl
}  // namespace
}  // namespace kcv::modifiers

// 長いのでエイリアス.
namespace mod = kcv::modifiers;

auto mod::fit_gun(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::fit_gun {
    namespace impl = kcv::modifiers::impl;

    // if (ctx.既存補正をoff) { return ctx.置換; }

    switch (data.phase) {
        case kcv::phase::sp_midnight:
            return impl::fit_gun_modifier(data);

        case kcv::phase::opening_taisen:
            return kcv::functions::fit_gun{.b = 0};

        case kcv::phase::opening_atack:
        case kcv::phase::hougeki:
            return impl::fit_gun_modifier(data);

        case kcv::phase::raigeki:
            return kcv::functions::fit_gun{.b = 0};

        case kcv::phase::friendly:
        case kcv::phase::midnight:
            return impl::fit_gun_modifier(data);
    }

    return kcv::functions::fit_gun::identity();
}
