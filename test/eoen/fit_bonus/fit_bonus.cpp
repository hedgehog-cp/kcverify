// std
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <ranges>
#include <vector>

// kcv
#include "common.hpp"
#include "eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "fit_bonuses/fit_bonuses.hpp"
#include "kcsapi/api_start2/api_mst_ship.hpp"
#include "kcsapi/api_start2/api_mst_slotitem.hpp"
#include "sortie/ship.hpp"
#include "sortie/sortie_data.hpp"

// kcv::test
#include "root.hpp"

namespace {

const auto api_mst_ship = []() static -> kcv::kcsapi::api_mst_ship {
    using T   = kcv::kcsapi::api_mst_ship;
    auto temp = T{};
    kcv::read_json(temp, kcv::test::root / "test/eoen/fit_bonus/api_mst_ship.json");
    if (not std::ranges::is_sorted(temp, {}, &T::value_type::api_id)) {
        std::ranges::sort(temp, {}, &T::value_type::api_id);
    }
    return temp;
}();

const auto api_mst_slotitem = []() static -> kcv::kcsapi::api_mst_slotitem {
    using T   = kcv::kcsapi::api_mst_slotitem;
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

auto test(const std::filesystem::path& fname) -> std::vector<kcv::fit_bonuses::bonus_value> {
    const auto sortie_record = [&fname]() -> kcv::eoen::database::sortie::sortie_record {
        auto temp = std::vector<kcv::eoen::database::sortie::sortie_record>{};
        kcv::read_json(temp, kcv::test::root / fname);
        return temp.at(0);
    }();
    const auto sortie_data = kcv::sortie::sortie_data::from_eoen(sortie_record, api_mst_ship, api_mst_slotitem);
    const auto& fleet      = *sortie_data.fleet_data().fleets().at(0);
    return fleet.ships()  //
         | std::ranges::views::transform([&](const kcv::sortie::ship& e) {
               return kcv::fit_bonuses::calc_bonus(e, fit_bonuses);
           })
         | std::ranges::to<std::vector>();
}

void print_bonus(const kcv::fit_bonuses::bonus_value& v) {
    std::println(
        "{:2}, {:2}, {:2}, {:2}, {:2}, {:2}, {:2}, {:2}, {:2}, {:2}",  //
        v.houg, v.tyku, v.kaih, v.souk, v.houm, v.tais, v.raig, v.saku, v.leng, v.baku
    );
}

}  // namespace

int main() {
    // [0]: 加賀改二護
    // [1]: 時雨改三
    // [2]: 矢矧改二乙
    // [3]: 龍鳳改二
    {
        std::println("test 0");

        const auto expected = std::vector<kcv::fit_bonuses::bonus_value>({
            {
                .houg = 13,
                .tyku = 1,
                .kaih = 6,
                .souk = 0,
                .houm = 0,
                .tais = 19,
                .raig = 0,
                .saku = 0,
                .leng = 0,
                .baku = 0,
            },
            {
                .houg = 5,
                .tyku = 0,
                .kaih = 14,
                .souk = 0,
                .houm = 0,
                .tais = 13,
                .raig = 5,
                .saku = 1,
                .leng = 0,
                .baku = 0,
            },
            {
                .houg = 6,
                .tyku = 1,
                .kaih = 5,
                .souk = 0,
                .houm = 0,
                .tais = 7,
                .raig = 0,
                .saku = 0,
                .leng = 0,
                .baku = 0,
            },
            {
                .houg = 4,
                .tyku = 0,
                .kaih = 2,
                .souk = 0,
                .houm = 0,
                .tais = 3,
                .raig = 4,
                .saku = 0,
                .leng = 0,
                .baku = 0,
            },
        });
        const auto result   = test("test/eoen/fit_bonus/sortie_record/0/sortie_record.json");

        if (const bool is_ok = (result == expected); is_ok) {
            std::println("ok");
        } else {
            for (const auto& e : result) print_bonus(e);

            std::exit(EXIT_FAILURE);
        }
    }

    std::println("");

    // [0]: 鹿島改
    // [1]: 沖波改二
    // [2]: 綾波改二
    // [3]: 島風改
    // [4]: 飛龍改二
    {
        std::println("test 1");

        const auto expected = std::vector<kcv::fit_bonuses::bonus_value>({
            {
                .houg = 0,
                .tyku = 0,
                .kaih = 4,
                .souk = 0,
                .houm = 0,
                .tais = 6,
                .raig = 0,
                .saku = 0,
                .leng = 0,
                .baku = 0,
            },
            {
                .houg = 17,
                .tyku = 5,
                .kaih = 10,
                .souk = 0,
                .houm = 7,
                .tais = 2,
                .raig = 12,
                .saku = 2,
                .leng = 0,
                .baku = 0,
            },
            {
                .houg = 4,
                .tyku = 13,
                .kaih = 0,
                .souk = 0,
                .houm = 0,
                .tais = 0,
                .raig = 0,
                .saku = 0,
                .leng = 0,
                .baku = 0,
            },
            {
                .houg = 6,
                .tyku = 0,
                .kaih = 4,
                .souk = 0,
                .houm = 0,
                .tais = 0,
                .raig = 1,
                .saku = 0,
                .leng = 0,
                .baku = 0,
            },
            {
                .houg = 12,
                .tyku = 2,
                .kaih = 3,
                .souk = 0,
                .houm = 5,
                .tais = 0,
                .raig = 0,
                .saku = 0,
                .leng = 1,
                .baku = 0,
            },
        });
        const auto result   = test("test/eoen/fit_bonus/sortie_record/1/sortie_record.json");

        if (const bool is_ok = (result == expected); is_ok) {
            std::println("ok");
        } else {
            for (const auto& e : result) print_bonus(e);

            std::exit(EXIT_FAILURE);
        }
    }
}