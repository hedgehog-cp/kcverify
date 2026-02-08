#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"

// -----------------------------------------------------------------------------
// 攻撃力式のうち損傷状態補正の実装をここに分離する.
// -----------------------------------------------------------------------------

// kcv
#include "kcv/core/context_data.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"
#include "kcv/domain/verification/entity/ship.hpp"
#include "kcv/external/kcsapi/extensions/damage_state.hpp"

namespace kcv::modifiers {
namespace {
namespace impl {

/// @brief 攻撃艦の損傷状態を取得する.
auto get_attacker_damage_state(const kcv::battlelog& data) -> kcv::damage_state {
    const auto& attacker = kcv::get_attacker(data);
    return kcv::to_damage_state(attacker.hp(), attacker.maxhp());
}

/// @brief 雷撃の損傷状態補正を返す.
auto torpedo_modifier(const kcv::battlelog& data) -> kcv::functions::damage_state {
    switch (get_attacker_damage_state(data)) {
        case kcv::damage_state::healthy:
        case kcv::damage_state::light:
            return kcv::functions::damage_state{.a = 1.0};

        case kcv::damage_state::medium:
            return kcv::functions::damage_state{.a = 0.8};

        case kcv::damage_state::heavy:
            return kcv::functions::damage_state{.a = 0.0};

        case kcv::damage_state::sunk:
            /// @todo 要検討: 刺し違え雷撃.
            return kcv::functions::damage_state::identity();
    }
}

/// @brief 主要な損傷状態補正を返す.
auto primary_modifier(const kcv::battlelog& data) -> kcv::functions::damage_state {
    switch (get_attacker_damage_state(data)) {
        case kcv::damage_state::healthy:
        case kcv::damage_state::light:
            return kcv::functions::damage_state{.a = 1.0};

        case kcv::damage_state::medium:
            return kcv::functions::damage_state{.a = 0.7};

        case kcv::damage_state::heavy:
            return kcv::functions::damage_state{.a = 0.4};

        case kcv::damage_state::sunk:
            return kcv::functions::damage_state::identity();
    }
}

}  // namespace impl
}  // namespace
}  // namespace kcv::modifiers

// 長いのでエイリアス.
namespace mod = kcv::modifiers;

auto mod::damage_state(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::damage_state {
    namespace impl = kcv::modifiers::impl;

    // if (ctx.既存補正をoff) { return ctx.置換; }

    // 大破であれば夜間攻撃できないが, ネルソンタッチに巻き込めば攻撃できる. このときの補正値は*0.4である.
    switch (data.phase) {
        case kcv::phase::sp_midnight:
        case kcv::phase::opening_taisen:
            return impl::primary_modifier(data);

        case kcv::phase::opening_atack:
            return impl::torpedo_modifier(data);

        case kcv::phase::hougeki:
            return impl::primary_modifier(data);

        case kcv::phase::raigeki:
            return impl::torpedo_modifier(data);

        case kcv::phase::midnight:
        case kcv::phase::friendly:
            return impl::primary_modifier(data);
    }

    return kcv::functions::damage_state::identity();
}
