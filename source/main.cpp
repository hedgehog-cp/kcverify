// std
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <vector>

// kcv
#include "kcv/core/context_data.hpp"
#include "kcv/core/json/read_json.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_io.hpp"
#include "kcv/domain/verification/damage_formula/damage_formula_verification.hpp"
#include "kcv/external/eoen/database/sortie/sortie_record.hpp"
#include "kcv/std_ext/exception.hpp"
#include "kcv/std_ext/formatter.hpp"

int main() try {
    auto ctx = kcv::context_data{};
    ctx.api_mst_ship("./assets/kcsapi/api_start2/api_mst_ship.json");
    ctx.api_mst_slotitem("./assets/kcsapi/api_start2/api_mst_slotitem.json");
    ctx.destination("./assets/eoen/destination.json");
    ctx.fit_bonuses("./assets/eoen/fit_bonuses.json");
    ctx.map_bonus("./assets/kc3kai/bonus/7-4.json");
    ctx.map_bonus("./assets/kc3kai/bonus/7-5.json");

    auto battlelogs = kcv::battlelogs_t{};
    battlelogs.reserve(500uz);
    for (const auto& file : std::filesystem::directory_iterator{"./data"}) {
        auto sortie_records = std::vector<kcv::eoen::database::sortie::sortie_record>{};
        kcv::read_json(sortie_records, file.path());
        for (const auto& sortie_record : sortie_records) {
            kcv::generate_battlelog(battlelogs, sortie_record, ctx.api_mst_ship(), ctx.api_mst_slotitem());
        }
    }

    kcv::write_akakari(battlelogs, "./out/battlelogs.csv");

    const auto explained_results = kcv::explain_damage(ctx, battlelogs);

} catch (const std::exception& e) {
    kcv::print_exception(stderr, e);
    return EXIT_FAILURE;
}