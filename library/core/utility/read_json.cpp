#include "core/utility/read_json.hpp"

// std
#include <filesystem>
#include <string>
#include <utility>

// glz
#include <glaze/json.hpp>

// kcv
#include "extensions/exception.hpp"
#include "models/eoen/database/kancolle_api/api_files.hpp"
#include "models/eoen/database/sortie/sortie_air_base.hpp"
#include "models/eoen/database/sortie/sortie_air_base_squadron.hpp"
#include "models/eoen/database/sortie/sortie_equipment.hpp"
#include "models/eoen/database/sortie/sortie_equipment_slot.hpp"
#include "models/eoen/database/sortie/sortie_fleet.hpp"
#include "models/eoen/database/sortie/sortie_fleet_data.hpp"
#include "models/eoen/database/sortie/sortie_map_data.hpp"
#include "models/eoen/database/sortie/sortie_record.hpp"
#include "models/eoen/database/sortie/sortie_ship.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_data.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_value.hpp"
#include "models/kc3kai/mst_slotitem_bonus.hpp"
#include "models/kcsapi/api_get_member/ship_deck/response.hpp"
#include "models/kcsapi/api_req_battle_midnight/battle/response.hpp"
#include "models/kcsapi/api_req_map/next/response.hpp"
#include "models/kcsapi/api_req_map/start/request.hpp"
#include "models/kcsapi/api_req_map/start/response.hpp"
#include "models/kcsapi/api_req_sortie/battle/response.hpp"
#include "models/kcsapi/api_req_sortie/battleresult/response.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/svdata.hpp"

template <>
struct glz::meta<kcv::kc3kai::bonus_data> {
   public:
    using T = kcv::kc3kai::bonus_data;

   private:
    static constexpr void impl(T& dst, const std::optional<std::vector<std::string_view>>& src) {
        constexpr auto impl = [](std::string_view country) static -> kcv::kcsapi::nationality {
            if (country == "JP") return kcv::kcsapi::nationality::japanese;
            if (country == "DE") return kcv::kcsapi::nationality::german;
            if (country == "IT") return kcv::kcsapi::nationality::italian;
            if (country == "US") return kcv::kcsapi::nationality::american;
            if (country == "GB") return kcv::kcsapi::nationality::british;
            if (country == "FR") return kcv::kcsapi::nationality::french;
            if (country == "RU") return kcv::kcsapi::nationality::russian;
            if (country == "SE") return kcv::kcsapi::nationality::swedish;
            if (country == "AU") return kcv::kcsapi::nationality::australian;
            if (country == "NL") return kcv::kcsapi::nationality::dutch;
            return kcv::kcsapi::nationality::unknown;
        };
        if (src.has_value()) {
            dst.ship_country = std::vector<kcv::kcsapi::nationality>{};
            dst.ship_country->reserve(src->size());
            for (const auto& country : *src) {
                dst.ship_country->push_back(impl(country));
            }
        } else {
            dst.ship_country = std::nullopt;
        }
    }

   public:
    static constexpr auto value = object(
        // clang-format off

        "requiresAR",       &T::requires_anti_air_radar,
        "requiresSR",       &T::requires_surface_radar,
        "requiresAccR",     &T::requires_accuracy_radar,
        "shipClass",        &T::ship_class,
        "shipCountry",      glz::custom<
                                [](T& dst, const std::optional<std::vector<std::string_view>>& src) { impl(dst, src); },
                                &T::ship_country
                            >,
        "shipId",           &T::ship_id,
        "shipBase",         &T::ship_base,
        "shipType",         &T::ship_type,
        "requiresId",       &T::requires_id,
        "requiresIdLevel",  &T::requires_id_level,
        "requiresIdNum",    &T::requires_id_num,
        "requiresType",     &T::requires_type,
        "requiresTypeNum",  &T::requires_type_num,
        "level",            &T::level,
        "num",              &T::num,
        "bonus",            &T::bonus

        // clang-format on
    );
};

template <>
struct glz::meta<kcv::eoen::database::kancolle_api::api_files> {
    using T = kcv::eoen::database::kancolle_api::api_files;

    static constexpr auto value = object(
        // clang-format off

        "Id",             &T::id,
        "ApiFileType",    &T::api_file_type,
        "Name",           &T::name,
        "Content",        &T::content,
        "TimeStamp",      &T::time_stamp,
        "Version",        &T::version,
        "SortieRecordId", &T::sortie_record_id

        // clang-format on
    );
};

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_air_base> {
    using T = kcv::eoen::database::sortie::sortie_air_base;

    static constexpr auto value = object(
        // clang-format off

        "Name",          &T::name,
        "MapAreaId",     &T::map_area_id,
        "AirCorpsId",    &T::air_corps_id,
        "ActionKind",    &T::action_kind,
        "BaseDistance",  &T::base_distance,
        "BonusDistance", &T::bonus_distance,
        "Squadrons",     &T::squadrons

        // clang-format on

    );
};

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_air_base_squadron> {
    using T = kcv::eoen::database::sortie::sortie_air_base_squadron;

    static constexpr auto value = object(
        // clang-format off

        "AircraftCurrent", &T::aircraft_current,
        "State",           &T::state,
        "Condition",       &T::condition,
        "EquipmentSlot",   &T::equipment_slot

        // clang-format on
    );
};

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_equipment> {
    using T = kcv::eoen::database::sortie::sortie_equipment;

    static constexpr auto value = object(
        // clang-format off

        "Id",            &T::id,
        "Level",         &T::level,
        "AircraftLevel", &T::aircraft_level

        // clang-format on
    );
};

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_equipment_slot> {
    using T = kcv::eoen::database::sortie::sortie_equipment_slot;

    static constexpr auto value = object(
        // clang-format off

        "AircraftCurrent", &T::aircraft_current,
        "AircraftMax",     &T::aircraft_max,
        "Equipment",       &T::equipment

        // clang-format on
    );
};

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_fleet> {
    using T = kcv::eoen::database::sortie::sortie_fleet;

    static constexpr auto value = object(
        // clang-format off

        "Name",  &T::name,
        "Ships", &T::ships

        // clang-format on
    );
};

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_fleet_data> {
    using T = kcv::eoen::database::sortie::sortie_fleet_data;

    static constexpr auto value = object(
        // clang-format off

        "FleetId",            &T::fleet_id,
        "NodeSupportFleetId", &T::node_support_fleet_id,
        "BossSupportFleetId", &T::boss_support_fleet_id,
        "CombinedFlag",       &T::combined_flag,
        "Fleets",             &T::fleets,
        "AirBases",           &T::air_bases

        // clang-format on
    );
};

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_map_data> {
    using T = kcv::eoen::database::sortie::sortie_map_data;

    static constexpr auto value = object(
        // clang-format off
        
        "RequiredDefeatedCount", &T::required_defeat_count,
        "MapHPCurrent",          &T::map_hp_current,
        "MapHPMax",              &T::map_hp_max

        // clang-format on
    );
};

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_record> {
    using T = kcv::eoen::database::sortie::sortie_record;

    static constexpr auto value = object(
        // clang-format off

        "Id",                   &T::id,
        "Version",              &T::version,
        "World",                &T::world,
        "Map",                  &T::map,
        "ApiFiles",             &T::api_files,
        "FleetData",            &T::fleet_data,
        "FleetAfterSortieData", &T::fleet_after_sortie_data,
        "MapData",              &T::map_data,
        "CalculatedSortieCost", skip{}

        // clang-format on
    );
};

template <>
struct glz::meta<kcv::eoen::database::sortie::sortie_ship> {
    using T = kcv::eoen::database::sortie::sortie_ship;

    static constexpr auto value = object(
        // clang-format off
        
        "Id",                  &T::id,
        "DropId",              &T::drop_id,
        "Level",               &T::level,
        "Condition",           &T::condition,
        "Kyouka",              &T::kyouka,
        "Fuel",                &T::fuel,
        "Ammo",                &T::ammo,
        "Hp",                  &T::hp,
        "Armor",               &T::armor,
        "Evasion",             &T::evasion,
        "Aircraft",            &T::aircraft,
        "Range",               &T::range,
        "Speed",               &T::speed,
        "Firepower",           &T::firepower,
        "Torpedo",             &T::torpedo,
        "Aa",                  &T::aa,
        "Asw",                 &T::asw,
        "Search",              &T::search,
        "Luck",                &T::luck,
        "EquipmentSlots",      &T::equipment_slots,
        "ExpansionSlot",       &T::expansion_slot,
        "SpecialEffectItems",  &T::special_effect_items

        // clang-format on
    );
};

template <>
struct glz::meta<kcv::eoen::serialization::fit_bonus::fit_bonus_data> {
    using T = kcv::eoen::serialization::fit_bonus::fit_bonus_data;

    static constexpr auto value = object(
        // clang-format off

        "shipType",        &T::ship_type,
        "level",           &T::level,
        "num",             &T::num,
        "bonus",           &T::bonus,
        "shipX",           &T::ship_id,
        "bonusAR",         &T::bonus_if_anti_air_radar,
        "shipS",           &T::original_id,
        "requires",        &T::requires_id, 
        "requiresLevel",   &T::requires_level,
        "requiresNum",     &T::requires_num,
        "requiresType",    &T::requires_type,
        "requiresNumType", &T::requires_num_type,
        "shipClass",       &T::ship_class,
        "bonusSR",         &T::bonus_if_surface_radar,
        "shipNationality", &T::nationality,
        "bonusAccR",       &T::bonus_if_accuracy_radar

        // clang-format on
    );
};

template <>
struct glz::meta<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment> {
    using T = kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment;

    static constexpr auto value = object(
        // clang-format off

        "types",   &T::types,
        "ids",     &T::ids,
        "bonuses", &T::bonuses

        // clang-format on
    );
};

void kcv::read_json(auto& dst, const std::string& buffer) try {
    const auto error = glz::read_json(dst, buffer);
    if (error) {
        throw kcv::exception{glz::format_error(error, buffer)};
    }
} catch (const kcv::exception& e) {
    throw;
} catch (const std::exception& e) {
    std::throw_with_nested(kcv::make_exception_with_context("could not parse buffer."));
}

void kcv::read_json(auto& dst, const std::filesystem::path& fname) try {
    auto buffer = std::string{};
    buffer.resize_and_overwrite(
        std::filesystem::file_size(fname),
        [&fname](char* data, std::size_t size) -> std::size_t {
            std::ifstream{fname}.read(data, size);
            return size;
        }
    );
    kcv::read_json(dst, std::as_const(buffer));
} catch (const kcv::exception& e) {
    throw;
} catch (const std::exception& e) {
    // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2024/p2319r0.html
    // https://onihusube.hatenablog.com/#P2319R0-Prevent-path-presentation-problems
    // [[deprecated("P2319: std::filesystemm::string")]]
    const auto msg = std::format("could not read file. [file = {}].", fname.string());
    std::throw_with_nested(kcv::make_exception_with_context(std::move(msg)));
}

// clang-format off

// testで使う関数もここで明示的特殊化する
template void kcv::read_json(std::vector<kcv::kc3kai::bonus_value>&, const std::string&);
template void kcv::read_json(std::vector<kcv::kc3kai::bonus_value>&, const std::filesystem::path&);

template void kcv::read_json(std::vector<kcv::kc3kai::mst_slotitem_bonus>&, const std::string&);
template void kcv::read_json(std::vector<kcv::kc3kai::mst_slotitem_bonus>&, const std::filesystem::path&);

template void kcv::read_json(std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_value>&, const std::string&);
template void kcv::read_json(std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_value>&, const std::filesystem::path&);

template void kcv::read_json(std::vector<kcv::eoen::database::sortie::sortie_record>&, const std::string&);
template void kcv::read_json(std::vector<kcv::eoen::database::sortie::sortie_record>&, const std::filesystem::path&);

template void kcv::read_json(std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>&, const std::string&);
template void kcv::read_json(std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::api_req_map::start::request&, const std::string&);
template void kcv::read_json(kcv::kcsapi::api_req_map::start::request&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::api_mst_ship&, const std::string&);
template void kcv::read_json(kcv::kcsapi::api_mst_ship&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::api_mst_slotitem&, const std::string&);
template void kcv::read_json(kcv::kcsapi::api_mst_slotitem&, const std::filesystem::path&);

// clang-format on
