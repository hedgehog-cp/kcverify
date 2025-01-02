#ifndef KCVERIFY_FIT_BONUSES_FIT_BONUSES_HPP_INCLUDED
#define KCVERIFY_FIT_BONUSES_FIT_BONUSES_HPP_INCLUDED

// std
#include <algorithm>

// kcv
#include "eoen/serialization/fit_bonus/fit_bonus_data.hpp"
#include "eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "eoen/serialization/fit_bonus/fit_bonus_value.hpp"
#include "kcsapi/types/api_type.hpp"
#include "kcsapi/types/enum/category.hpp"
#include "kcsapi/types/enum/equipment_id.hpp"
#include "sortie_data/equipment.hpp"
#include "sortie_data/ship.hpp"
#include "sortie_data/slot.hpp"

namespace kcv {
namespace fit_bonuses {

using bonus_data      = eoen::serialization::fit_bonus::fit_bonus_data;
using bonus_equipment = eoen::serialization::fit_bonus::fit_bonus_per_equipment;
using bonus_value     = eoen::serialization::fit_bonus::fit_bonus_value;

/// @brief 各種電探の搭載状態.
/// @note より汎用的な関数を実装した際に不要となるが, それまではこれを使う.
struct radar final {
    static constexpr bool is_radar(const std::optional<kcv::equipment>& e) noexcept {
        if (not e.has_value()) return false;
        return std::get<kcsapi::idx_type::icon>(e->mst().api_type) == kcsapi::icon::radar;
    }

    static constexpr bool is_anti_air_radar(const std::optional<kcv::equipment>& e) noexcept {
        if (not e.has_value()) return false;
        return is_radar(e) and e->mst().api_tyku >= 2;
    }

    static constexpr bool is_surface_air_radar(const std::optional<kcv::equipment>& e) noexcept {
        if (not e.has_value()) return false;
        return is_radar(e) and e->mst().api_saku >= 5;
    }

    static constexpr bool is_accuracy_air_radar(const std::optional<kcv::equipment>& e) noexcept {
        if (not e.has_value()) return false;
        return is_radar(e) and e->mst().api_houm >= 8;
    }

    constexpr radar(const ship& attacker) noexcept
        : has_anti_air_radar{std::ranges::any_of(attacker.eqslots(), &is_anti_air_radar, &kcv::slot::equipment)}
        , has_surface_radar{std::ranges::any_of(attacker.eqslots(), &is_surface_air_radar, &kcv::slot::equipment)}
        , has_accuracy_radar{std::ranges::any_of(attacker.eqslots(), &is_accuracy_air_radar, &kcv::slot::equipment)} {
    }

    const bool has_anti_air_radar;
    const bool has_surface_radar;
    const bool has_accuracy_radar;
};

/// @brief 装備種3(カテゴリ)で指定された装備を搭載しているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_equipment(const std::optional<std::vector<kcsapi::category>>& categories, const ship& attacker) {
    if (categories.has_value()) {
        const bool has_fit_equipment = std::ranges::any_of(
            attacker.slots(),
            [&categories](const auto& equipment) -> bool {
                if (not equipment.has_value()) return false;
                const auto category = std::get<kcsapi::idx_type::category>(equipment->mst().api_type);
                return std::ranges::contains(*categories, category);
            },
            &slot::equipment
        );
        if (not has_fit_equipment) {
            return false;
        }
    }

    return true;
}

/// @brief 装備IDで指定された装備を搭載しているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_equipment(const std::optional<std::vector<kcsapi::equipment_id>>& ids, const ship& attacker) {
    if (ids.has_value()) {
        const bool has_fit_equipment = std::ranges::any_of(
            attacker.slots(),
            [&ids](const auto& equipment) -> bool {
                if (not equipment.has_value()) return false;
                const auto id = equipment->mst().api_id;
                return std::ranges::contains(*ids, id);
            },
            &slot::equipment
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
constexpr bool matches_bonus_equipment(const bonus_equipment& bonus_equipment, const ship& ship) {
    const auto& [categories, ids, _] = bonus_equipment;
    return matches_equipment(categories, ship) and matches_equipment(ids, ship);
}

/// @brief 指定された艦娘の条件を満たしているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_ship(const bonus_data& cnd, const ship& ship) {
    if (cnd.original_id.has_value() and not std::ranges::contains(*cnd.original_id, ship.original_id())) {
        return false;
    }

    if (cnd.ship_class.has_value() and not std::ranges::contains(*cnd.ship_class, ship.mst().api_ctype)) {
        return false;
    }

    if (cnd.nationality.has_value() and not std::ranges::contains(*cnd.nationality, ship.nationality())) {
        return false;
    }

    if (cnd.ship_type.has_value() and not std::ranges::contains(*cnd.ship_type, ship.mst().api_stype)) {
        return false;
    }

    if (cnd.ship_id.has_value() and not std::ranges::contains(*cnd.ship_id, ship.mst().api_id)) {
        return false;
    }

    return true;
}

/// @brief 指定された装備の条件を満たしているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_required_id(const bonus_data& cnd, const ship& attacker) {
    if (cnd.requires_id.has_value()) {
        const auto count = std::ranges::count_if(
            attacker.slots(),
            [&cnd](const auto& equipment) -> bool {
                if (not equipment.has_value()) return false;
                return std::ranges::contains(*cnd.requires_id, equipment->mst().api_id)
                   and (not cnd.requires_level.has_value() or equipment->level() >= *cnd.requires_level);
            },
            &slot::equipment
        );
        if (count < cnd.requires_num.value_or(1)) {
            return false;
        }
    }

    return true;
}

/// @brief 指定された装備の条件を満たしているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_required_category(const bonus_data& cnd, const ship& attacker) {
    if (cnd.requires_type.has_value()) {
        const auto count = std::ranges::count_if(
            attacker.slots(),
            [&categories = *cnd.requires_type](const auto& equipment) -> bool {
                if (not equipment.has_value()) return false;
                const auto category = std::get<kcsapi::idx_type::category>(equipment->mst().api_type);
                return std::ranges::contains(categories, category);
            },
            &slot::equipment
        );
        if (count < cnd.requires_num_type.value_or(1)) {
            return false;
        }
    }

    return true;
}

/// @brief 指定された条件を満たしているかを検証する.
/// 満たしていないならば, ボーナス付与なし. 次のボーナスへ.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_bonus_data(const bonus_data& bonus_data, const ship& ship) {
    return matches_ship(bonus_data, ship)
       and matches_required_id(bonus_data, ship)
       and matches_required_category(bonus_data, ship);
}

/// @brief 指定された条件を満たす装備の搭載数を数え上げる.
constexpr int count_fit_equipment(
    const ship& ship, 
    const bonus_equipment& bonus_equipment,
    const bonus_data& bonus_data
) {
    const auto& [categories, ids, _] = bonus_equipment;

    return std::ranges::count_if(
        ship.slots(),
        [&](const std::optional<equipment>& e) -> bool {
            if (not e.has_value()) return false;

            if (ids.has_value()) {
                const auto id = e->mst().api_id;
                if (not std::ranges::contains(*ids, id)) {
                    return false;
                }
            }

            if (categories.has_value()) {
                const auto category = std::get<kcsapi::idx_type::category>(e->mst().api_type);
                if (not std::ranges::contains(*categories, category)) {
                    return false;
                }
            }

            if (bonus_data.level.has_value()) {
                if (e->level() < *bonus_data.level) {
                    return false;
                }
            }

            return true;
        },
        &slot::equipment
    );
}

/// @brief 装備ボーナスを求める.
constexpr auto calc_bonus(const ship& ship, const std::vector<bonus_equipment>& bonus_list) -> bonus_value {
    auto total = bonus_value{};

    for (const auto radar = kcv::fit_bonuses::radar{ship}; const auto& bonus_equipment : bonus_list) {
        if (not matches_bonus_equipment(bonus_equipment, ship)) continue;

        for (const auto& bonus_data : bonus_equipment.bonuses) {
            if (not matches_bonus_data(bonus_data, ship)) continue;

            if (bonus_data.bonus.has_value()) {
                const auto count = count_fit_equipment(ship, bonus_equipment, bonus_data);

                if (bonus_data.num.has_value() and count < *bonus_data.num) {
                    // 算入しない.
                } else if (bonus_data.num.has_value() or bonus_data.requires_id.has_value() or bonus_data.requires_type.has_value()) {
                    total += *bonus_data.bonus;
                } else {
                    total += *bonus_data.bonus * count;
                }
            }

            if (bonus_data.bonus_if_has_anti_air_radar.has_value() and radar.has_anti_air_radar) {
                total += *bonus_data.bonus_if_has_anti_air_radar;
            }

            if (bonus_data.bonus_if_has_accuracy_radar.has_value() and radar.has_accuracy_radar) {
                total += *bonus_data.bonus_if_has_accuracy_radar;
            }

            if (bonus_data.bonus_if_has_surface_radar.has_value() and radar.has_surface_radar) {
                total += *bonus_data.bonus_if_has_surface_radar;
            }
        }
    }

    return total;
}

}  // namespace fit_bonuses
}  // namespace kcv

#endif  // KCVERIFY_FIT_BONUSES_FIT_BONUSES_HPP_INCLUDED
