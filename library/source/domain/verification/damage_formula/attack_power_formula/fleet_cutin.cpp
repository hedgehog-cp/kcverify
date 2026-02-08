#include "domain/verification/damage_formula/attack_power_formula/fleet_cutin.hpp"

// -----------------------------------------------------------------------------
// 攻撃力式のうち昼間特殊攻撃補正の実装をここに分離する.
// -----------------------------------------------------------------------------

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
#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"
#include "kcv/domain/verification/entity/equipment.hpp"
#include "kcv/domain/verification/entity/fleet.hpp"
#include "kcv/domain/verification/entity/ship.hpp"
#include "kcv/domain/verification/entity/slot.hpp"
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
#include "kcv/external/kcsapi/types/enum/stype.hpp"
#include "kcv/std_ext/exception.hpp"
#include "kcv/std_ext/utility.hpp"

namespace kcv::modifiers {
namespace {
namespace impl {
///
}
}  // namespace
}  // namespace kcv::modifiers

namespace mod = kcv::modifiers;

auto mod::special_nelson(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    throw kcv::exception{"not impl"};
}

namespace kcv::modifiers {
namespace {
namespace impl {

/// @brief 艦隊特殊砲撃における共通の装備補正を返す.
/// @details 攻撃艦が徹甲弾を搭載しているならば*1.35, 攻撃艦が水上電探を搭載しているならば*1.15
auto equipment_modifier(const kcv::ship& attacker) -> kcv::number {
    const auto ap_shell      = kcv::has_equipment(attacker, kcv::kcsapi::category::ap_shell) ? 1.35 : 1.0;
    const auto surface_radar = kcv::has_equipment(attacker, &kcv::is_surface_radar) ? 1.15 : 1.0;
    return ap_shell * surface_radar;
}

}  // namespace impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::special_nagato(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    throw kcv::exception{"not impl"};
}

auto mod::special_mutsu(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    throw kcv::exception{"not impl"};
}

auto mod::special_colorado(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    throw kcv::exception{"not impl"};
}

auto mod::special_kongou(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    throw kcv::exception{"not impl"};
}

auto mod::special_richelieu(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    throw kcv::exception{"not impl"};
}

auto mod::special_queen_elizabeth_class(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    throw kcv::exception{"not impl"};
}

auto mod::special_submarine_tender_23(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    throw kcv::exception{"not impl"};
}

auto mod::special_submarine_tender_34(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    throw kcv::exception{"not impl"};
}

auto mod::special_submarine_tender_24(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    throw kcv::exception{"not impl"};
}

auto mod::special_yamato_3_ships(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    throw kcv::exception{"not impl"};
}

namespace kcv::modifiers {
namespace {
namespace impl {

/// @brief (旗艦が大和改二または大和改二重)かつ(僚艦が武蔵改二)であるかを検証する.
bool is_yamato_kai2_musashi_kai2(const kcv::fleet& attacker_fleet) {
    const auto flagship_id    = attacker_fleet.ships().at(0).mst().api_id;
    const bool is_yamato_kai2 = flagship_id == kcv::ship_id("大和改二") or flagship_id == kcv::ship_id("大和改二重");

    const auto consort_id      = attacker_fleet.ships().at(1).mst().api_id;
    const bool is_musashi_kai2 = consort_id == kcv::ship_id("武蔵改二");

    return is_yamato_kai2 and is_musashi_kai2;
}

/// @brief (旗艦が武蔵改二)かつ(僚艦が大和改二または大和改二重)であるかを検証する.
bool is_musashi_kai2_yamato_kai2(const kcv::fleet& attacker_fleet) {
    const auto flagship_id     = attacker_fleet.ships().at(0).mst().api_id;
    const bool is_musashi_kai2 = flagship_id == kcv::ship_id("武蔵改二");

    const auto consort_id     = attacker_fleet.ships().at(1).mst().api_id;
    const bool is_yamato_kai2 = consort_id == kcv::ship_id("大和改二") or consort_id == kcv::ship_id("大和改二重");

    return is_musashi_kai2 and is_yamato_kai2;
}

/// @brief (旗艦が武蔵改二)かつ(僚艦が大和改二重)であるかを検証する.
bool is_musashi_kai2_yamato_kai2_heavy(const kcv::fleet& attacker_fleet) {
    const auto flagship_id     = attacker_fleet.ships().at(0).mst().api_id;
    const bool is_musashi_kai2 = flagship_id == kcv::ship_id("武蔵改二");

    const auto consort_id           = attacker_fleet.ships().at(1).mst().api_id;
    const bool is_yamato_kai2_heavy = consort_id == kcv::ship_id("大和改二重");

    return is_musashi_kai2 and is_yamato_kai2_heavy;
}

/// @brief 装備が15m二重測距儀+21号電探改二または15m二重測距儀改+21号電探改二+熟練射撃指揮所であるかを検証する.
bool is_15m_duplex_rangefinder(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::equipment_literals::operator""_id;
        case "15m二重測距儀+21号電探改二"_id:
        case "15m二重測距儀改+21号電探改二+熟練射撃指揮所"_id:
            return true;

        default:
            return false;
    }
}

/// @brief 攻撃艦が15m二重測距儀+21号電探改二または15m二重測距儀改+21号電探改二+熟練射撃指揮所を搭載しているかを検証する.
bool has_15m_duplex_rangefinder(const kcv::ship& attacker) {
    return kcv::has_equipment(attacker, &impl::is_15m_duplex_rangefinder);
}

/// @brief 第一戦隊、突撃！主砲、全力斉射ッ！の1撃目の補正値を返す.
auto special_yamato_2_ships_1st_attack(const kcv::battlelog& data) -> kcv::number {
    const auto& attacker_fleet = kcv::get_attacker_fleet(data);
    const auto& attacker       = kcv::get_attacker(data);

    const auto base = 1.4;

    const auto combination = impl::is_yamato_kai2_musashi_kai2(attacker_fleet)          //
                                  or impl::is_musashi_kai2_yamato_kai2(attacker_fleet)  //
                               ? 1.1
                               : 1.0;

    const auto radar = impl::has_15m_duplex_rangefinder(attacker) ? 1.1 : 1.0;

    const auto equipment = impl::equipment_modifier(attacker);

    return base * combination * radar * equipment;
}

/// @brief 第一戦隊、突撃！主砲、全力斉射ッ！の2撃目の補正値を返す.
auto special_yamato_2_ships_2nd_attack(const kcv::battlelog& data) -> kcv::number {
    const auto& attacker_fleet = kcv::get_attacker_fleet(data);
    const auto& attacker       = kcv::get_attacker(data);

    const auto base = 1.4;

    const auto combination = impl::is_yamato_kai2_musashi_kai2(attacker_fleet)  //
                                  or impl::is_musashi_kai2_yamato_kai2(attacker_fleet)
                               ? 1.1
                               : 1.0;

    const auto radar = impl::has_15m_duplex_rangefinder(attacker) ? 1.1 : 1.0;

    const auto equipment = impl::equipment_modifier(attacker);

    return base * combination * radar * equipment;
}

/// @brief 第一戦隊、突撃！主砲、全力斉射ッ！の3撃目の補正値を返す.
auto special_yamato_2_ships_3rd_attack(const kcv::battlelog& data) -> kcv::number {
    const auto& attacker_fleet = kcv::get_attacker_fleet(data);
    const auto& attacker       = kcv::get_attacker(data);

    const auto base = 1.55;

    const auto combination = impl::is_musashi_kai2_yamato_kai2_heavy(attacker_fleet)  //
                               ? 1.25
                               : impl::is_yamato_kai2_musashi_kai2(attacker_fleet)             //
                                         or impl::is_musashi_kai2_yamato_kai2(attacker_fleet)  //
                                     ? 1.2
                                     : 1.0;

    const auto radar = impl::has_15m_duplex_rangefinder(attacker) ? 1.1 : 1.0;

    const auto equipment = impl::equipment_modifier(attacker);

    return base * combination * radar * equipment;
}

}  // namespace impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::special_yamato_2_ships(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    namespace impl = kcv::modifiers::impl;

    // if (ctx.既存補正をoff) { return ctx.置換; }

    switch (data.attack_order) {
        case 0:
            return impl::special_yamato_2_ships_1st_attack(data);

        case 1:
            return impl::special_yamato_2_ships_2nd_attack(data);

        case 2:
            return impl::special_yamato_2_ships_3rd_attack(data);
    }

    return 1;
}
