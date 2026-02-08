#include "kcv/domain/verification/logic/logic.hpp"

// std
#include <algorithm>
#include <cassert>
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
#include "kcv/domain/verification/entity/slot.hpp"
#include "kcv/domain/verification/logic/logic.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcv/external/kcsapi/extensions/damage_state.hpp"
#include "kcv/external/kcsapi/extensions/utility.hpp"
#include "kcv/external/kcsapi/types/enum/category.hpp"
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"
#include "kcv/external/kcsapi/types/enum/fleet_flag.hpp"
#include "kcv/external/kcsapi/types/enum/icon.hpp"
#include "kcv/external/kcsapi/types/enum/stype.hpp"
#include "kcv/std_ext/exception.hpp"

namespace kcv {
namespace {
namespace impl {

//

}  // namespace impl
}  // namespace
}  // namespace kcv

int kcv::classify_asw_operation(const kcv::battlelog& data) {
    constexpr int depth_charge = 3 + 10;
    constexpr int air_attack   = 3 + 5;
    constexpr int not_asw      = 0;

    if (not kcv::is_submarine(kcv::get_defender(data).mst())) {
        return not_asw;
    }

    constexpr auto has_available_asw_plane = [](const kcv::ship& attacker) static noexcept -> bool {
        static constexpr auto planes = {
            kcv::kcsapi::category::carrier_based_bomber,
            kcv::kcsapi::category::carrier_based_torpedo,
            kcv::kcsapi::category::seaplane_bomber,
            kcv::kcsapi::category::autogyro,
            kcv::kcsapi::category::as_patrol,
        };
        return kcv::has_equipment(attacker, planes);
    };

    const auto& attacker = kcv::get_attacker(data);

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
            return has_available_asw_plane(attacker) ? air_attack : depth_charge;

        case "加賀改二護"_id:
            return air_attack;

        default:
            break;
    }

    using std::literals::string_view_literals::operator""sv;
    if (attacker.mst().api_name.starts_with("宗谷"sv)) {
        return depth_charge;
    }
    // 誤判定.
    // if (attacker.mst().api_name.starts_with("戦艦レ級"sv)) {
    //     return depth_charge;
    // }

    switch (attacker.mst().api_stype) {
        case kcv::kcsapi::stype::de:
        case kcv::kcsapi::stype::dd:
        case kcv::kcsapi::stype::cl:
        case kcv::kcsapi::stype::clt:
            return depth_charge;

        case kcv::kcsapi::stype::cav:
        case kcv::kcsapi::stype::cvl:
        case kcv::kcsapi::stype::bbv:
        case kcv::kcsapi::stype::av:
        case kcv::kcsapi::stype::lha:
            return air_attack;

        case kcv::kcsapi::stype::ct:
            return depth_charge;

        default:
            break;
    }

    return not_asw;
}

namespace kcv {
namespace {
namespace impl {

/// @brief 夜間作戦可能な空母であるかを検証する.
/// 艦船の特性および夜間作戦航空要員の装備条件のみを検証し, 損傷状態および夜間機数などは考慮しない.
bool can_night_operation_aircraft_carrier(const kcv::ship& attacker) {
    if (kcv::is_night_operation_aircraft_carrier(attacker.mst())) {
        return true;
    }

    // 夜間作戦航空要員を例えばGotland andraや山汐丸改に搭載しても夜間航空攻撃をしない.
    // 艦種を航空母艦に限定する.
    return kcv::has_equipment(attacker, &kcv::is_night_operation_aviation_personnel)
       and kcv::is_aircraft_carrier(attacker.mst());
}

/// @brief 機数>0である夜間機を搭載しているかを検証する.
bool has_available_night_plane(const kcv::ship& attacker) {
    for (const auto& slot : attacker.slots() | kcv::ranges::views::with_equipment) {
        if (slot.aircraft_current() > 0 and kcv::is_night_plane(slot.equipment()->mst())) {
            return true;
        }
    }

    return false;
}

/// @brief 夜間航空攻撃であるかを検証する.
bool is_night_air_attack(const kcv::battlelog& data) {
    // Gambier Bay Mk.IIは夜間作戦航空要員を搭載していても, 潜水艦を優先して爆雷攻撃する.
    if (kcv::is_submarine(kcv::get_defender(data).mst())) {
        return false;
    }

    const auto& attacker = kcv::get_attacker(data);

    // 夜間作戦可能な空母による攻撃である.
    if (impl::can_night_operation_aircraft_carrier(attacker)) {
        // 装甲空母または損傷が小破以下である.
        if (attacker.mst().api_stype == kcv::kcsapi::stype::cvb
            or kcv::to_damage_state(attacker.hp(), attacker.maxhp()) <= kcv::damage_state::light) {
            // 夜間機が残存している.
            if (impl::has_available_night_plane(attacker)) {
                return true;
            }
        }
    }

    return false;
}

}  // namespace impl
}  // namespace
}  // namespace kcv

bool kcv::is_night_air_attack(const kcv::battlelog& data) {
    namespace impl = kcv::impl;

    switch (data.phase) {
        case kcv::phase::sp_midnight:
            return impl::is_night_air_attack(data);

        case kcv::phase::opening_taisen:
        case kcv::phase::opening_atack:
        case kcv::phase::hougeki:
        case kcv::phase::raigeki:
            return false;

        case kcv::phase::friendly:
        case kcv::phase::midnight:
            return impl::is_night_air_attack(data);
    }
}
