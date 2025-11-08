#include "core/entity/adapter/from_eoen.hpp"

// std
#include <optional>
#include <ranges>
#include <vector>

// kcv
#include "core/entity/air_base.hpp"
#include "core/entity/air_base_squadron.hpp"
#include "core/entity/equipment.hpp"
#include "core/entity/fleet.hpp"
#include "core/entity/fleet_data.hpp"
#include "core/entity/map_data.hpp"
#include "core/entity/ship.hpp"
#include "core/entity/slot.hpp"
#include "core/utility/kcsapi.hpp"
#include "models/kcsapi/types/api_minmax.hpp"

auto kcv::equipment_from_eoen(
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

auto kcv::slot_from_eoen(
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

auto kcv::ship_from_eoen(
    const kcv::eoen::database::sortie::sortie_ship& src,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::ship {
    const auto& mst = kcv::find_mst(api_mst_ship, src.id);
    return ship{
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
        std::get<kcv::kcsapi::idx_minmax::max>(mst.api_taik.value()),
        src.hp,
    };
}

auto kcv::air_base_squadron_from_eoen(
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

auto kcv::air_base_from_eoen(
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

auto kcv::map_data_from_eoen(const kcv::eoen::database::sortie::sortie_map_data& src) -> kcv::map_data {
    return kcv::map_data{
        src.required_defeat_count,
        src.map_hp_current,
        src.map_hp_max,
    };
}

auto kcv::fleet_from_eoen(
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

auto kcv::fleet_data_from_eoen(
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