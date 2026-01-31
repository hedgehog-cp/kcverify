#ifndef KCV_DOMAIN_VERIFICATION_ENTITY_ADAPTER_FROM_EOEN_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_ENTITY_ADAPTER_FROM_EOEN_HPP_INCLUDED

// std
#include <optional>
#include <ranges>
#include <vector>

// kcv
#include "kcv/domain/verification/entity/air_base.hpp"
#include "kcv/domain/verification/entity/air_base_squadron.hpp"
#include "kcv/domain/verification/entity/fleet.hpp"
#include "kcv/domain/verification/entity/fleet_data.hpp"
#include "kcv/domain/verification/entity/map_data.hpp"
#include "kcv/domain/verification/entity/ship.hpp"
#include "kcv/domain/verification/entity/slot.hpp"
#include "kcv/external/eoen/database/sortie/sortie_air_base_squadron.hpp"
#include "kcv/external/eoen/database/sortie/sortie_equipment.hpp"
#include "kcv/external/eoen/database/sortie/sortie_equipment_slot.hpp"
#include "kcv/external/eoen/database/sortie/sortie_fleet.hpp"
#include "kcv/external/eoen/database/sortie/sortie_fleet_data.hpp"
#include "kcv/external/eoen/database/sortie/sortie_map_data.hpp"
#include "kcv/external/eoen/database/sortie/sortie_ship.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_ship.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcv/external/kcsapi/extensions/utility.hpp"
#include "kcv/external/kcsapi/types/api_kyouka.hpp"
#include "kcv/external/kcsapi/types/api_minmax.hpp"

namespace kcv {

inline auto equipment_from_eoen(
    const kcv::eoen::database::sortie::sortie_equipment& src,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::equipment {
    const auto& mst = kcv::find_mst(api_mst_slotitem, src.id);
    return kcv::equipment{
        mst,
        src.level,
        src.aircraft_level,
    };
}

inline auto slot_from_eoen(
    const kcv::eoen::database::sortie::sortie_equipment_slot& src,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::slot {
    return kcv::slot{
        src.aircraft_current,
        src.aircraft_max,
        src.equipment.transform([&api_mst_slotitem](const auto& e) -> kcv::equipment {
            return kcv::equipment_from_eoen(e, api_mst_slotitem);
        }),
    };
}

inline auto ship_from_eoen(
    const kcv::eoen::database::sortie::sortie_ship& src,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::ship {
    const auto& mst = kcv::find_mst(api_mst_ship, src.id);
    /// @todo: value_orで0にフォールバックするのが正しいのか検討する.
    return kcv::ship{
        mst,
        kcv::base_id(api_mst_ship, mst),
        kcv::nationality(mst),
        src.equipment_slots  //
            | std::ranges::views::transform([&api_mst_slotitem](const auto& e) -> kcv::slot {
                  return kcv::slot_from_eoen(e, api_mst_slotitem);
              })
            | std::ranges::to<std::vector>(),
        src.expansion_slot.transform([&api_mst_slotitem](const auto& e) -> kcv::slot {
            return kcv::slot_from_eoen(e, api_mst_slotitem);
        }),
        src.level,
        src.condition,
        src.ammo,
        src.kyouka,
        kcv::get_maxhp(mst, std::get<kcv::kcsapi::idx_kyouka::taik>(src.kyouka), src.level),
        src.hp,
        src.firepower.value_or(0),
        src.torpedo.value_or(0),
        src.armor.value_or(0),
        src.speed,
        src.asw.value_or(0),
    };
}

inline auto air_base_squadron_from_eoen(
    const kcv::eoen::database::sortie::sortie_air_base_squadron& src,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::air_base_squadron {
    return kcv::air_base_squadron{
        src.aircraft_current,
        src.state,
        src.condition,
        kcv::slot_from_eoen(src.equipment_slot, api_mst_slotitem),
    };
}

inline auto air_base_from_eoen(
    const kcv::eoen::database::sortie::sortie_air_base& src,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::air_base {
    return kcv::air_base{
        src.name,
        src.map_area_id,
        src.air_corps_id,
        src.action_kind,
        src.base_distance,
        src.bonus_distance,
        src.squadrons  //
            | std::ranges::views::transform([&api_mst_slotitem](const auto& e) -> kcv::air_base_squadron {
                  return kcv::air_base_squadron_from_eoen(e, api_mst_slotitem);
              })
            | std::ranges::to<std::vector>(),
    };
}

inline auto map_data_from_eoen(const kcv::eoen::database::sortie::sortie_map_data& src) -> kcv::map_data {
    return kcv::map_data{
        src.required_defeat_count,
        src.map_hp_current,
        src.map_hp_max,
    };
}

inline auto fleet_from_eoen(
    const kcv::eoen::database::sortie::sortie_fleet& src,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::fleet {
    return kcv::fleet{
        src.name,
        src.ships  //
            | std::ranges::views::transform([&api_mst_ship, &api_mst_slotitem](const auto& e) -> kcv::ship {
                  return kcv::ship_from_eoen(e, api_mst_ship, api_mst_slotitem);
              })
            | std::ranges::to<std::vector>(),
    };
}

inline auto fleet_data_from_eoen(
    const kcv::eoen::database::sortie::sortie_fleet_data& src,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::fleet_data {
    return kcv::fleet_data{
        src.fleet_id,
        src.node_support_fleet_id,
        src.boss_support_fleet_id,
        src.combined_flag,
        src.fleets  //
            | std::ranges::views::transform([&](const auto& e) -> std::optional<kcv::fleet> {
                  return e.transform([&api_mst_ship, &api_mst_slotitem](const auto& e) -> kcv::fleet {
                      return kcv::fleet_from_eoen(e, api_mst_ship, api_mst_slotitem);
                  });
              })
            | std::ranges::to<std::vector>(),
        src.air_bases  //
            | std::ranges::views::transform([&api_mst_slotitem](const auto& e) -> kcv::air_base {
                  return kcv::air_base_from_eoen(e, api_mst_slotitem);
              })
            | std::ranges::to<std::vector>(),
    };
}

}  // namespace kcv

#endif  // KCV_DOMAIN_VERIFICATION_ENTITY_ADAPTER_FROM_EOEN_HPP_INCLUDED
