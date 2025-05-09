// std
#include <cstdlib>
#include <filesystem>
#include <print>
#include <ranges>
#include <vector>

// kcv
#include "core/common/formatter.hpp"
#include "core/common/read_json.hpp"
#include "core/sortie/entities/ship.hpp"
#include "core/sortie/equipment_bonus.hpp"
#include "models/eoen/database/sortie/sortie_record.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_value.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"

int main() {
    const auto api_mst_ship = []() static -> kcv::kcsapi::api_mst_ship {
        auto temp = kcv::kcsapi::api_mst_ship{};
        kcv::read_json(temp, std::filesystem::path{"./assets/api_mst_ship.json"});
        return temp;
    }();

    const auto api_mst_slotitem = []() static -> kcv::kcsapi::api_mst_slotitem {
        auto temp = kcv::kcsapi::api_mst_slotitem{};
        kcv::read_json(temp, std::filesystem::path{"./assets/api_mst_slotitem.json"});
        return temp;
    }();

    const auto bonus_object = []() static -> std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment> {
        auto temp = std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>{};
        kcv::read_json(temp, std::filesystem::path{"./assets/fit_bonuses.json"});
        return temp;
    }();

    for (const auto& dir : std::filesystem::directory_iterator{"./test/libkcv/core/sortie/equipment_bonus/data"}) {
        const auto sortie_record = [](const auto& fname) static {
            auto temp = std::vector<kcv::eoen::database::sortie::sortie_record>{};
            kcv::read_json(temp, fname);
            return temp.at(0);
        }(dir.path() / "sortie_record.json");

        const auto expected = [](const auto& fname) static {
            auto temp = std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_value>{};
            kcv::read_json(temp, fname);
            return temp;
        }(dir.path() / "expected.json");

        const auto& ships = sortie_record.fleet_data.fleets.at(0)->ships;
        if (ships.size() != expected.size()) {
            return EXIT_FAILURE;
        }

        for (const auto& [eoen_ship, bonus] : std::ranges::views::zip(ships, expected)) {
            const auto sortie_ship     = kcv::sortie::ship::from_eoen(eoen_ship, api_mst_ship, api_mst_slotitem);
            const auto equipment_bonus = kcv::sortie::get_equipment_bonus(sortie_ship, bonus_object);
            if (equipment_bonus != bonus) {
                std::println("{}", sortie_ship.mst().api_name);
                std::println("calculated: {:>2}", equipment_bonus);
                std::println("expected:   {:>2}", bonus);
                std::println("");

                return EXIT_FAILURE;
            }
        }
    }
}