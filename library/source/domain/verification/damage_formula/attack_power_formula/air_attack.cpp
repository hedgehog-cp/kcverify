#include "kcv/core/constants/ship_attributes.hpp"
#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"

// -----------------------------------------------------------------------------
// 攻撃力式のうち砲撃戦.航空攻撃補正の実装をここに分離する.
// -----------------------------------------------------------------------------

// kcv
#include "kcv/core/context_data.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"
#include "kcv/domain/verification/entity/equipment.hpp"
#include "kcv/domain/verification/entity/ship.hpp"
#include "kcv/domain/verification/entity/slot.hpp"
#include "kcv/domain/verification/logic/logic.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcv/external/kcsapi/types/enum/category.hpp"
#include "kcv/external/kcsapi/types/enum/stype.hpp"

namespace kcv::modifiers {
namespace {
namespace impl {

/// @brief 対象の機体であるかを検証する.
bool is_plane(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (std::get<kcv::kcsapi::category>(mst.api_type)) {
        case kcv::kcsapi::category::carrier_based_bomber:
        case kcv::kcsapi::category::carrier_based_torpedo:
            return true;

        default:
            return false;
    }
}

/// @brief 搭載数>0である機体を搭載しているかを検証する.
bool has_available_plane(const kcv::ship& attacker) {
    for (const auto& slot : attacker.slots() | kcv::ranges::views::with_equipment) {
        if (slot.aircraft_current() > 0 and impl::is_plane(slot.equipment()->mst())) {
            return true;
        }
    }

    return false;
}

/// @brief 攻撃が砲撃戦の航空攻撃であるかを検証する.
bool is_air_attack(const kcv::battlelog& data) {
    if (kcv::is_submarine(kcv::get_defender(data).mst())) {
        return false;
    }

    const auto& attacker = kcv::get_attacker(data);

    switch (attacker.mst().api_stype) {
        case kcv::kcsapi::stype::cvl:
        case kcv::kcsapi::stype::cv:
        case kcv::kcsapi::stype::cvb:
            return true;

        case kcv::kcsapi::stype::ao:
            return impl::has_available_plane(attacker);

        default:
            return false;
    }
}

}  // namespace impl
}  // namespace
}  // namespace kcv::modifiers

// 長いのでエイリアス.
namespace mod = kcv::modifiers;

auto mod::air_attack(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::air_attack {
    namespace impl = kcv::modifiers::impl;

    // if (ctx.既存補正をoff) { return ctx.置換; }

    switch (data.phase) {
        case kcv::phase::sp_midnight:
        case kcv::phase::opening_taisen:
        case kcv::phase::opening_atack:
            return kcv::functions::air_attack{.is_enabled = false};

        case kcv::phase::hougeki:
            return kcv::functions::air_attack{.is_enabled = impl::is_air_attack(data)};

        case kcv::phase::raigeki:
        case kcv::phase::friendly:
        case kcv::phase::midnight:
            return kcv::functions::air_attack{.is_enabled = false};
    }

    return kcv::functions::air_attack::identity();
}