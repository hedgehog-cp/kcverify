// std
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <vector>

// kcv
#include "core/battlelog/generate_battlelog.hpp"
#include "core/context_data.hpp"
#include "core/json/read_json.hpp"
#include "extensions/exception.hpp"
#include "models/eoen/database/sortie/sortie_record.hpp"

int main() try {
    auto ctx = kcv::context_data{};
    ctx.api_mst_ship("./assets/api_mst_ship.json");
    ctx.api_mst_slotitem("./assets/api_mst_slotitem.json");
    ctx.destination("./assets/eoen/destination.json");
    ctx.fit_bonuses("./assets/eoen/fit_bonuses.json");
    ctx.map_bonus("./assets/kc3kai/bonus/7-4.json");
    ctx.map_bonus("./assets/kc3kai/bonus/7-5.json");

    for (const auto& dir : std::filesystem::directory_iterator{"./data"}) {
        auto sortie_records = std::vector<kcv::eoen::database::sortie::sortie_record>{};
        kcv::read_json(sortie_records, dir.path());

        for (const auto& sortie_record : sortie_records) {
            const auto battlelogs = kcv::generate_battlelog(sortie_record, ctx.api_mst_ship(), ctx.api_mst_slotitem());
            for ([[maybe_unused]] const auto& battlelog : battlelogs) {
                // ...
            }
        }
    }

} catch (const std::exception& e) {
    kcv::print_exception(stderr, e);
    return EXIT_FAILURE;
}