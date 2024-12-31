// WIP

// std
#include <algorithm>

// kcv
#include "eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "json/read_json.hpp"
#include "kcapi/api_start2/api_mst_ship.hpp"
#include "kcapi/api_start2/api_mst_slotitem.hpp"

// kcv::test
#include "root.hpp"

int main() {
    const auto api_mst_ship = []() static -> kcv::kcapi::api_mst_ship {
        using T   = kcv::kcapi::api_mst_ship;
        auto temp = T{};
        kcv::read_json(temp, kcv::test::root / "test/eoen/fit_bonus/api_mst_ship.json");
        if (not std::ranges::is_sorted(temp, {}, &T::value_type::api_id)) {
            std::ranges::sort(temp, {}, &T::value_type::api_id);
        }
        return temp;
    }();

    const auto api_mst_slotitem = []() static -> kcv::kcapi::api_mst_slotitem {
        using T   = kcv::kcapi::api_mst_slotitem;
        auto temp = T{};
        kcv::read_json(temp, kcv::test::root / "test/eoen/fit_bonus/api_mst_slotitem.json");
        if (not std::ranges::is_sorted(temp, {}, &T::value_type::api_id)) {
            std::ranges::sort(temp, {}, &T::value_type::api_id);
        }
        return temp;
    }();

    const auto fit_bonuses = []() static -> std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment> {
        auto temp = std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>{};
        kcv::read_json(temp, kcv::test::root / "test/eoen/fit_bonus/fit_bonuses.json");
        return temp;
    }();
}