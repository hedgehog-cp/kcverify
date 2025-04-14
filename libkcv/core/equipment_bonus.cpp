#include "equipment_bonus.hpp"

// std
#include <algorithm>
#include <optional>

// kcv
#include "core/constants/equipment.hpp"
#include "core/sortie/entities/equipment.hpp"
#include "core/sortie/entities/ship.hpp"
#include "core/sortie/entities/slot.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_data.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_value.hpp"
#include "models/kcsapi/types/api_type.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"

namespace {

/// @brief 装備種3(カテゴリ)で指定された装備を搭載しているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_equipment(
    const kcv::sortie::ship& ship, const std::optional<std::vector<kcv::kcsapi::category>>& categories
) {
    if (categories.has_value()) {
        const bool has_fit_equipment = std::ranges::any_of(
            ship.slots(),
            [&categories](const std::optional<kcv::sortie::equipment>& equipment) -> bool {
                if (not equipment.has_value()) return false;
                const auto category = std::get<kcv::kcsapi::idx_type::category>(equipment->mst().api_type);
                return std::ranges::contains(*categories, category);
            },
            [](const kcv::sortie::slot& slot) { return slot.equipment(); }
        );
        if (not has_fit_equipment) {
            return false;
        }
    }

    return true;
}

/// @brief 装備IDで指定された装備を搭載しているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_equipment(
    const kcv::sortie::ship& ship, const std::optional<std::vector<kcv::kcsapi::equipment_id>>& ids
) {
    if (ids.has_value()) {
        const bool has_fit_equipment = std::ranges::any_of(
            ship.slots(),
            [&ids](const std::optional<kcv::sortie::equipment>& equipment) -> bool {
                if (not equipment.has_value()) return false;
                const auto id = equipment->mst().api_id;
                return std::ranges::contains(*ids, id);
            },
            [](const kcv::sortie::slot& slot) { return slot.equipment(); }
        );
        if (not has_fit_equipment) {
            return false;
        }
    }

    return true;
}

/// @brief 指定された装備を搭載しているかを検証する.
/// 搭載していないならば, ボーナス付与なし. 次のボーナスへ.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_bonus_equipment(
    const kcv::sortie::ship& ship, const kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment per_equipment
) {
    const auto& [categories, ids, _] = per_equipment;
    return matches_equipment(ship, categories) and matches_equipment(ship, ids);
}

/// @brief 指定された艦娘の条件を満たしているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_ship(
    const kcv::sortie::ship& ship, const kcv::eoen::serialization::fit_bonus::fit_bonus_data& data
) {
    if (data.original_id.has_value() and not std::ranges::contains(*data.original_id, ship.base_id())) {
        return false;
    }

    if (data.ship_class.has_value() and not std::ranges::contains(*data.ship_class, ship.mst().api_ctype)) {
        return false;
    }

    if (data.nationality.has_value() and not std::ranges::contains(*data.nationality, ship.nationality())) {
        return false;
    }

    if (data.ship_type.has_value() and not std::ranges::contains(*data.ship_type, ship.mst().api_stype)) {
        return false;
    }

    if (data.ship_id.has_value() and not std::ranges::contains(*data.ship_id, ship.mst().api_id)) {
        return false;
    }

    return true;
}

/// @brief 指定された装備の条件を満たしているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_required_id(
    const kcv::sortie::ship& ship, const kcv::eoen::serialization::fit_bonus::fit_bonus_data& data
) {
    if (data.requires_id.has_value()) {
        const auto count = std::ranges::count_if(
            ship.slots(),
            [&data](const std::optional<kcv::sortie::equipment>& equipment) -> bool {
                if (not equipment.has_value()) return false;
                return std::ranges::contains(*data.requires_id, equipment->mst().api_id)
                   and (not data.requires_level.has_value() or equipment->level() >= *data.requires_level);
            },
            [](const kcv::sortie::slot& slot) { return slot.equipment(); }
        );
        if (count < data.requires_num.value_or(1)) {
            return false;
        }
    }

    return true;
}

/// @brief 指定された装備の条件を満たしているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_required_category(
    const kcv::sortie::ship& attacker, const kcv::eoen::serialization::fit_bonus::fit_bonus_data& data
) {
    if (data.requires_type.has_value()) {
        const auto count = std::ranges::count_if(
            attacker.slots(),
            [&categories = *data.requires_type](const std::optional<kcv::sortie::equipment>& equipment) -> bool {
                if (not equipment.has_value()) return false;
                const auto category = std::get<kcv::kcsapi::idx_type::category>(equipment->mst().api_type);
                return std::ranges::contains(categories, category);
            },
            [](const kcv::sortie::slot& slot) { return slot.equipment(); }
        );
        if (count < data.requires_num_type.value_or(1)) {
            return false;
        }
    }

    return true;
}

/// @brief 指定された条件を満たしているかを検証する.
/// 満たしていないならば, ボーナス付与なし. 次のボーナスへ.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_bonus_data(
    const kcv::sortie::ship& ship, const kcv::eoen::serialization::fit_bonus::fit_bonus_data& data
) {
    return matches_ship(ship, data) and matches_required_id(ship, data) and matches_required_category(ship, data);
}

/// @brief 指定された条件を満たす装備の搭載数を数え上げる.
constexpr int count_fit_equipment(
    const kcv::sortie::ship& ship, const kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment& per_equipment,
    const kcv::eoen::serialization::fit_bonus::fit_bonus_data& data
) {
    const auto& [categories, ids, _] = per_equipment;

    // count_ifの返り値の型はintではないが,
    // ship.slots().size() <= 6 であり, int型の範囲で表現できるためint型で返す.
    // int型で返すのは, fit_bonus_value::operator*の定義を簡略化するため.
    return std::ranges::count_if(
        ship.slots(),
        [&data, &categories, &ids](const std::optional<kcv::sortie::equipment>& equipment) -> bool {
            if (not equipment.has_value()) return false;

            if (ids.has_value()) {
                const auto id = equipment->mst().api_id;
                if (not std::ranges::contains(*ids, id)) {
                    return false;
                }
            }

            if (categories.has_value()) {
                const auto category = std::get<kcv::kcsapi::idx_type::category>(equipment->mst().api_type);
                if (not std::ranges::contains(*categories, category)) {
                    return false;
                }
            }

            if (data.level.has_value()) {
                if (equipment->level() < *data.level) {
                    return false;
                }
            }

            return true;
        },
        [](const kcv::sortie::slot& slot) { return slot.equipment(); }
    );
}

}  // namespace

auto kcv::get_equipment_bonus(
    const kcv::sortie::ship& ship,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& bonus_object
) -> kcv::eoen::serialization::fit_bonus::fit_bonus_value {
    const bool has_anti_air_radar = std::ranges::any_of(
        ship.slots(),
        [](const std::optional<kcv::sortie::equipment>& equipment) -> bool {
            return equipment.has_value() and kcv::is_anti_air_radar(equipment->mst());
        },
        [](const kcv::sortie::slot& slot) { return slot.equipment(); }
    );

    const bool has_surface_radar = std::ranges::any_of(
        ship.slots(),
        [](const std::optional<kcv::sortie::equipment>& equipment) -> bool {
            return equipment.has_value() and kcv::is_surface_radar(equipment->mst());
        },
        [](const kcv::sortie::slot& slot) { return slot.equipment(); }
    );

    const bool has_accuracy_radar = std::ranges::any_of(
        ship.slots(),
        [](const std::optional<kcv::sortie::equipment>& equipment) -> bool {
            return equipment.has_value() and kcv::is_accuracy_radar(equipment->mst());
        },
        [](const kcv::sortie::slot& slot) { return slot.equipment(); }
    );

    auto total = kcv::eoen::serialization::fit_bonus::fit_bonus_value{};

    for (const auto& per_equipment : bonus_object) {
        if (not matches_bonus_equipment(ship, per_equipment)) continue;
        for (const auto& data : per_equipment.bonuses) {
            if (not matches_bonus_data(ship, data)) continue;

            if (data.bonus.has_value()) {
                const auto count = count_fit_equipment(ship, per_equipment, data);

                if (data.num.has_value() and count < *data.num) {
                    // 算入しない
                } else if (data.num.has_value() or data.requires_id.has_value() or data.requires_type.has_value()) {
                    total += *data.bonus;
                } else {
                    total += *data.bonus * count;
                }
            }

            if (data.bonus_if_anti_air_radar.has_value() and has_anti_air_radar) {
                total += *data.bonus_if_anti_air_radar;
            }

            if (data.bonus_if_surface_radar.has_value() and has_surface_radar) {
                total += *data.bonus_if_surface_radar;
            }

            if (data.bonus_if_accuracy_radar.has_value() and has_accuracy_radar) {
                total += *data.bonus_if_accuracy_radar;
            }
        }
    }

    return total;
}

#if 0  // MARK: WIP

namespace {

constexpr bool matches_ship(const kcv::sortie::ship& ship, const kcv::kc3kai::bonus_data& data) {
    if (data.shipClass.has_value() and not std::ranges::contains(*data.shipClass, ship.mst().api_ctype)) {
        return false;
    }

    // なぜか文字列になっているのでenumに変換してから比較する.
    // KC3Kai/kancolle-replay/js/data/country_ctype.json
    static constexpr auto countries = std::to_array<std::pair<std::string_view, kcv::kcsapi::nationality>>({
        {"JP", kcv::kcsapi::nationality::japanese},
        {"DE", kcv::kcsapi::nationality::german},
        {"IT", kcv::kcsapi::nationality::italian},
        {"US", kcv::kcsapi::nationality::american},
        {"GB", kcv::kcsapi::nationality::british},
        {"FR", kcv::kcsapi::nationality::french},
        {"RU", kcv::kcsapi::nationality::russian},
        {"SE", kcv::kcsapi::nationality::swedish},
        {"NL", kcv::kcsapi::nationality::dutch},
        {"AU", kcv::kcsapi::nationality::australian},
    });
    const auto itr = std::ranges::find(countries, ship.nationality(), &decltype(countries)::value_type::second);
    if (itr != countries.end()) {
        if (data.shipCountry.has_value() and not std::ranges::contains(*data.shipCountry, itr->first)) {
            return false;
        }
    }

    if (data.shipId.has_value() and not std::ranges::contains(*data.shipId, ship.mst().api_id)) {
        return false;
    }

    if (data.shipBase.has_value() and not std::ranges::contains(*data.shipBase, ship.base_id())) {
        return false;
    }

    if (data.shipType.has_value() and not std::ranges::contains(*data.shipType, ship.mst().api_stype)) {
        return false;
    }

    return true;
}

constexpr bool matches_requires_id(const kcv::sortie::ship& ship, const kcv::kc3kai::bonus_data& data) {
    if (not data.requiresId.has_value()) {
        return false;
    }

    int count = 0;
    for (const auto& id : *data.requiresId) {
        if (data.requiresIdLevel.has_value()) {
            //...
        } else {
            //...
        }
    }

    return count < data.requiresIdNum.value_or(1);
}

}  // namespace

auto kcv::get_equipment_bonus(
    const kcv::sortie::ship& ship, const std::vector<kcv::kc3kai::mst_slotitem_bonus>& bonus_object
) -> kcv::kc3kai::bonus_value {
    const bool has_anti_air_radar = std::ranges::any_of(
        ship.slots(),
        [](const std::optional<kcv::sortie::equipment>& equipment) -> bool { return equipment.has_value() and false; },
        [](const kcv::sortie::slot& slot) { return slot.equipment(); }
    );

    const bool has_surface_radar = std::ranges::any_of(
        ship.slots(),
        [](const std::optional<kcv::sortie::equipment>& equipment) -> bool { return equipment.has_value() and false; },
        [](const kcv::sortie::slot& slot) { return slot.equipment(); }
    );

    const bool has_accuracy_radar = std::ranges::any_of(
        ship.slots(),
        [](const std::optional<kcv::sortie::equipment>& equipment) -> bool { return equipment.has_value() and false; },
        [](const kcv::sortie::slot& slot) { return slot.equipment(); }
    );

    auto total = kcv::kc3kai::bonus_value{};

    for (const auto& mst_slotitem_bonus : bonus_object) {
        for (const auto& data : mst_slotitem_bonus.bonuses) {
            if (data.requiresAR.has_value() and not has_accuracy_radar) continue;
            if (data.requiresSR.has_value() and not has_surface_radar) continue;
            if (data.requiresAR.has_value() and not has_anti_air_radar) continue;
            if (matches_ship(ship, data)) continue;
            if (matches_requires_id(ship, data)) continue;
        }
    }

    return total;
}

#endif  // unimplemented
