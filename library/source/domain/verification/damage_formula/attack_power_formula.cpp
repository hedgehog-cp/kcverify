#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"

// std
#include <algorithm>
#include <array>
#include <concepts>
#include <functional>
#include <initializer_list>
#include <optional>
#include <ranges>
#include <span>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>

// kcv
#include "kcv/core/constants/equipment.hpp"
#include "kcv/core/constants/equipment_attributes.hpp"
#include "kcv/core/constants/ship.hpp"
#include "kcv/core/constants/ship_attributes.hpp"
#include "kcv/core/context_data.hpp"
#include "kcv/core/numeric/composed_function.hpp"
#include "kcv/core/numeric/interval.hpp"
#include "kcv/core/numeric/interval/basic_interval.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"
#include "kcv/domain/verification/entity/ship.hpp"
#include "kcv/domain/verification/logic/logic.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_ship.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcv/external/kcsapi/extensions/damage_state.hpp"
#include "kcv/external/kcsapi/extensions/utility.hpp"
#include "kcv/external/kcsapi/types/enum/category.hpp"
#include "kcv/external/kcsapi/types/enum/day_attack_kind.hpp"
#include "kcv/external/kcsapi/types/enum/engagement.hpp"
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"
#include "kcv/external/kcsapi/types/enum/formation.hpp"
#include "kcv/external/kcsapi/types/enum/icon.hpp"
#include "kcv/external/kcsapi/types/enum/night_attack_kind.hpp"
#include "kcv/std_ext/exception.hpp"
#include "kcv/std_ext/utility.hpp"

auto kcv::formulate_attack_power(
    const kcv::context_data& ctx,  //
    const kcv::battlelog& data     //
) -> kcv::attack_power_formula {
    return kcv::attack_power_formula{
        kcv::modifiers::base_attack_power(ctx, data),
        kcv::modifiers::f0(ctx, data)                  //
            | kcv::modifiers::air_attack(ctx, data)    //
            | kcv::modifiers::engagement(ctx, data)    //
            | kcv::modifiers::formation(ctx, data)     //
            | kcv::modifiers::night(ctx, data)         //
            | kcv::modifiers::dd_d_gun(ctx, data)      //
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
            | kcv::modifiers::day(ctx, data)           //
            | kcv::modifiers::ap(ctx, data)            //
            | kcv::modifiers::floor_if_ap(ctx, data)   //
            | kcv::modifiers::map(ctx, data)           //
            | kcv::modifiers::event(ctx, data)         //
            | kcv::modifiers::f8(ctx, data)            //
            | kcv::modifiers::pt_imp(ctx, data)        //
            // | kcv::modifiers::pt_imp_equipment(ctx, data)
            // | kcv::modifiers::pt_imp_midnight(ctx, data)
            | kcv::modifiers::critical(ctx, data)           //
            | kcv::modifiers::proficiency(ctx, data)        //
            | kcv::modifiers::floor_if_critical(ctx, data)  //
        ,
    };
}

// 長いのでエイリアス.
namespace mod = kcv::modifiers;

// 各補正の実装詳細は `kcv::modifiers::(anonymous)::impl` 名前空間に包んで実装し, namespace impl = ...; とともに使う.
// namespace kcv::modifiers { namespace { namespace impl { auto func() { ... } } }}
// auto kcv::modifiers::foo() { namespace impl = kcv::modifiers::impl; return impl::func(); }

// -----------------------------------------------------------------------------
// 基本攻撃力の実装を`base_attack_power.cpp`に分離する.
// auto kcv::modifiers::base_attack_power(...) -> kcv::number { ... }
// -----------------------------------------------------------------------------

auto mod::f0(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f0 {
    // if (ctx.既存補正をoff) { return ctx.置換; }
    return kcv::functions::f0{};
}

// -----------------------------------------------------------------------------
// 砲撃戦.航空攻撃補正の実装を`air_attack_power.cpp`に分離する.
// auto kcv::modifiers::air_attack_power(...) -> kcv::functions::air_attack { ... }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 交戦形態補正の実装を`engagement.cpp`に分離する.
// auto kcv::modifiers::engagement(...) -> kcv::functions::engagement { ... }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 攻撃側陣形補正の実装を`formation.cpp`に分離する.
// auto kcv::modifiers::formation(...) -> kcv::functions::formation { ... }
// -----------------------------------------------------------------------------

namespace kcv::modifiers {
namespace {
namespace fleet_special_attack_impl {

// /// @todo ctypeを使う.
// bool is_nelson_class(const kcv::kcsapi::api_mst_ship_value_t& mst) {
//     switch (mst.api_id) {
//         using kcv::literals::ship_literals::operator""_id;
//         case "Nelson"_id:
//         case "Nelson改"_id:
//         case "Rodney"_id:
//         case "Rodney改"_id:
//             return true;
//
//         default:
//             return false;
//     }
// }
//
// auto nelson_touch(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
//     // T字不利の補正は交戦形態補正として適用する.
//
//     switch (data.attack_order) {
//         case 0: {
//             const auto& attacker_fleet   = kcv::get_attacker_fleet(data);
//             const bool is_nelson_class_3 = is_nelson_class(attacker_fleet.ships().at(2).mst());
//             const bool is_nelson_class_5 = is_nelson_class(attacker_fleet.ships().at(4).mst());
//             if (is_nelson_class_3 or is_nelson_class_5) {
//                 return 2 * 1.15;
//             }
//             return 2;
//         }
//
//         case 1:
//         case 2: {
//             const auto& attacker = kcv::get_attacker(data);
//             if (is_nelson_class(attacker.mst())) {
//                 return 2 * 1.2;
//             }
//             return 2;
//         }
//
//         default:
//             return 1;
//     }
// }
//
// auto special_nagato(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
//     //
// }

}  // namespace fleet_special_attack_impl
}  // namespace
}  // namespace kcv::modifiers

namespace kcv ::modifiers {
namespace {
namespace night_impl {

// std::optional<const T&>はC++26を待つため, rwでラップする.
using opt_mst_slotitem_value_t = std::optional<std::reference_wrapper<const kcv::kcsapi::api_mst_slotitem_value_t>>;

/// @brief i番目の装備とi番目の述語関数とが全て満たすならばtrueを返す.
template <std::predicate<const kcv::kcsapi::api_mst_slotitem_value_t&>... Preds>
bool matches_equipments(std::span<const opt_mst_slotitem_value_t> equipments, Preds&&... preds) {
    if (std::ranges::size(equipments) != sizeof...(Preds)) {
        return false;
    }

    auto i = 0uz;
    return ((equipments[i].has_value() and std::invoke(preds, equipments[i++]->get())) and ...);
}

bool is_submarine_equipment(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    return std::get<kcv::kcsapi::category>(mst.api_type) == kcv::kcsapi::category::submarine_equipment;
}

bool is_torpedo(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    return std::get<kcv::kcsapi::category>(mst.api_type) == kcv::kcsapi::category::torpedo;
}

auto cutin_torpedo_torpedo(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    // 表示装備がある場合は, 表示装備の個数==data.display_equipments.size();
    // -1でパディングされることはないはず.
    const auto display_equipments = data.display_equipments  //
                                  | std::ranges::views::transform([&ctx](auto id) -> opt_mst_slotitem_value_t {
                                        if (id == kcv::kcsapi::invalid_equipment_id) {
                                            return std::nullopt;
                                        }
                                        return std::make_optional(std::cref(kcv::find_mst(ctx.api_mst_slotitem(), id)));
                                    })
                                  | std::ranges::to<std::vector>();

    // [潜電, 後期型潜水艦魚雷].
    if (matches_equipments(display_equipments, &is_submarine_equipment, &kcv::is_late_model_bow_torpedo)) {
        return 1.75;
    }

    // [後期型潜水艦魚雷, 後期型潜水艦魚雷].
    if (matches_equipments(display_equipments, &kcv::is_late_model_bow_torpedo, &kcv::is_late_model_bow_torpedo)) {
        return 1.6;
    }

    // [魚雷, 魚雷].
    if (matches_equipments(display_equipments, &is_torpedo, &is_torpedo)) {
        return 1.5;
    }

    return 1;
}

bool is_night_fighter(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    return std::get<kcv::kcsapi::icon>(mst.api_type) == kcv::kcsapi::icon::night_fighter;
}

bool is_night_attacker(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    return std::get<kcv::kcsapi::icon>(mst.api_type) == kcv::kcsapi::icon::night_attacker;
}

bool is_night_bomber(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    return std::get<kcv::kcsapi::icon>(mst.api_type) == kcv::kcsapi::icon::night_bomber;
}

bool is_photoelectric_fuze_bombs(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    return mst.api_id == kcv::equipment_id("彗星一二型(三一号光電管爆弾搭載機)");
}

auto cutin_air_attack(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    // 表示装備がある場合は, 表示装備の個数==data.display_equipments.size();
    // -1でパディングされることはないはず.
    const auto display_equipments = data.display_equipments  //
                                  | std::ranges::views::transform([&ctx](auto id) -> opt_mst_slotitem_value_t {
                                        if (id == kcv::kcsapi::invalid_equipment_id) {
                                            return std::nullopt;
                                        }
                                        return std::make_optional(std::cref(kcv::find_mst(ctx.api_mst_slotitem(), id)));
                                    })
                                  | std::ranges::to<std::vector>();

    // [夜戦, 夜攻].
    if (matches_equipments(display_equipments, &is_night_fighter, &is_night_attacker)) {
        return 1.2;
    }

    // [夜戦, 光電管].
    if (matches_equipments(display_equipments, &is_night_fighter, &is_photoelectric_fuze_bombs)) {
        return 1.2;
    }

    // [夜攻, 光電管].
    if (matches_equipments(display_equipments, &is_night_attacker, &is_night_attacker)) {
        return 1.2;
    }

    // [夜戦, 夜爆].
    if (matches_equipments(display_equipments, &is_night_fighter, &is_night_bomber)) {
        return 1.2;
    }

    // [夜攻, 夜爆].
    if (matches_equipments(display_equipments, &is_night_fighter, &is_night_bomber)) {
        return 1.2;
    }

    // [夜爆, 光電管].
    if (matches_equipments(display_equipments, &is_night_bomber, &is_photoelectric_fuze_bombs)) {
        return 1.2;
    }

    // [夜戦, 夜間機, 夜間機].
    if (matches_equipments(display_equipments, &is_night_fighter, &kcv::is_night_plane, &kcv::is_night_plane)) {
        // [夜戦, 夜戦, 夜攻].
        if (matches_equipments(display_equipments, &is_night_fighter, &is_night_fighter, &is_night_attacker)) {
            // 判定不可能だが例外送出しないためにとりあえず返す.
            return kcv::number{1.18, 1.25};
        }
        return 1.18;
    }

    return 1;
}

}  // namespace night_impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::night(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::night {
    namespace impl = kcv::modifiers::night_impl;

    // 戦闘フェーズを参照せずとも攻撃種別から夜間攻撃であることを判定でき, 直接的に補正値の分岐を記述できる.
    return std::visit(
        kcv::overloaded{
            [](const auto&) static noexcept -> kcv::functions::night { return kcv::functions::night{}; },
            [&ctx, &data](const kcv::kcsapi::night_attack_kind& v) -> kcv::functions::night {
                switch (v) {
                    case kcv::kcsapi::night_attack_kind::double_shelling:
                        return kcv::functions::night{.a = 1.2};

                    case kcv::kcsapi::night_attack_kind::cutin_main_torpedo:
                        return kcv::functions::night{.a = 1.3};

                    case kcv::kcsapi::night_attack_kind::cutin_torpedo_torpedo:
                        return kcv::functions::night{.a = impl::cutin_torpedo_torpedo(ctx, data)};

                    case kcv::kcsapi::night_attack_kind::cutin_main_sub:
                        return kcv::functions::night{.a = 1.75};

                    case kcv::kcsapi::night_attack_kind::cutin_main_main:
                        return kcv::functions::night{.a = 2};

                    case kcv::kcsapi::night_attack_kind::cutin_air_attack:
                        return kcv::functions::night{.a = impl::cutin_air_attack(ctx, data)};

                    case kcv::kcsapi::night_attack_kind::cutin_torpedo_radar:
                        return kcv::functions::night{.a = 1.3};

                    case kcv::kcsapi::night_attack_kind::cutin_torpedo_picket:
                        return kcv::functions::night{.a = 1.2};

                    case kcv::kcsapi::night_attack_kind::cutin_torpedo_destroyer_picket:
                        return kcv::functions::night{.a = 1.5};

                    case kcv::kcsapi::night_attack_kind::cutin_torpedo_drum:
                        return kcv::functions::night{.a = 1.3};

                    case kcv::kcsapi::night_attack_kind::cutin_torpedo_radar_2:
                        return kcv::functions::night{.a = 1.3};

                    case kcv::kcsapi::night_attack_kind::cutin_torpedo_picket_2:
                        return kcv::functions::night{.a = 1.2};

                    case kcv::kcsapi::night_attack_kind::cutin_torpedo_destroyer_picket_2:
                        return kcv::functions::night{.a = 1.5};

                    case kcv::kcsapi::night_attack_kind::cutin_torpedo_drum_2:
                        return kcv::functions::night{.a = 1.3};

                    case kcv::kcsapi::night_attack_kind::special_nelson:
                    case kcv::kcsapi::night_attack_kind::special_nagato:
                    case kcv::kcsapi::night_attack_kind::special_mutsu:
                    case kcv::kcsapi::night_attack_kind::special_colorado:
                    case kcv::kcsapi::night_attack_kind::special_kongou:
                    case kcv::kcsapi::night_attack_kind::special_richelieu:
                    case kcv::kcsapi::night_attack_kind::special_queen_elizabeth_class:
                        return kcv::functions::night{};  // !!! not impl

                    case kcv::kcsapi::night_attack_kind::cutin_zuiun:
                        // とりあえず区間に包む.
                        return kcv::functions::night{.a = kcv::number{1.24, 1.36}};

                    case kcv::kcsapi::night_attack_kind::special_submarine_tender_23:
                    case kcv::kcsapi::night_attack_kind::special_submarine_tender_34:
                    case kcv::kcsapi::night_attack_kind::special_submarine_tender_24:
                    case kcv::kcsapi::night_attack_kind::special_yamato_3_ships:
                    case kcv::kcsapi::night_attack_kind::special_yamato_2_ships:
                        return kcv::functions::night{};  // !!! not impl

                    default:
                        return kcv::functions::night{};
                }
            },
        },
        data.attack_kind
    );
}

namespace kcv::modifiers {
namespace {
namespace dd_d_gum_impl {

auto d2_or_d3(const kcv::battlelog& data) -> kcv::number {
    const auto& attacker = kcv::get_attacker(data);
    const auto d2_num    = kcv::count_equipment(attacker, kcv::equipment_id("12.7cm連装砲D型改二"));
    const auto d3_num    = kcv::count_equipment(attacker, kcv::equipment_id("12.7cm連装砲D型改三"));
    switch (d2_num + d3_num) {
        case 1:
            return 1.25;

        case 2:
            return 1.4;

        default:
            return 1;
    }
}

auto d3(const kcv::battlelog& data) -> kcv::number {
    const auto& attacker = kcv::get_attacker(data);
    const auto d3_num    = kcv::count_equipment(attacker, kcv::equipment_id("12.7cm連装砲D型改三"));
    switch (d3_num) {
        case 1:
            return 1.05;

        case 2:
            return 1.1;

        default:
            return 1;
    }
}

}  // namespace dd_d_gum_impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::dd_d_gun(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::dd_d_gun {
    namespace impl = kcv::modifiers::dd_d_gum_impl;

    // 戦闘フェーズを参照せずとも攻撃種別から駆逐艦の夜間攻撃であることを判定でき, 直接的に補正値の分岐を記述できる.
    return std::visit(
        kcv::overloaded{
            [](const auto&) static noexcept -> kcv::functions::dd_d_gun { return kcv::functions::dd_d_gun{}; },
            [&data](const kcv::kcsapi::night_attack_kind& v) -> kcv::functions::dd_d_gun {
                switch (v) {
                    case kcv::kcsapi::night_attack_kind::cutin_torpedo_radar:
                    case kcv::kcsapi::night_attack_kind::cutin_torpedo_picket:
                    case kcv::kcsapi::night_attack_kind::cutin_torpedo_radar_2:
                    case kcv::kcsapi::night_attack_kind::cutin_torpedo_picket_2:
                        // 乗算順序不明につき, 補正を分解しない.
                        return kcv::functions::dd_d_gun{.a = impl::d2_or_d3(data) * impl::d3(data)};

                    default:
                        return kcv::functions::dd_d_gun{};
                }
            },
        },
        data.attack_kind
    );
}

// -----------------------------------------------------------------------------
// 損傷状態補正の実装を`damage_state.cpp`に分離する.
// auto kcv::modifiers::damage_state(...) -> kcv::functions::damage_state { ... }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// 前対潜シナジー補正, 後対潜シナジー補正の実装を`asw_synergy.cpp`に分離する.
// auto kcv::modifiers::pre_asw(...) -> kcv::functions::pre_asw { ... }
// auto kcv::modifiers::post_asw(...) -> kcv::functions::post_asw { ... }
// -----------------------------------------------------------------------------

auto mod::f14(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::f14 {
    // if (ctx.既存補正をoff) { return ctx.置換; }
    return kcv::functions::f14{};
}

// -----------------------------------------------------------------------------
// フィット砲補正の実装を`fit_gun.cpp`に分離する.
// auto kcv::modifiers::fit_gun(...) -> kcv::functions::fit_gun { ... }
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// ソフトキャップ補正の実装を`softcap.cpp`に分離する.
// auto kcv::modifiers::softcap(...) -> kcv::functions::softcap { ... }
// -----------------------------------------------------------------------------

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

// -----------------------------------------------------------------------------
// 昼間特殊攻撃補正の実装を`day_special_attack.cpp`に分離する.
// auto kcv::modifiers::day(...) -> kcv::functions::day { ... }
// -----------------------------------------------------------------------------

namespace kcv::modifiers {
namespace {
namespace ap_impl {

/// @brief 徹甲弾攻撃であるかを検証する.
bool is_ap_shell_attack(const kcv::battlelog& data) {
    switch (data.phase) {
        case kcv::phase::sp_midnight:
        case kcv::phase::opening_taisen:
        case kcv::phase::opening_atack:
            return false;

        case kcv::phase::hougeki:
            return kcv::is_ap_shell_target(kcv::get_defender(data).mst())
               and kcv::has_equipment(kcv::get_attacker(data), kcv::kcsapi::category::ap_shell)
               and kcv::has_equipment(
                       kcv::get_attacker(data),  //
                       {
                           kcv::kcsapi::category::main_gun_small,
                           kcv::kcsapi::category::main_gun_medium,
                           kcv::kcsapi::category::main_gun_large,
                       }
               );

        case kcv::phase::raigeki:
        case kcv::phase::friendly:
        case kcv::phase::midnight:
            return false;
    }

    return false;
}

}  // namespace ap_impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::ap(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::ap {
    namespace impl = kcv::modifiers::ap_impl;

    if (impl::is_ap_shell_attack(data)) {
        // 徹甲弾と主砲とを搭載している.
        const auto& attacker = kcv::get_attacker(data);

        if (kcv::has_equipment(attacker, kcv::kcsapi::category::secondary_gun)) {
            return kcv::functions::ap{.a = 1.15};
        }

        if (kcv::has_equipment(attacker, &kcv::is_radar)) {
            return kcv::functions::ap{.a = 1.15};
        }

        return kcv::functions::ap{.a = 1.10};
    }

    return kcv::functions::ap{};
}

auto mod::floor_if_ap(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::floor_if {
    namespace impl = kcv::modifiers::ap_impl;

    return kcv::functions::floor_if{.is_enabled = impl::is_ap_shell_attack(data)};
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

// -----------------------------------------------------------------------------
// 急所弾補正, 熟練急所弾補正の実装を`critical.cpp`に分離する.
// auto kcv::modifiers::critical(...) -> kcv::functions::critical { ... }
// auto kcv::modifiers::proficiency(...) -> kcv::functions::proficiency { ... }
// auto kcv::modifiers::floor_if_critical(...) -> kcv::functions::floor_if { ... }
// -----------------------------------------------------------------------------
