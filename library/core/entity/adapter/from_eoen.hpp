#ifndef KCVERIFY_CORE_ENTITY_ADAPTER_FROM_EOEN_HPP_INCLUDED
#define KCVERIFY_CORE_ENTITY_ADAPTER_FROM_EOEN_HPP_INCLUDED

#include "core/entity/air_base.hpp"
#include "core/entity/air_base_squadron.hpp"
#include "core/entity/fleet.hpp"
#include "core/entity/fleet_data.hpp"
#include "core/entity/map_data.hpp"
#include "core/entity/ship.hpp"
#include "core/entity/slot.hpp"
#include "models/eoen/database/sortie/sortie_air_base_squadron.hpp"
#include "models/eoen/database/sortie/sortie_equipment.hpp"
#include "models/eoen/database/sortie/sortie_equipment_slot.hpp"
#include "models/eoen/database/sortie/sortie_fleet.hpp"
#include "models/eoen/database/sortie/sortie_fleet_data.hpp"
#include "models/eoen/database/sortie/sortie_map_data.hpp"
#include "models/eoen/database/sortie/sortie_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"

namespace kcv {

auto equipment_from_eoen(
    const kcv::eoen::database::sortie::sortie_equipment& src,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::equipment;

auto slot_from_eoen(
    const kcv::eoen::database::sortie::sortie_equipment_slot& src,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::slot;

auto ship_from_eoen(
    const kcv::eoen::database::sortie::sortie_ship& src,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::ship;

auto air_base_squadron_from_eoen(
    const kcv::eoen::database::sortie::sortie_air_base_squadron& src,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::air_base_squadron;

auto air_base_from_eoen(
    const kcv::eoen::database::sortie::sortie_air_base& src,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::air_base;

auto map_data_from_eoen(const kcv::eoen::database::sortie::sortie_map_data& src) -> kcv::map_data;

auto fleet_from_eoen(
    const kcv::eoen::database::sortie::sortie_fleet& src,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::fleet;

auto fleet_data_from_eoen(
    const kcv::eoen::database::sortie::sortie_fleet_data& src,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::fleet_data;

}  // namespace kcv

#endif  // KCVERIFY_CORE_ENTITY_ADAPTER_FROM_EOEN_HPP_INCLUDED
