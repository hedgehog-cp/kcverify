#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"

#include <algorithm>
#include <type_traits>

#include "kcv/core/constants/equipment.hpp"
#include "kcv/core/constants/equipment_attributes.hpp"
#include "kcv/core/constants/ship_attributes.hpp"
#include "kcv/core/context_data.hpp"
#include "kcv/core/numeric/composed_function.hpp"
#include "kcv/core/numeric/interval.hpp"
#include "kcv/core/numeric/interval/basic_interval.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"
#include "kcv/domain/verification/entity/equipment.hpp"
#include "kcv/domain/verification/entity/ship.hpp"
#include "kcv/external/kcsapi/extensions/damage_state.hpp"
#include "kcv/external/kcsapi/types/api_type.hpp"
#include "kcv/external/kcsapi/types/enum/air_hit_type.hpp"
#include "kcv/external/kcsapi/types/enum/category.hpp"
#include "kcv/external/kcsapi/types/enum/engagement.hpp"
#include "kcv/external/kcsapi/types/enum/formation.hpp"
#include "kcv/external/kcsapi/types/enum/night_attack_kind.hpp"
#include "kcv/std_ext/exception.hpp"
#include "kcv/std_ext/utility.hpp"

auto kcv::formulate_attack_power(
    const kcv::context_data& ctx,  //
    const kcv::battlelog& data     //
) -> kcv::attack_power_formula {
    return kcv::attack_power_formula{
        kcv::modifiers::basic_attack_power(ctx, data),
        kcv::modifiers::f0(ctx, data)                  //
            | kcv::modifiers::engagement(ctx, data)    //
            | kcv::modifiers::formation(ctx, data)     //
            | kcv::modifiers::damage_state(ctx, data)  //
            | kcv::modifiers::pre_asw(ctx, data)       //
            | kcv::modifiers::post_asw(ctx, data)      //
            | kcv::modifiers::f14(ctx, data)           //
            | kcv::modifiers::fit_gun(ctx, data)       //
            | kcv::modifiers::softcap(ctx, data)       //
            | kcv::modifiers::f5(ctx, data)            //
            | kcv::modifiers::floor_f5(ctx, data)      //
            | kcv::modifiers::f6(ctx, data)            //
            | kcv::modifiers::f7(ctx, data)            //
            | kcv::modifiers::floor_f7(ctx, data)      //
            | kcv::modifiers::map(ctx, data)           //
            | kcv::modifiers::event(ctx, data)         //
            | kcv::modifiers::f8(ctx, data)            //
            | kcv::modifiers::pt_imp(ctx, data)        //
            // | kcv::modifiers::pt_imp_equipment(ctx, data)
            // | kcv::modifiers::pt_imp_midnight(ctx, data)
            | kcv::modifiers::critical(ctx, data)           //
            | kcv::modifiers::floor_if_critical(ctx, data)  //
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
namespace basic_attack_power_impl {

auto torpedo_improvement_bonus(const kcv::equipment& equipment) -> kcv::number {
    switch (std::get<kcv::kcsapi::category>(equipment.mst().api_type)) {
        case kcv::kcsapi::category::torpedo:
        case kcv::kcsapi::category::aa_gun:
            return 1.2 * std::sqrt(equipment.level());

        case kcv::kcsapi::category::submarine_torpedo:
            return 0.2 * equipment.level();

        default:
            return 0;
    }
}

auto total_torpedo_improvement_bonus(const kcv::ship& ship) -> kcv::number {
    auto total = kcv::number{0};

    for (const auto& slot : ship.slots()) {
        if (slot.equipment().has_value()) {
            total += torpedo_improvement_bonus(*slot.equipment());
        }
    }

    return total;
}

/// @brief 雷撃の基本攻撃力を返す.
auto torpedo_attack_power(const kcv::battlelog& data) -> kcv::number {
    const auto& attacker = kcv::get_attacker(data);

    const auto base_value = 5;
    const auto torpedo    = attacker.torpedo();
    // TODO: 熟練甲板要員+航空整備員.ボーナス.雷装
    const auto improvement = total_torpedo_improvement_bonus(attacker);
    // TODO: 連合艦隊補正.

    return base_value + torpedo + improvement;
}

}  // namespace basic_attack_power_impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::basic_attack_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    namespace impl = kcv::modifiers::basic_attack_power_impl;

    switch (data.phase) {
        case kcv::phase::opening_taisen:
            throw kcv::exception{"not impl"};

        case kcv::phase::opening_atack:
            return impl::torpedo_attack_power(data);

        case kcv::phase::hougeki:
            throw kcv::exception{"not impl"};

        case kcv::phase::raigeki:
            return impl::torpedo_attack_power(data);

        case kcv::phase::midnight:
        case kcv::phase::friendly:
            throw kcv::exception{"not impl"};
    }

    return kcv::number{};
}

auto mod::f0(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f0 {
    // if (ctx.既存補正をoff) { return ctx.置換; }
    return kcv::functions::f0{};
}

namespace kcv::modifiers {
namespace {
namespace engagement_impl {

auto default_modifier() noexcept -> kcv::functions::engagement {
    return kcv::functions::engagement{};
}

auto special_kongou(const kcv::battlelog& data) noexcept -> kcv::functions::engagement {
    switch (data.engagement) {
        case kcv::kcsapi::engagement::green_t:
            return kcv::functions::engagement{.a = 1.25};

        case kcv::kcsapi::engagement::parallel:
        case kcv::kcsapi::engagement::head_on:
            return kcv::functions::engagement{.a = 1.0};

        case kcv::kcsapi::engagement::red_t:
            return kcv::functions::engagement{.a = 0.8};
    }

    return default_modifier();
}

auto nelson_touch(const kcv::battlelog& data) noexcept -> kcv::functions::engagement {
    switch (data.engagement) {
        case kcv::kcsapi::engagement::green_t:
        case kcv::kcsapi::engagement::parallel:
        case kcv::kcsapi::engagement::head_on:
            return kcv::functions::engagement{.a = 1.0};

        case kcv::kcsapi::engagement::red_t:
            return kcv::functions::engagement{.a = 1.25};
    }

    return default_modifier();
}

auto midnight_modifier(const kcv::battlelog& data) -> kcv::functions::engagement {
    switch (std::get<kcv::kcsapi::night_attack_kind>(data.attack_kind)) {
        case kcv::kcsapi::night_attack_kind::normal_attack:
            // 僚艦夜戦突撃を交戦形態補正とするならばネルソンタッチもここだろう.
            // ソース無し.
            return nelson_touch(data);

        case kcv::kcsapi::night_attack_kind::special_kongou:
            // 僚艦夜戦突撃のT字有利およびT字不利の補正は, 本体の補正より前に位置するため交戦形態補正の一種とする.
            // https://x.com/hedgehog_hasira/status/1654086587649753088
            return special_kongou(data);

        default:
            return default_modifier();
    }
}

auto primary_modifier(const kcv::battlelog& data) -> kcv::functions::engagement {
    switch (data.engagement) {
        case kcv::kcsapi::engagement::green_t:
            return kcv::functions::engagement{.a = 1.2};

        case kcv::kcsapi::engagement::parallel:
            return kcv::functions::engagement{.a = 1.0};

        case kcv::kcsapi::engagement::head_on:
            return kcv::functions::engagement{.a = 0.8};

        case kcv::kcsapi::engagement::red_t:
            return kcv::functions::engagement{.a = 0.6};
    }

    return default_modifier();
}

}  // namespace engagement_impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::engagement(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::engagement {
    namespace impl = kcv::modifiers::engagement_impl;

    // if (ctx.既存補正をoff) { return ctx.置換; }

    switch (data.phase) {
        case kcv::phase::opening_taisen:
        case kcv::phase::opening_atack:
        case kcv::phase::hougeki:
        case kcv::phase::raigeki:
            return impl::primary_modifier(data);

        case kcv::phase::midnight:
        case kcv::phase::friendly:
            return impl::midnight_modifier(data);
    }
}

namespace kcv::modifiers {
namespace {
namespace formation_impl {

auto default_modifier() noexcept -> kcv::functions::formation {
    return kcv::functions::formation{};
}

bool is_vanguard_main_in_combined_fleet(const kcv::battlelog& data) {
    constexpr auto escort_flagship_index = 6uz;
    switch (data.attacker_ship) {
        case escort_flagship_index:
        case escort_flagship_index + 1:
        case escort_flagship_index + 2:
            return true;

        default:
            return false;
    }
}

bool is_vanguard_main_in_single_fleet(const kcv::battlelog& data) {
    const auto& attacker_fleet = kcv::get_attacker_fleet(data);
    return static_cast<double>(data.attacker_ship + 1) / attacker_fleet.ships().size() > 0.5;
}

bool is_vanguard_main(const kcv::battlelog& data) noexcept {
    const auto& attacker_fleet_data = kcv::get_attacker_fleet_data(data);
    const bool is_single_fleet      = attacker_fleet_data.combined_flag() == 0;
    if (is_single_fleet) {
        return is_vanguard_main_in_single_fleet(data);
    }

    return is_vanguard_main_in_combined_fleet(data);
}

auto vanguard_in_midnight_modifier(const kcv::battlelog& data) -> kcv::functions::formation {
    if (is_vanguard_main(data)) {
        return kcv::functions::formation{.a = 0.5};
    }

    return kcv::functions::formation{.a = 1.0};
}

auto midnight_modifier(const kcv::battlelog& data) -> kcv::functions::formation {
    switch (kcv::get_attacker_formation(data)) {
        case kcv::kcsapi::formation::vanguard:
            return vanguard_in_midnight_modifier(data);

        default:
            return kcv::functions::formation{.a = 1.0};
    }
}

auto vanguard_in_shelling_modifier(const kcv::battlelog& data) -> kcv::functions::formation {
    if (is_vanguard_main(data)) {
        return kcv::functions::formation{.a = 0.5};
    }

    return kcv::functions::formation{.a = 1.0};
}

auto shelling_modifier(const kcv::battlelog& data) -> kcv::functions::formation {
    switch (kcv::get_attacker_formation(data)) {
        case kcv::kcsapi::formation::line_ahead:
            return kcv::functions::formation{.a = 1.0};

        case kcv::kcsapi::formation::double_line:
            return kcv::functions::formation{.a = 0.8};

        case kcv::kcsapi::formation::diamond:
            return kcv::functions::formation{.a = 0.7};

        case kcv::kcsapi::formation::echelon:
            return kcv::functions::formation{.a = 0.75};

        case kcv::kcsapi::formation::line_abreast:
            return kcv::functions::formation{.a = 0.6};

        case kcv::kcsapi::formation::vanguard:
            return vanguard_in_shelling_modifier(data);

        case kcv::kcsapi::formation::Cruising1:
            return kcv::functions::formation{.a = 0.8};

        case kcv::kcsapi::formation::Cruising2:
            return kcv::functions::formation{.a = 1.0};

        case kcv::kcsapi::formation::Cruising3:
            return kcv::functions::formation{.a = 0.7};

        case kcv::kcsapi::formation::Cruising4:
            return kcv::functions::formation{.a = 1.1};
    }

    return default_modifier();
}

auto torpedo_modifier(const kcv::battlelog& data) -> kcv::functions::formation {
    switch (kcv::get_attacker_formation(data)) {
        case kcv::kcsapi::formation::line_ahead:
            return kcv::functions::formation{.a = 1.0};

        case kcv::kcsapi::formation::double_line:
            return kcv::functions::formation{.a = 0.8};

        case kcv::kcsapi::formation::diamond:
            return kcv::functions::formation{.a = 0.7};

        case kcv::kcsapi::formation::echelon:
            return kcv::functions::formation{.a = 0.6};

        case kcv::kcsapi::formation::line_abreast:
            return kcv::functions::formation{.a = 0.6};

        case kcv::kcsapi::formation::vanguard:
            return kcv::functions::formation{.a = 1.0};

        case kcv::kcsapi::formation::Cruising1:
            return kcv::functions::formation{.a = 0.7};

        case kcv::kcsapi::formation::Cruising2:
            return kcv::functions::formation{.a = 0.9};

        case kcv::kcsapi::formation::Cruising3:
            return kcv::functions::formation{.a = 0.6};

        case kcv::kcsapi::formation::Cruising4:
            return kcv::functions::formation{.a = 1.0};
    }

    return default_modifier();
}

auto vanguard_in_asw_modifier(const kcv::battlelog& data) -> kcv::functions::formation {
    if (is_vanguard_main(data)) {
        return kcv::functions::formation{.a = 1.0};
    }

    return kcv::functions::formation{.a = 0.6};
}

auto asw_modifier(const kcv::battlelog& data) -> kcv::functions::formation {
    switch (kcv::get_attacker_formation(data)) {
        case kcv::kcsapi::formation::line_ahead:
            return kcv::functions::formation{.a = 0.6};

        case kcv::kcsapi::formation::double_line:
            return kcv::functions::formation{.a = 0.8};

        case kcv::kcsapi::formation::diamond:
            return kcv::functions::formation{.a = 1.2};

        case kcv::kcsapi::formation::echelon:
            return kcv::functions::formation{.a = 1.1};

        case kcv::kcsapi::formation::line_abreast:
            return kcv::functions::formation{.a = 1.3};

        case kcv::kcsapi::formation::vanguard:
            return vanguard_in_asw_modifier(data);

        case kcv::kcsapi::formation::Cruising1:
            return kcv::functions::formation{.a = 1.3};

        case kcv::kcsapi::formation::Cruising2:
            return kcv::functions::formation{.a = 1.1};

        case kcv::kcsapi::formation::Cruising3:
            return kcv::functions::formation{.a = 1.0};

        case kcv::kcsapi::formation::Cruising4:
            return kcv::functions::formation{.a = 0.7};
    }

    return default_modifier();
}

}  // namespace formation_impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::formation(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::formation {
    namespace impl = kcv::modifiers::formation_impl;

    // if (ctx.既存補正をoff) { return ctx.置換; }

    switch (data.phase) {
        case kcv::phase::opening_taisen:
            return impl::asw_modifier(data);

        case kcv::phase::opening_atack:
            return impl::torpedo_modifier(data);

        case kcv::phase::hougeki:
            return impl::shelling_modifier(data);

        case kcv::phase::raigeki:
            return impl::torpedo_modifier(data);

        case kcv::phase::midnight:
        case kcv::phase::friendly:
            return impl::midnight_modifier(data);
    }

    return impl::default_modifier();
}

namespace kcv::modifiers {
namespace {
namespace damage_state_impl {

auto get_attacker_damage_state(const kcv::battlelog& data) -> kcv::damage_state {
    const auto& attacker = kcv::get_attacker(data);
    return kcv::to_damage_state(attacker.hp(), attacker.maxhp());
}

auto default_modifier() noexcept -> kcv::functions::damage_state {
    return kcv::functions::damage_state{};
}

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
            /// TODO: 要検討. 刺し違え雷撃.
            return default_modifier();
    }
}

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
            return default_modifier();
    }
}

}  // namespace damage_state_impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::damage_state(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::damage_state {
    namespace impl = kcv::modifiers::damage_state_impl;

    // if (ctx.既存補正をoff) { return ctx.置換; }

    switch (data.phase) {
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
            // 夜戦における大破艦のネルソンタッチは*0.4なので夜戦の大破補正は*0.4といえる.
            return impl::primary_modifier(data);
    }
}

namespace kcv::modifiers {
namespace {
namespace pre_asw_impl {

auto default_modifier() noexcept -> kcv::functions::pre_asw {
    return kcv::functions::pre_asw{};
}

}  // namespace pre_asw_impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::pre_asw(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::pre_asw {
    namespace impl = kcv::modifiers::pre_asw_impl;

    // if (ctx.既存補正をoff) { return ctx.置換; }

    if (const bool is_asw = kcv::is_submarine(kcv::get_defender(data).mst()); is_asw) {
        const auto& attacker        = kcv::get_attacker(data);
        const bool has_sonor        = kcv::has_equipment(attacker, kcv::is_sonor);
        const bool has_depth_charge = kcv::has_equipment(attacker, kcv::is_depth_charge);
        if (has_sonor and has_depth_charge) {
            return kcv::functions::pre_asw{.a = 1.15};
        }
    }

    return impl::default_modifier();
}

namespace kcv::modifiers {
namespace {
namespace post_asw_impl {

auto default_modifier() noexcept -> kcv::functions::post_asw {
    return kcv::functions::post_asw{};
}

}  // namespace post_asw_impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::post_asw(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::post_asw {
    namespace impl = kcv::modifiers::post_asw_impl;

    // if (ctx.既存補正をoff) { return ctx.置換; }

    if (const bool is_asw = kcv::is_submarine(kcv::get_defender(data).mst()); is_asw) {
        const auto& attacker                    = kcv::get_attacker(data);
        const bool has_depth_charge_projector   = kcv::has_equipment(attacker, kcv::is_depth_charge_projector);
        const bool has_synergistic_depth_charge = kcv::has_equipment(attacker, kcv::is_synergistic_depth_charge);
        if (has_depth_charge_projector and has_synergistic_depth_charge) {
            const bool has_small_sonor = kcv::has_equipment(attacker, [](const auto& mst) static -> bool {
                return std::get<kcv::kcsapi::idx_type::category>(mst.api_type) == kcv::kcsapi::category::sonar;
            });
            if (has_small_sonor) {
                return kcv::functions::post_asw{.a = 1.25};
            } else {
                return kcv::functions::post_asw{.a = 1.1};
            }
        }
    }

    return impl::default_modifier();
}

auto mod::f14(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f14 {
    // if (ctx.既存補正をoff) { return ctx.置換; }
    return kcv::functions::f14{};
}

namespace kcv::modifiers {
namespace {
namespace fit_gun_impl {

auto default_modifier() noexcept -> kcv::functions::fit_gun {
    return kcv::functions::fit_gun{};
}

auto italian_fit_gun_modifier(const kcv::battlelog& data) -> kcv::functions::fit_gun {
    const auto& attacker       = kcv::get_attacker(data);
    const auto italian_gun_num = kcv::number{
        static_cast<kcv::number::base_type>(kcv::count_equipment(attacker, kcv::is_italian_fit_main_gun)),
    };
    return kcv::functions::fit_gun{.b = kcv::sqrt(italian_gun_num)};
}

auto cl_fit_gun_modifier(const kcv::battlelog& data) -> kcv::functions::fit_gun {
    const auto& attacker    = kcv::get_attacker(data);
    const auto main_gun_num = kcv::number{
        static_cast<kcv::number::base_type>(kcv::count_equipment(attacker, kcv::is_cl_fit_main_gun)),
    };
    const auto secondary_gun_num = kcv::number{
        static_cast<kcv::number::base_type>(kcv::count_equipment(attacker, kcv::is_cl_fit_secondary_gun)),
    };
    return kcv::functions::fit_gun{.b = 2 * kcv::sqrt(main_gun_num) + kcv::sqrt(secondary_gun_num)};
}

auto fit_gun_modifier(const kcv::battlelog& data) -> kcv::functions::fit_gun {
    const auto& attacker = kcv::get_attacker(data);
    if (kcv::is_cl(attacker.mst())) {
        return cl_fit_gun_modifier(data);
    }

    if (kcv::is_italian_ca(attacker.mst())) {
        return italian_fit_gun_modifier(data);
    }

    return default_modifier();
}

}  // namespace fit_gun_impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::fit_gun(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::fit_gun {
    namespace impl = kcv::modifiers::fit_gun_impl;

    // if (ctx.既存補正をoff) { return ctx.置換; }

    switch (data.phase) {
        case kcv::phase::opening_taisen:
            return impl::default_modifier();

        case kcv::phase::opening_atack:
        case kcv::phase::hougeki:
            return impl::fit_gun_modifier(data);

        case kcv::phase::raigeki:
            return impl::default_modifier();

        case kcv::phase::midnight:
        case kcv::phase::friendly:
            return impl::fit_gun_modifier(data);
    }

    return impl::default_modifier();
}

namespace kcv::modifiers {
namespace {
namespace softcap_impl {

static bool is_asw(const kcv::battlelog& data) {
    return kcv::is_submarine(kcv::get_defender(data).mst());
}

static bool is_torpedo(const kcv::battlelog& data) {
    switch (data.phase) {
        case kcv::phase::opening_atack:
        case kcv::phase::raigeki:
            return true;

        default:
            return false;
    }
}

static bool is_shelling(const kcv::battlelog& data) {
    switch (data.phase) {
        case kcv::phase::hougeki:
            return true;

        default:
            return false;
    }
}

static bool is_midnight(const kcv::battlelog& data) {
    switch (data.phase) {
        case kcv::phase::midnight:
            return true;

        default:
            return false;
    }
}

}  // namespace softcap_impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::softcap(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::softcap {
    namespace impl = kcv::modifiers::softcap_impl;

    // 夜戦より前に判定しなければ, 連合夜戦対潜を扱えないかも?
    if (impl::is_asw(data)) {
        return kcv::functions::softcap{.cap = 170};
    }

    if (impl::is_torpedo(data)) {
        return kcv::functions::softcap{.cap = 180};
    }

    if (impl::is_shelling(data)) {
        return kcv::functions::softcap{.cap = 220};
    }

    if (impl::is_midnight(data)) {
        return kcv::functions::softcap{.cap = 360};
    }

    return kcv::functions::softcap{.cap = std::numeric_limits<kcv::number::base_type>::infinity()};
}

auto mod::f5(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f5 {
    // if (ctx.既存補正をoff) { return ctx.置換; }
    return kcv::functions::f5{};
}

auto mod::floor_f5(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::floor_if {
    return kcv::functions::floor_if{.is_enabled = true};
}

auto mod::f6(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f6 {
    // if (ctx.既存補正をoff) { return ctx.置換; }
    return kcv::functions::f6{};
}

auto mod::f7(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f7 {
    // if (ctx.既存補正をoff) { return ctx.置換; }
    return kcv::functions::f7{};
}

auto mod::floor_f7(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::floor_if {
    return kcv::functions::floor_if{.is_enabled = true};
}

auto mod::map(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::map {
    // if (ctx.既存補正をoff) { return ctx.置換; }
    return kcv::functions::map{};
}

auto mod::event(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::event {
    // if (ctx.既存補正をoff) { return ctx.置換; }
    return kcv::functions::event{};
}

auto mod::f8(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f8 {
    // if (ctx.既存補正をoff) { return ctx.置換; }
    return kcv::functions::f8{};
}

auto mod::pt_imp(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::pt_imp {
    // if (ctx.既存補正をoff) { return ctx.置換; }

    if (kcv::is_pt_imp(kcv::get_defender(data).mst())) {
        return kcv::functions::pt_imp{.is_enabled = true};
    }

    return kcv::functions::pt_imp{.is_enabled = false};
}

namespace kcv::modifiers {
namespace {
namespace pt_imp_equipment_impl {

using result_t = std::invoke_result_t<
    decltype(kcv::modifiers::pt_imp_equipment),  //
    const kcv::context_data&,
    const kcv::battlelog&>;

auto default_modifier() noexcept -> result_t {
    return kcv::functions::liner{}  //
         | kcv::functions::liner{}  //
         | kcv::functions::liner{}  //
         | kcv::functions::liner{}  //
         | kcv::functions::liner{}  //
         | kcv::functions::liner{}  //
         | kcv::functions::liner{}  //
         | kcv::functions::liner{}  //
         | kcv::functions::liner{}  //
         | kcv::functions::liner{}  //
    ;
}

using main_gun_small_modifiers_t = kcv::functions::composed_function<kcv::functions::liner, kcv::functions::liner>;

auto main_gun_small_modifiers(const kcv::battlelog& data) -> main_gun_small_modifiers_t {
    const auto& attacker         = kcv::get_attacker(data);
    const int main_gun_small_num = kcv::count_equipment(attacker, kcv::kcsapi::category::main_gun_small);

    const auto mod1 = main_gun_small_num >= 1 ? kcv::functions::liner{.a = 1.5} : kcv::functions::liner{.a = 1.0};
    const auto mod2 = main_gun_small_num >= 2 ? kcv::functions::liner{.a = 1.4} : kcv::functions::liner{.a = 1.0};
    return mod1 | mod2;
}

using aa_gun_small_modifiers_t = kcv::functions::composed_function<kcv::functions::liner, kcv::functions::liner>;

auto aa_gun_modifiers(const kcv::battlelog& data) -> aa_gun_small_modifiers_t {
    const auto& attacker = kcv::get_attacker(data);
    const int aa_gun_num = kcv::count_equipment(attacker, kcv::kcsapi::category::aa_gun);

    const auto mod1 = aa_gun_num >= 1 ? kcv::functions::liner{.a = 1.2} : kcv::functions::liner{.a = 1.0};
    const auto mod2 = aa_gun_num >= 2 ? kcv::functions::liner{.a = 1.2} : kcv::functions::liner{.a = 1.0};
    return mod1 | mod2;
}

auto secondary_gun_modifier(const kcv::battlelog& data) -> kcv::functions::liner {
    const auto& attcker          = kcv::get_attacker(data);
    const bool has_secondary_gun = kcv::has_equipment(attcker, kcv::kcsapi::category::secondary_gun);

    return has_secondary_gun ? kcv::functions::liner{.a = 1.3} : kcv::functions::liner{.a = 1.0};
}

using bomber_modifier_t = kcv::functions::composed_function<kcv::functions::liner, kcv::functions::liner>;

auto bomber_modifiers(const kcv::battlelog& data) -> bomber_modifier_t {
    const auto& attacker               = kcv::get_attacker(data);
    const int carrier_based_bomber_num = kcv::count_equipment(attacker, kcv::kcsapi::category::carrier_based_bomber);
    const int jet_bomber_num           = kcv::count_equipment(attacker, kcv::kcsapi::category::jet_bomber);
    const int max_bomber_num           = std::max(carrier_based_bomber_num, jet_bomber_num);

    const auto mod1 = max_bomber_num >= 1 ? kcv::functions::liner{.a = 1.4} : kcv::functions::liner{.a = 1.0};
    const auto mod2 = max_bomber_num >= 2 ? kcv::functions::liner{.a = 1.3} : kcv::functions::liner{.a = 1.0};
    return mod1 | mod2;
}

auto seaplane_modifier(const kcv::battlelog& data) -> kcv::functions::liner {
    const auto& attcker      = kcv::get_attacker(data);
    const bool has_seaplanes = kcv::has_equipment(attcker, kcv::kcsapi::category::seaplane_bomber)
                            or kcv::has_equipment(attcker, kcv::kcsapi::category::seaplane_fighter);

    return has_seaplanes ? kcv::functions::liner{.a = 1.2} : kcv::functions::liner{.a = 1.0};
}

auto surface_ship_personnel_modifier(const kcv::battlelog& data) -> kcv::functions::liner {
    const auto& attcker                   = kcv::get_attacker(data);
    const bool has_surface_ship_personnel = kcv::has_equipment(attcker, kcv::kcsapi::category::surface_ship_personnel);

    return has_surface_ship_personnel ? kcv::functions::liner{.a = 1.1} : kcv::functions::liner{.a = 1.0};
}

auto boat_modifier(const kcv::battlelog& data) -> kcv::functions::liner {
    const auto& attacker  = kcv::get_attacker(data);
    const int ab_boat_num = kcv::count_equipment(attacker, kcv::equipment_id("装甲艇(AB艇)"));
    const int armored_num = kcv::count_equipment(attacker, kcv::equipment_id("武装大発"));

    if (ab_boat_num >= 1 and armored_num >= 1) {
        return kcv::functions::liner{.a = 1.32};
    }

    if (ab_boat_num >= 1 or armored_num >= 1) {
        return kcv::functions::liner{.a = 1.2};
    }

    return kcv::functions::liner{.a = 1.0};
}

bool is_torpedo_attack(const kcv::battlelog& data) {
    switch (data.phase) {
        case kcv::phase::opening_atack:
        case kcv::phase::raigeki:
            return true;

        default:
            return false;
    }
}

}  // namespace pt_imp_equipment_impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::pt_imp_equipment(const kcv::context_data& ctx, const kcv::battlelog& data)
    -> kcv::functions::composed_function<
        kcv::functions::liner,  // 小口径主砲 [1]
        kcv::functions::liner,  // 小口径主砲 [2]
        kcv::functions::liner,  // 対空機銃 [1]
        kcv::functions::liner,  // 対空機銃 [2]
        kcv::functions::liner,  // 副砲
        kcv::functions::liner,  // 艦上爆撃機 | 噴式戦闘爆撃機 [1]
        kcv::functions::liner,  // 艦上爆撃機 | 噴式戦闘爆撃機 [2]
        kcv::functions::liner,  // 水上爆撃機 | 水上戦闘機
        kcv::functions::liner,  // 装甲艇(AB艇) & 武装大発
        kcv::functions::liner   // 装甲艇(AB艇) & 武装大発 ★
        >                       //
{
    namespace impl = kcv::modifiers::pt_imp_equipment_impl;

    // if (ctx.既存補正をoff) { return ctx.置換; }
    if (kcv::is_pt_imp(kcv::get_defender(data).mst())) {
        if (not impl::is_torpedo_attack(data)) {
            return impl::main_gun_small_modifiers(data)         //
                 | impl::aa_gun_modifiers(data)                 //
                 | impl::secondary_gun_modifier(data)           //
                 | impl::bomber_modifiers(data)                 //
                 | impl::seaplane_modifier(data)                //
                 | impl::surface_ship_personnel_modifier(data)  //
                 | impl::boat_modifier(data)                    //
                ;
        }
    }

    return impl::default_modifier();
}

auto mod::pt_imp_midnight(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::liner {
    // if (ctx.既存補正をoff) { return ctx.置換; }

    if (kcv::is_pt_imp(kcv::get_defender(data).mst())) {
        if (data.phase == kcv::phase::midnight) {
            return kcv::functions::liner{.a = 0.6};
        }
    }

    return kcv::functions::liner{.a = 1.0};
}

auto mod::critical(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::critical {
    // if (ctx.既存補正をoff) { return ctx.置換; }

    return kcv::functions::critical{.is_enabled = kcv::is_critical(data)};
}

auto mod::floor_if_critical(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::floor_if {
    // if (ctx.既存補正をoff) { return ctx.置換; }

    return kcv::functions::floor_if{.is_enabled = kcv::is_critical(data)};
}