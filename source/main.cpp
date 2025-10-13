// std
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <print>
#include <vector>

// kcv
#include "core/battlelog/generate_battlelog.hpp"
#include "core/utility/read_json.hpp"
#include "extensions/exception.hpp"
#include "extensions/formatter.hpp"
#include "models/eoen/database/sortie/sortie_record.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"

int main() try {
    const auto api_mst_ship = []() -> kcv::kcsapi::api_mst_ship {
        auto temp = kcv::kcsapi::api_mst_ship{};
        kcv::read_json(temp, std::filesystem::path{"./assets/api_mst_ship.json"});
        return temp;
    }();

    const auto api_mst_slotitem = []() -> kcv::kcsapi::api_mst_slotitem {
        auto temp = kcv::kcsapi::api_mst_slotitem{};
        kcv::read_json(temp, std::filesystem::path{"./assets/api_mst_slotitem.json"});
        return temp;
    }();

    const auto fit_bonuses = []() -> std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment> {
        auto temp = std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>{};
        kcv::read_json(temp, std::filesystem::path{"./assets/fit_bonuses.json"});
        return temp;
    }();

    for (const auto& dir : std::filesystem::directory_iterator{"./data"}) {
        const auto sortie_records = [](const auto& fname) -> std::vector<kcv::eoen::database::sortie::sortie_record> {
            auto temp = std::vector<kcv::eoen::database::sortie::sortie_record>{};
            kcv::read_json(temp, fname);
            return temp;
        }(dir.path());

        for (const auto& sortie_record : sortie_records) {
            const auto battlelogs = kcv::generate_battlelog(api_mst_ship, api_mst_slotitem, fit_bonuses, sortie_record);
            for ([[maybe_unused]] const auto& battlelog : battlelogs) {
                // ...
            }
        }
    }

} catch (const std::exception& e) {
    kcv::print_exception(stderr, e);
    return EXIT_FAILURE;
}