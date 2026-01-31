#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"

// -----------------------------------------------------------------------------
// 攻撃力式のうち基本攻撃力の実装をここに分離する.
// -----------------------------------------------------------------------------

// std
#include <cmath>
#include <string_view>

// kcv
#include "kcv/core/constants/equipment.hpp"
#include "kcv/core/constants/equipment_attributes.hpp"
#include "kcv/core/constants/ship.hpp"
#include "kcv/core/constants/ship_attributes.hpp"
#include "kcv/core/context_data.hpp"
#include "kcv/core/numeric/interval.hpp"
#include "kcv/core/numeric/interval/basic_interval.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/damage_formula/bonuses/equipment_bonus.hpp"
#include "kcv/domain/verification/entity/equipment.hpp"
#include "kcv/domain/verification/entity/ship.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcv/external/kcsapi/extensions/utility.hpp"
#include "kcv/external/kcsapi/types/enum/category.hpp"
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"
#include "kcv/external/kcsapi/types/enum/fleet_flag.hpp"
#include "kcv/external/kcsapi/types/enum/stype.hpp"
#include "kcv/std_ext/exception.hpp"

// 各補正の実装詳細は `*_impl` 名前空間に包んで実装し, namespace impl = ...; とともに使う.
// namespace kcv::modifiers { namespace { namespace modifier_name_impl { ... } }}
// auto f() { namespace impl = kcv::modifiers::modifier_name_impl; impl::foo(); }

/// @brief 長いのでalias. 関数のシグネチャが改行されちゃうもん...
namespace mod = kcv::modifiers;

namespace kcv::modifiers {
namespace {
namespace impl {

/// @brief 開幕夜戦の基本攻撃力を返す. 払暁戦マスにおける開幕夜戦を含む.
auto sp_midnight_attack_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief 砲撃戦の基本攻撃力を返す.
auto hougeki_attack_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief 対潜の基本攻撃力を返す.
auto asw_attack_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief 雷撃の基本攻撃力を返す. 雷撃戦に限らないため, 雷撃と表現する.
auto torpedo_attack_power(const kcv::battlelog& data) -> kcv::number;

/// @brief 友軍攻撃の基本攻撃力を返す.
auto friendly_attack_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

/// @brief 夜戦の基本攻撃力を返す.
auto midnight_attack_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number;

}  // namespace impl
}  // namespace
}  // namespace kcv::modifiers

auto mod::base_attack_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    namespace impl = kcv::modifiers::impl;

    switch (data.phase) {
        case kcv::phase::sp_midnight:
            return impl::sp_midnight_attack_power(ctx, data);

        case kcv::phase::opening_taisen:
            return impl::asw_attack_power(ctx, data);

        case kcv::phase::opening_atack:
            return impl::torpedo_attack_power(data);

        case kcv::phase::hougeki:
            return impl::hougeki_attack_power(ctx, data);

        case kcv::phase::raigeki:
            return impl::torpedo_attack_power(data);

        case kcv::phase::friendly:
            return impl::friendly_attack_power(ctx, data);

        case kcv::phase::midnight:
            return impl::midnight_attack_power(ctx, data);
    }

    return kcv::number{};
}

namespace kcv::modifiers {
namespace {
namespace impl {

auto hougeki_attack_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    if (kcv::is_submarine(kcv::get_defender(data).mst())) {
        return asw_attack_power(ctx, data);
    }

    throw kcv::exception{"not impl"};
}

auto asw_base_power(const kcv::battlelog& data) -> kcv::number {
    constexpr int depth_charge = 3 + 10;
    constexpr int air_attack   = 3 + 5;
    constexpr int not_asw      = 0;

    const auto& attacker = kcv::get_attacker(data);

    constexpr auto has_some_planes = [](const kcv::ship& attacker) static -> bool {
        static constexpr auto planes = {
            kcv::kcsapi::category::carrier_based_bomber,
            kcv::kcsapi::category::carrier_based_torpedo,
            kcv::kcsapi::category::seaplane_bomber,
            kcv::kcsapi::category::autogyro,
            kcv::kcsapi::category::as_patrol,
        };
        return kcv::has_equipment(attacker, planes);
    };
    switch (attacker.mst().api_id) {
        using kcv::literals::ship_literals::operator""_id;
        case "速吸"_id:
        case "神威改母"_id:
        case "第百一号輸送艦"_id:
        case "第百一号輸送艦改"_id:
        case "大泊"_id:
        case "大泊改"_id:
            return depth_charge;

        case "速吸改"_id:
        case "山汐丸"_id:
        case "山汐丸改"_id:
            return has_some_planes(attacker) ? air_attack : depth_charge;

        case "加賀改二護"_id:
            return air_attack;
    }

    using std::literals::string_view_literals::operator""sv;
    if (attacker.mst().api_name.starts_with("宗谷"sv)) {
        return depth_charge;
    }
    if (attacker.mst().api_name.starts_with("戦艦レ級"sv)) {
        return depth_charge;
    }

    switch (attacker.mst().api_stype) {
        case kcv::kcsapi::stype::de:
        case kcv::kcsapi::stype::dd:
        case kcv::kcsapi::stype::cl:
        case kcv::kcsapi::stype::clt:
        case kcv::kcsapi::stype::ct:
            return depth_charge;

        case kcv::kcsapi::stype::cav:
        case kcv::kcsapi::stype::cvl:
        case kcv::kcsapi::stype::bbv:
        case kcv::kcsapi::stype::av:
        case kcv::kcsapi::stype::lha:
            return air_attack;

        default:
            break;
    }

    return not_asw;
}

auto total_equipment_asw(const kcv::ship& attacker) -> kcv::number {
    auto total = kcv::number{0};

    for (const auto& slot : attacker.slots()) {
        if (const auto& equipment = slot.equipment(); equipment.has_value()) {
            total += equipment->mst().api_tais;
        }
    }

    return total;
}

auto asw_equipment(const kcv::kcsapi::api_mst_slotitem_value_t& mst) -> kcv::number {
    switch (std::get<kcv::kcsapi::category>(mst.api_type)) {
        case kcv::kcsapi::category::carrier_based_bomber:
        case kcv::kcsapi::category::carrier_based_torpedo:
        case kcv::kcsapi::category::seaplane_bomber:
        case kcv::kcsapi::category::sonar:
        case kcv::kcsapi::category::depth_charge:
        case kcv::kcsapi::category::autogyro:
        case kcv::kcsapi::category::as_patrol:
        case kcv::kcsapi::category::sonar_large:
            return mst.api_tais;

        default:
            return 0;
    }
}

auto total_asw_equipment(const kcv::ship& attacker) -> kcv::number {
    auto total = kcv::number{0};

    for (const auto& slot : attacker.slots()) {
        if (slot.equipment().has_value()) {
            total += asw_equipment(slot.equipment()->mst());
        }
    }

    return total;
}

auto asw_improvement_bonus(const kcv::equipment& equipment) -> kcv::number {
    switch (std::get<kcv::kcsapi::category>(equipment.mst().api_type)) {
        case kcv::kcsapi::category::carrier_based_bomber:
        case kcv::kcsapi::category::carrier_based_torpedo:
            return 0.2 * equipment.level();

        case kcv::kcsapi::category::sonar:
        case kcv::kcsapi::category::depth_charge:
            return std::sqrt(equipment.level());

        case kcv::kcsapi::category::autogyro:
            return equipment.mst().api_tais > 10  //
                     ? 0.3 * equipment.level()
                     : 0.2 * equipment.level();

        case kcv::kcsapi::category::as_patrol:
            return 0.3 * equipment.level();

        case kcv::kcsapi::category::sonar_large:
            return std::sqrt(equipment.level());

        default:
            return 0;
    }
}

auto total_asw_improvement_bonus(const kcv::ship& attacker) -> kcv::number {
    auto total = kcv::number{0};

    for (const auto& slot : attacker.slots()) {
        if (slot.equipment().has_value()) {
            total += asw_improvement_bonus(*slot.equipment());
        }
    }

    return total;
}

auto asw_attack_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    const auto& attacker       = kcv::get_attacker(data);
    const auto base_value      = asw_base_power(data);
    const auto asw             = attacker.asw();
    const auto equipment_asw   = total_equipment_asw(attacker);
    const auto asw_equipment   = total_asw_equipment(attacker);
    const auto equipment_bonus = kcv::total_equipment_bonus(attacker, ctx.fit_bonuses()).tais;
    const auto naked_value     = data.attacker_side == kcv::kcsapi::fleet_flag::player  //
                                   ? asw - equipment_asw - equipment_bonus
                                   : 0;  // 不明.
    const auto asw_improvement = total_asw_improvement_bonus(attacker);

    return base_value + 2 * kcv::sqrt(naked_value) + 1.5 * (asw_equipment + equipment_bonus) + asw_improvement;
}

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

auto total_torpedo_improvement_bonus(const kcv::ship& attacker) -> kcv::number {
    auto total = kcv::number{0};

    for (const auto& slot : attacker.slots()) {
        if (slot.equipment().has_value()) {
            total += torpedo_improvement_bonus(*slot.equipment());
        }
    }

    return total;
}

auto torpedo_attack_power(const kcv::battlelog& data) -> kcv::number {
    const auto& attacker = kcv::get_attacker(data);

    const auto base_value = 5;
    const auto torpedo    = attacker.torpedo();
    // TODO: 熟練甲板要員+航空整備員.ボーナス.雷装
    const auto improvement = total_torpedo_improvement_bonus(attacker);
    // TODO: 連合艦隊補正.

    return base_value + torpedo + improvement;
}

// 6   = 夜戦.砲雷攻撃.対水上
// 9   = 夜戦.夜間航空攻撃.対水上

/// @brief 夜間航空攻撃であるかを検証する.
bool is_night_air_attack(const kcv::battlelog& data) {
    const auto& attacker = kcv::get_attacker(data);

    // 夜間作戦空母による攻撃.
    if (kcv::is_night_operation_aircraft_carrier(attacker.mst())) {
        // 夜間作戦空母かつ夜間砲撃可能空母は存在しない.
        // 攻撃したことは確定しているため, 残存している夜間機がある.
        return true;
    }

    // 夜間作戦航空要員を装備している かつ 残存している夜間機がある.
    if (kcv::has_equipment(attacker, &kcv::is_night_operation_aviation_personnel)) {
        for (const auto& slot : attacker.slots()) {
            if (slot.equipment().has_value()) {
                if (slot.aircraft_current() > 0 and kcv::is_night_plane(slot.equipment()->mst())) {
                    return true;
                }
            }
        }
    }

    return false;
}

/// @brief Ark Royalによるswordfish攻撃であるかを検証する.
bool is_ark_royal_with_swordfish_attack(const kcv::battlelog& data) {
    const auto& attacker = kcv::get_attacker(data);

    // 枯れていてもいいんだっけ?
    return kcv::is_ark_royal(attacker.mst()) and kcv::has_equipment(attacker, &kcv::is_cb_swordfish);
}

/// @brief 水上艦に対する夜間航空攻撃の基本攻撃力を返す.
auto night_air_attack_for_surface(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    throw kcv::exception{"not impl"};
}

/// @brief 陸上型に対する夜間航空攻撃の基本攻撃力を返す.
auto night_air_attack_for_instllation(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    throw kcv::exception{"not impl"};
}

/// @brief Ark Royalによるswordfish攻撃の基本攻撃力を返す.
auto ark_royal_with_swordfish_attack(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    throw kcv::exception{"not impl"};
}

/// @brief 夜間触接機補正を返す.
auto night_touch_plane(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    const auto touch_plane_id = kcv::get_attacker_touch_plane(data);
    if (touch_plane_id == kcv::kcsapi::invalid_equipment_id) {
        return 0;
    }

    const auto& touch_plane = kcv::find_mst(ctx.api_mst_slotitem(), touch_plane_id);
    switch (touch_plane.api_houm) {
        case 0:
            return 0;

        case 1:
            return 5;

        case 2:
            return 7;

        case 3:
            return 9;

        default:
            return 0;
    }
}

auto night_improvement_bonus(const kcv::equipment& equipment) -> kcv::number {
    constexpr auto secondary_gun_impl = [](const kcv::equipment& equipment) static noexcept -> kcv::number {
        switch (equipment.mst().api_id) {
            using kcv::literals::equipment_literals::operator""_id;
            case "12.7cm連装高角砲"_id:
                return 0.2 * equipment.level();

            case "15.2cm単装砲"_id:
                return std::sqrt(equipment.level());

            case "15.5cm三連装副砲"_id:
                return 0.3 * equipment.level();

            case "8cm高角砲"_id:
            case "10cm連装高角砲(砲架)"_id:
                return 0.2 * equipment.level();

            case "15cm連装副砲"_id:
                return 0.3 * equipment.level();

            case "12.7cm高角砲+高射装置"_id:
                return 0.2 * equipment.level();

            case "OTO 152mm三連装速射砲"_id:
            case "90mm単装高角砲"_id:
                return std::sqrt(equipment.level());

            case "10.5cm連装砲"_id:
            case "5inch連装砲 Mk.28 mod.2"_id:
            case "8cm高角砲改+増設機銃"_id:
                return 0.2 * equipment.level();

            case "15.5cm三連装副砲改"_id:
            case "15.2cm三連装砲"_id:
                return 0.3 * equipment.level();

            case "10cm連装高角砲改+増設機銃"_id:
            case "5inch 単装高角砲群"_id:
            case "65mm/64 単装速射砲改"_id:
            case "10cm連装高角砲群 集中配備"_id:
                return 0.2 * equipment.level();

            case "5inch連装砲(副砲配置) 集中配備"_id:
                return 0.3 * equipment.level();

            case "12cm単装高角砲+25mm機銃増備"_id:
                return 0.2 * equipment.level();

            default:
                return 0;
        }
    };

    switch (std::get<kcv::kcsapi::category>(equipment.mst().api_type)) {
        case kcv::kcsapi::category::main_gun_small:
        case kcv::kcsapi::category::main_gun_medium:
        case kcv::kcsapi::category::main_gun_large:
            return std::sqrt(equipment.level());

        case kcv::kcsapi::category::secondary_gun:
            return secondary_gun_impl(equipment);

        case kcv::kcsapi::category::torpedo:
        case kcv::kcsapi::category::aa_shell:
        case kcv::kcsapi::category::ap_shell:
        case kcv::kcsapi::category::midget_submarine:
        case kcv::kcsapi::category::landing_craft:
        case kcv::kcsapi::category::searchlight:
            return std::sqrt(equipment.level());

        case kcv::kcsapi::category::submarine_torpedo:
            return 0.2 * equipment.level();

        case kcv::kcsapi::category::command_facility:
        case kcv::kcsapi::category::aviation_personnel:
        case kcv::kcsapi::category::aa_director:
        case kcv::kcsapi::category::rocket:
        case kcv::kcsapi::category::surface_ship_personnel:
        case kcv::kcsapi::category::searchlight_large:
        case kcv::kcsapi::category::special_amphibious_tank:
        case kcv::kcsapi::category::army_infantry:
        case kcv::kcsapi::category::surface_ship_equipment:
            return std::sqrt(equipment.level());

        default:
            return 0;
    }
}

auto total_night_improvement_bonus(const kcv::ship& attacker) -> kcv::number {
    auto total = kcv::number{0};

    for (const auto& slot : attacker.slots()) {
        if (slot.equipment().has_value()) {
            total += night_improvement_bonus(*slot.equipment());
        }
    }

    return total;
}

/// @brief 水上艦に対する汎用的な夜間攻撃の基本攻撃力を返す.
/// 対地でなく, 夜間航空攻撃でなく, Ark Royal with swordfishでない夜間攻撃.
auto night_attack_power_for_surface(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    const auto& attacker = kcv::get_attacker(data);

    const auto firepower         = attacker.firepower();
    const auto torpedo           = attacker.torpedo();
    const auto night_touch_plane = impl::night_touch_plane(ctx, data);
    // 熟練甲板要員+航空整備員.ボーナス.雷装.
    const auto improvement = total_night_improvement_bonus(attacker);

    // 攻撃艦.火力 + 攻撃艦.雷装 +  熟練甲板要員+航空整備員.ボーナス.雷装 + 夜間触接補正 + 装備改修補正;
    return firepower + torpedo + night_touch_plane + improvement;
}

/// @brief 陸上型に対する汎用的な夜間攻撃の基本攻撃力を返す.
auto night_attack_power_for_instllation(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    throw kcv::exception{"not impl"};
}

/// @brief 対潜を除く夜間攻撃の基本攻撃力を返す.
auto night_attack_power_non_asw(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    // 対陸上施設.
    if (kcv::is_installation(kcv::get_defender(data).mst())) {
        // 夜間航空攻撃.
        if (is_night_air_attack(data)) {
            return night_air_attack_for_instllation(ctx, data);
        }

        // 砲弾攻撃.
        return night_attack_power_for_instllation(ctx, data);
    }

    // 夜間航空攻撃.
    if (is_night_air_attack(data)) {
        return night_air_attack_for_surface(ctx, data);
    }

    // Ark Royal with swordfish
    if (is_ark_royal_with_swordfish_attack(data)) {
        return ark_royal_with_swordfish_attack(ctx, data);
    }

    // 砲雷攻撃.
    return night_attack_power_for_surface(ctx, data);
}

auto sp_midnight_attack_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    if (kcv::is_submarine(kcv::get_defender(data).mst())) {
        return asw_attack_power(ctx, data);
    }

    return night_attack_power_non_asw(ctx, data);
}

auto friendly_attack_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    if (kcv::is_submarine(kcv::get_defender(data).mst())) {
        // 終局阻止を除いて撃沈可能.
        return asw_attack_power(ctx, data);
    }

    return night_attack_power_non_asw(ctx, data);
}

auto midnight_attack_power(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    if (kcv::is_submarine(kcv::get_defender(data).mst())) {
        // 攻撃側が連合艦隊のとき撃沈可能.
        if (kcv::get_attacker_fleet_data(data).combined_flag() != 0) {
            return asw_attack_power(ctx, data);
        }

        // 基本攻撃力を逆算できないため, 任意の値をとれる.
        return kcv::number::whole();
    }

    return night_attack_power_non_asw(ctx, data);
}

}  // namespace impl
}  // namespace
}  // namespace kcv::modifiers
