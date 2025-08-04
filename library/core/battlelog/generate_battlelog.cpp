#include "core/battlelog/generate_battlelog.hpp"

// std
#include <variant>
#include <vector>

// kcv
#include "core/battlelog/battlelog.hpp"
#include "core/battlelog/sortie_api.hpp"
#include "models/eoen/database/sortie/sortie_record.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"

auto kcv::generate_battlelog(
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    const kcv::eoen::database::sortie::sortie_record& sortie_record
) -> std::vector<kcv::battlelog> {
    auto battlelogs = std::vector<kcv::battlelog>{};

    const auto sortie_apis = kcv::parse_api_files(sortie_record.api_files);
    for (const auto& api : sortie_apis) {
        std::visit(
            [&](const auto& v) {
                kcv::process_api(v, api_mst_ship, api_mst_slotitem, fit_bonuses, sortie_record, battlelogs);
            },
            api
        );
    }

    return battlelogs;
}