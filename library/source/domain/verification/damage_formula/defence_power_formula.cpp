#include "kcv/domain/verification/damage_formula/defence_power_formula.hpp"

#include "kcv/core/context_data.hpp"
#include "kcv/core/numeric/composed_function.hpp"
#include "kcv/core/numeric/interval.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"
#include "kcv/domain/verification/entity/ship.hpp"

auto kcv::formulate_defence_power(
    const kcv::context_data& ctx,  //
    const kcv::battlelog& data     //
) -> kcv::defence_power_formula {
    return kcv::defence_power_formula{
        kcv::modifiers::basic_defence_power(ctx, data),
        kcv::modifiers::f3(ctx, data)                                  //
            | kcv::modifiers::improvement(ctx, data)                   //
            | kcv::modifiers::noth_bulge(ctx, data)                    //
            | kcv::modifiers::depth_charge_armor_break(ctx, data)      //
            | kcv::modifiers::depth_charge_armor_break_cap(ctx, data)  //
            | kcv::modifiers::armor_rand(ctx, data)                    //
            | kcv::modifiers::f2(ctx, data)                            //
            | kcv::modifiers::armor_break(ctx, data)                   //
        ,
    };
}

// 各補正の実装詳細は `*_impl` 名前空間に包んで実装し, namespace impl = ...; とともに使う.
// namespace kcv::modifiers { namespace { namespace modifier_name_impl { ... } }}
// auto f() { namespace impl = kcv::modifiers::modifier_name_impl; impl::foo(); }

/// @brief 長いのでalias. 関数のシグネチャが改行されちゃうもん...
namespace mod = kcv::modifiers;

auto mod::basic_defence_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    const auto& defender = kcv::get_defender(data);
    const auto armor     = defender.armor();

    return armor;
}

auto mod::f3(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f3 {
    return kcv::functions::f3{};
}

auto mod::improvement(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner {
    return kcv::functions::liner{};
}

auto mod::noth_bulge(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner {
    return kcv::functions::liner{};
}

auto mod::depth_charge_armor_break(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner {
    return kcv::functions::liner{};
}

auto mod::depth_charge_armor_break_cap(const kcv::context_data& ctx, const kcv::battlelog& data)
    -> kcv::functions::depth_armor_break_cap {
    return kcv::functions::depth_armor_break_cap{};
}

auto mod::armor_rand(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::aromor_rand {
    return kcv::functions::aromor_rand{};
}

auto mod::f2(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f2 {
    return kcv::functions::f2{};
}

auto mod::armor_break(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner {
    return kcv::functions::liner{};
}