#include "core/json/read_json.hpp"

// std
#include <filesystem>
#include <string>
#include <vector>

// kcv
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
#include "models/kcsapi/api_port/port/response.hpp"
#include "models/kcsapi/api_req_battle_midnight/battle/response.hpp"
#include "models/kcsapi/api_req_battle_midnight/sp_midnight/response.hpp"
#include "models/kcsapi/api_req_combined_battle/battle_water/response.hpp"
#include "models/kcsapi/api_req_combined_battle/battleresult/response.hpp"
#include "models/kcsapi/api_req_combined_battle/each_battle_water/response.hpp"
#include "models/kcsapi/api_req_combined_battle/ec_battle/response.hpp"
#include "models/kcsapi/api_req_combined_battle/ec_midnight_battle/response.hpp"
#include "models/kcsapi/api_req_combined_battle/ld_airbattle/response.hpp"
#include "models/kcsapi/api_req_combined_battle/midnight_battle/response.hpp"
#include "models/kcsapi/api_req_map/next/response.hpp"
#include "models/kcsapi/api_req_map/start/request.hpp"
#include "models/kcsapi/api_req_map/start/response.hpp"
#include "models/kcsapi/api_req_map/start_air_base/request.hpp"
#include "models/kcsapi/api_req_map/start_air_base/response.hpp"
#include "models/kcsapi/api_req_sortie/battle/response.hpp"
#include "models/kcsapi/api_req_sortie/battleresult/response.hpp"
#include "models/kcsapi/api_req_sortie/goback_port/response.hpp"
#include "models/kcsapi/api_req_sortie/ld_airbattle/response.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/svdata.hpp"

// glz::meta
#include "core/json/glz/meta.hpp"

// impl
#include "core/json/read_json.ipp"

// clang-format off

// MARK: eoen

template void kcv::read_json(std::vector<kcv::eoen::database::sortie::sortie_record>&, const std::string&);
template void kcv::read_json(std::vector<kcv::eoen::database::sortie::sortie_record>&, const std::filesystem::path&);

template void kcv::read_json(std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_value>&, const std::string&);
template void kcv::read_json(std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_value>&, const std::filesystem::path&);

template void kcv::read_json(std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>&, const std::string&);
template void kcv::read_json(std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>&, const std::filesystem::path&);

// MARK: kc3kai

template void kcv::read_json(std::vector<kcv::kc3kai::bonus_value>&, const std::string&);
template void kcv::read_json(std::vector<kcv::kc3kai::bonus_value>&, const std::filesystem::path&);

template void kcv::read_json(std::vector<kcv::kc3kai::mst_slotitem_bonus>&, const std::string&);
template void kcv::read_json(std::vector<kcv::kc3kai::mst_slotitem_bonus>&, const std::filesystem::path&);

// MARK: kcsapi

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_port::port::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_port::port::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::sp_midnight::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::sp_midnight::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::battle_water::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::battle_water::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::battleresult::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::battleresult::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::each_battle_water::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::each_battle_water::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ec_battle::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ec_battle::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ec_midnight_battle::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ec_midnight_battle::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ld_airbattle::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ld_airbattle::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::midnight_battle::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::midnight_battle::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::api_req_map::start::request&, const std::string&);
template void kcv::read_json(kcv::kcsapi::api_req_map::start::request&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::api_req_map::start_air_base::request&, const std::string&);
template void kcv::read_json(kcv::kcsapi::api_req_map::start_air_base::request&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start_air_base::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start_air_base::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::goback_port::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::goback_port::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::ld_airbattle::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::ld_airbattle::response>&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::api_mst_ship&, const std::string&);
template void kcv::read_json(kcv::kcsapi::api_mst_ship&, const std::filesystem::path&);

template void kcv::read_json(kcv::kcsapi::api_mst_slotitem&, const std::string&);
template void kcv::read_json(kcv::kcsapi::api_mst_slotitem&, const std::filesystem::path&);

// clang-format on
