#include "core/damage_formula/map_bonus.hpp"

#include <algorithm>

#include "core/entity/ship.hpp"
#include "models/kc3kai/bonus/bonus.hpp"

namespace {

bool matches_ship(const kcv::ship& ship, const kcv::kc3kai::bonus_bonus_t& data) {
    if (data.ship_base.has_value() and not std::ranges::contains(*data.ship_base, ship.base_id())) {
        return false;
    }

    if (data.ship_type.has_value() and not std::ranges::contains(*data.ship_type, ship.mst().api_stype)) {
        return false;
    }

    return true;
}

}  // namespace

auto kcv::total_map_bonus(
    const kcv::ship& ship,                                      //
    const std::vector<kcv::kc3kai::bonus_bonus_t>& map_bonuses  //
) -> kcv::map_bonus_result {
    auto total = kcv::map_bonus_result{};

    for (const auto& data : map_bonuses) {
        /// TODO: 条件を追加する. とりあえず#7-4, #7-5に対応.
        if (not matches_ship(ship, data)) {
            continue;
        }

        if (data.dmg.has_value()) {
            total.dmg *= *data.dmg;
        }

        if (data.acc.has_value()) {
            total.acc *= *data.acc;
        }

        if (data.eva.has_value()) {
            total.eva *= *data.eva;
        }
    }

    return total;
}