// std
#include <algorithm>
#include <filesystem>
#include <print>
#include <ranges>

// kcv
#include "eoen/database/sortie/sortie_record.hpp"
#include "json/read_json.hpp"
#include "kcsapi/api_start2/api_mst_ship.hpp"
#include "kcsapi/api_start2/api_mst_slotitem.hpp"
#include "sortie_data/sortie_data.hpp"

// kcv::test
#include "root.hpp"

int main() {
    const auto api_mst_ship = []() static -> kcv::kcsapi::api_mst_ship {
        auto temp = kcv::kcsapi::api_mst_ship{};
        kcv::read_json(temp, kcv::test::root / "test/sortie_data/api_mst_ship.json");
        if (not std::ranges::is_sorted(temp, {}, &kcv::kcsapi::api_mst_ship_value_type::api_id)) {
            std::ranges::sort(temp, {}, &kcv::kcsapi::api_mst_ship_value_type::api_id);
        }
        return temp;
    }();

    const auto api_mst_slotitem = []() static -> kcv::kcsapi::api_mst_slotitem {
        auto temp = kcv::kcsapi::api_mst_slotitem{};
        kcv::read_json(temp, kcv::test::root / "test/sortie_data/api_mst_slotitem.json");
        if (not std::ranges::is_sorted(temp, {}, &kcv::kcsapi::api_mst_slotitem_value_type::api_id)) {
            std::ranges::sort(temp, {}, &kcv::kcsapi::api_mst_slotitem_value_type::api_id);
        }
        return temp;
    }();

    auto data = std::filesystem::directory_iterator{kcv::test::root / "test/sortie_data/sortie_record"}
              | std::ranges::views::transform([](const auto& file) {
                    auto sortie_records = std::vector<kcv::eoen::database::sortie::sortie_record>{};
                    kcv::read_json(sortie_records, file.path());
                    return sortie_records;
                })
              | std::ranges::views::join  //
              | std::ranges::views::transform([&](const auto& sortie_record) {
                    return kcv::sortie_data::from_eoen(sortie_record, api_mst_ship, api_mst_slotitem);
                });

    for (const auto& sortie_data : data) {
        for (const auto& fleet : sortie_data.fleet_data().fleets()) {
            if (not fleet.has_value()) continue;
            for (const auto& ship : fleet->ships()) {
                std::println("{}", ship.mst().api_name);
            }
        }
    }
}