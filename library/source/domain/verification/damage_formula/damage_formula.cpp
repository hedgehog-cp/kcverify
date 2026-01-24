#include "kcv/domain/verification/damage_formula/damage_formula.hpp"

#include <algorithm>
#include <cmath>

#include "kcv/core/context_data.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"
#include "kcv/external/kcsapi/types/enum/fleet_flag.hpp"

auto kcv::formulate_damage(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::damage_formula {
    return kcv::damage_formula{
        kcv::formulate_attack_power(ctx, data),
        kcv::formulate_defence_power(ctx, data),
        kcv::modifiers::ammo(ctx, data)                //
            | kcv::modifiers::f1(ctx, data)            //
            | kcv::modifiers::floor_damage(ctx, data)  //
        ,
    };
}

// 各補正の実装詳細は `*_impl` 名前空間に包んで実装し, namespace impl = ...; とともに使う.
// namespace kcv::modifiers { namespace { namespace modifier_name_impl { ... } }}
// auto f() { namespace impl = kcv::modifiers::modifier_name_impl; impl::foo(); }

/// @brief 長いのでalias. 関数のシグネチャが改行されちゃうもん...
namespace mod = kcv::modifiers;

namespace kcv::modifiers {
namespace {
namespace ammo_impl {

/// @todo 洋上補給, アイテムの使用検出, 戦闘後残弾薬量の参照, etc...
/// @details min([(残弾薬 + [最大弾薬 * 幼女割合]) / 最大弾薬 * 100], 50) / 50
auto primary_modifier(const kcv::battlelog& data) -> kcv::functions::liner {
    const auto& attacker    = kcv::get_attacker(data);
    const auto current_ammo = attacker.ammo();
    const auto max_ammo     = attacker.mst().api_bull_max.value();

    return kcv::functions::liner{
        .a = std::min(std::floor(current_ammo + std::floor(max_ammo * 1.0) / max_ammo * 100), 50.0) / 50
    };
}

}  // namespace ammo_impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::ammo(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner {
    namespace impl = kcv::modifiers::ammo_impl;

    // 演習相手はたぶんenemyとして常に1なので問題ないと思う.
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return impl::primary_modifier(data);

        case kcv::kcsapi::fleet_flag::enemy:
            return kcv::functions::liner{.a = 1.0};
    }

    return kcv::functions::liner{};
}

auto mod::f1(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner {
    return kcv::functions::liner{};
}

auto mod::floor_damage(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::floor_if {
    return kcv::functions::floor_if{.is_enabled = true};
}