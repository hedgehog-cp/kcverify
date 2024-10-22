
// std
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <vector>

// glz
#include <glaze/json.hpp>

// kcv
#include "eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "eoen/serialization/fit_bonus/fit_bonus_value.hpp"

// meta files
#include "eoen/serialization/fit_bonus/meta/fit_bonus_data.hpp"
#include "eoen/serialization/fit_bonus/meta/fit_bonus_per_equipment.hpp"

// kcv::test
#include "root.hpp"

namespace {

struct equipment_t final {
    /// @brief 装備ID
    int id;

    /// @brief api_type[2]
    int type2;

    /// @brief 改修値
    int level;
};

struct attacker_t final {
    int id;
    int ctype;
    int stype;
    int origina_id;
    int nationality;
    std::vector<equipment_t> slot;
};

void test_fit_bonus() {
    // 時雨改三 [三式水中探信儀改★10, 試製15cm9連装対潜噴進砲★0, 二式爆雷改二★10]
    const auto attacker = attacker_t{
        .id            = 961,
        .ctype         = 23,
        .stype         = 2,
        .origina_id    = 43,
        .nationality   = 1,
        .slot = std::vector{
            equipment_t{.id = 438, .type2 = 14, .level = 10},
            equipment_t{.id = 288, .type2 = 15, .level = 0},
            equipment_t{.id = 488, .type2 = 15, .level = 10},
        }
    };

    constexpr auto expected_result = kcv::eoen::serialization::fit_bonus::fit_bonus_value{
        .houg = 1,
        .tyku = 0,
        .kaih = 14,
        .souk = 0,
        .houm = 3,
        .tais = 20,
        .raig = 0,
        .saku = 0,
        .leng = 0,
        .baku = 0,
    };

    auto fit_bonuses = std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>{};
    {
        const auto dir   = std::filesystem::path{"test/eoen/fit_bonus/"};
        const auto fname = kcv::test::root / dir / "fit_bonuses.json";
        auto ifs         = std::ifstream{fname};
        const auto fsize = std::filesystem::file_size(fname);
        auto buffer      = std::string(fsize, '\0');
        ifs.read(buffer.data(), buffer.size());

        if (const auto error = glz::read_json(fit_bonuses, buffer); error) {
            std::exit(EXIT_FAILURE);
        }

        if (const auto result = glz::write_json(fit_bonuses); not result.has_value()) {
            std::exit(EXIT_FAILURE);
        }
    }

    auto fit_bonus = std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_value>{};
    {
        const int anti_air_radar = 0;
        const int surface_radar  = 0;
        const int accuracy_radar = 0;

        for (const auto &[types, ids, bonuses] : fit_bonuses) {
            if (not(types or ids) and bonuses.size() > 0) continue;

            const auto fit_equipments = [&]() -> std::vector<equipment_t> {
                if (types) {
                    return attacker.slot  //
                         | std::views::filter([&](const equipment_t &e) -> bool {
                               return std::ranges::find(*types, e.type2) != types->end();
                           })
                         | std::ranges::to<std::vector>();
                }
                if (ids) {
                    return attacker.slot  //
                         | std::views::filter([&](const equipment_t &e) -> bool {
                               return std::ranges::find(*ids, e.id) != ids->end();
                           })
                         | std::ranges::to<std::vector>();
                }

                // maybe unreachable
                return {};
            }();
            if (fit_equipments.size() == 0) continue;

            for (const auto &bonus : bonuses) {
                // 未改造判定
                if (const auto &v = bonus.original_id; v and std::ranges::find(*v, attacker.origina_id) == v->end()) {
                    continue;
                }

                // 艦型判定
                if (const auto &v = bonus.ship_class; v and std::ranges::find(*v, attacker.ctype) == v->end()) {
                    continue;
                }

                // 艦型判定
                if (const auto &v = bonus.nationality; v and std::ranges::find(*v, attacker.nationality) == v->end()) {
                    continue;
                }

                // 艦船ID判定
                if (const auto &v = bonus.ship_id; v and std::ranges::find(*v, attacker.id) == v->end()) {
                    continue;
                }

                // 対空電探判定
                if (bonus.air_radar and not anti_air_radar) {
                    continue;
                }

                // 水上電探判定
                if (bonus.surface_radar and not surface_radar) {
                    continue;
                }

                // 命中電探判定
                if (bonus.accuracy_radar and not accuracy_radar) {
                    continue;
                }

                if (bonus.requires_id) {
                    const auto &required_slotitems = bonus.requires_id;
                    const auto &required_level     = bonus.requires_level.value_or(0);
                    const auto target_slotitems
                        = attacker.slot  //
                        | std::views::filter([&](const equipment_t &e) -> bool {
                              return required_slotitems
                                 and std::ranges::find(*required_slotitems, e.id) != required_slotitems->end();
                          })
                        | std::ranges::to<std::vector>();

                    if (bonus.num and target_slotitems.size() < *bonus.num) {
                        continue;
                    }

                    if (required_level and std::ranges::any_of(target_slotitems, [&](const equipment_t &v) {
                            return v.level >= required_level;
                        })) {
                        continue;
                    }

                    if (target_slotitems.size() == 0) {
                        continue;
                    }
                }

                if (bonus.requires_type and not std::ranges::any_of(attacker.slot, [&](const equipment_t &v) {
                        return bonus.requires_type
                           and std::ranges::find(*bonus.requires_type, v.type2) != bonus.requires_type->end();
                    })) {
                    continue;
                }

                if (bonus.level) {
                    const auto level_fits
                        = fit_equipments
                        | std::ranges::views::filter([&](const equipment_t &v) { return v.level >= bonus.level; })
                        | std::ranges::to<std::vector>();

                    if (level_fits.size() == 0) {
                        continue;
                    }

                    if (bonus.num and level_fits.size() < bonus.num) {
                        continue;
                    }

                    if (not bonus.num) {
                        for (auto i = 0uz; i < level_fits.size(); i++) {
                            if (bonus.bonus) fit_bonus.push_back(*bonus.bonus);
                        }
                    } else {
                        if (bonus.bonus) fit_bonus.push_back(*bonus.bonus);
                    }
                } else if (bonus.num and fit_equipments.size() < bonus.num) {
                    continue;
                } else if (not bonus.num) {
                    for (auto i = 0uz; i < fit_equipments.size(); i++) {
                        if (bonus.bonus) fit_bonus.push_back(*bonus.bonus);
                    }
                } else {
                    if (bonus.bonus) fit_bonus.push_back(*bonus.bonus);
                }
            }
        }
    }

    auto result = kcv::eoen::serialization::fit_bonus::fit_bonus_value{};
    for (const auto &bonus : fit_bonus) {
        result.houg += bonus.houg;
        result.tyku += bonus.tyku;
        result.kaih += bonus.kaih;
        result.souk += bonus.souk;
        result.houm += bonus.houm;
        result.tais += bonus.tais;
        result.raig += bonus.raig;
        result.saku += bonus.saku;
        result.leng += bonus.leng;
        result.baku += bonus.baku;
    }

    assert(result.houg == expected_result.houg);
    assert(result.tyku == expected_result.tyku);
    assert(result.kaih == expected_result.kaih);
    assert(result.souk == expected_result.souk);
    assert(result.houm == expected_result.houm);
    assert(result.tais == expected_result.tais);
    assert(result.raig == expected_result.raig);
    assert(result.saku == expected_result.saku);
    assert(result.leng == expected_result.leng);
    assert(result.baku == expected_result.baku);
}

}  // namespace

int main() {
    test_fit_bonus();
}