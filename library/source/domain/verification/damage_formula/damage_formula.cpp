#include "kcv/domain/verification/damage_formula/damage_formula.hpp"

#include "kcv/core/context_data.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"

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

auto mod::ammo(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner {
    return kcv::functions::liner{};
}

auto mod::f1(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner {
    return kcv::functions::liner{};
}

auto mod::floor_damage(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::floor_if {
    return kcv::functions::floor_if{.is_enabled = true};
}