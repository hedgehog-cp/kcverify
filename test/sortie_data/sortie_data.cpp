// std
#include <algorithm>
#include <filesystem>
#include <optional>
#include <print>
#include <ranges>

// kcv
#include "eoen/database/sortie/sortie_record.hpp"
#include "json/read_json.hpp"
#include "kcapi/api_req_sortie/battle/response.hpp"
#include "kcapi/api_start2/api_mst_ship.hpp"
#include "kcapi/api_start2/api_mst_slotitem.hpp"
#include "kcapi/types/svdata.hpp"
#include "root.hpp"
#include "sortie_data/sortie_data.hpp"

int main() {
    const auto api_mst_ship = []() static -> kcv::kcapi::api_mst_ship {
        auto result = kcv::kcapi::api_mst_ship{};
        kcv::read_json(result, kcv::test::root / std::filesystem::path{"./data/api_mst_ship/latest.json"});
        if (not std::ranges::is_sorted(result, {}, &kcv::kcapi::api_mst_ship_value_type::api_id)) {
            std::ranges::sort(result, {}, &kcv::kcapi::api_mst_ship_value_type::api_id);
        }
        return result;
    }();

    const auto api_mst_slotitem = []() static -> kcv::kcapi::api_mst_slotitem {
        auto result = kcv::kcapi::api_mst_slotitem{};
        kcv::read_json(result, kcv::test::root / std::filesystem::path{"./data/api_mst_slotitem/latest.json"});
        if (not std::ranges::is_sorted(result, {}, &kcv::kcapi::api_mst_slotitem_value_type::api_id)) {
            std::ranges::sort(result, {}, &kcv::kcapi::api_mst_slotitem_value_type::api_id);
        }
        return result;
    }();

    auto data = std::filesystem::directory_iterator{kcv::test::root / "./data/eoen_sortie_detail"}
              | std::ranges::views::transform([](const auto& file) {
                    auto sortie_detail = std::vector<kcv::eoen::database::sortie::sortie_record>{};
                    kcv::read_json(sortie_detail, file.path());
                    return sortie_detail;
                })
              | std::ranges::views::join  //
              | std::ranges::views::transform([&](const auto& sortie_record) {
                    return kcv::sortie_data::from_eoen(sortie_record, api_mst_ship, api_mst_slotitem);
                });

    for (const auto& sortie_data : data) {
        std::println("雷撃戦");
        // 雷撃戦
        {
            const auto& raigeki = sortie_data.api_req_sortie_battle_response().and_then([](const auto& e) {
                return e.api_data.api_raigeki;
            });

            if (raigeki.has_value()) {
                for (const auto& [ecl, edam, erai, eydam, fcl, fdam, frai, fydam] : std::ranges::views::zip(
                         raigeki->api_ecl,    //
                         raigeki->api_edam,   //
                         raigeki->api_erai,   //
                         raigeki->api_eydam,  //
                         raigeki->api_fcl,    //
                         raigeki->api_fdam,   //
                         raigeki->api_frai,   //
                         raigeki->api_fydam   //
                     ))                       //
                {
                    if (erai >= 0) {
                        std::print("{}, ", sortie_data.fleet_data().fleets().at(0)->ships().at(erai).mst().api_name);
                    } else {
                        std::print("xxx, ");
                    }
                }
            }
            std::println("");
        }
    }
}