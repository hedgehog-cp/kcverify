#include "equipment_bonus.hpp"

// std
#include <algorithm>
#include <concepts>
#include <optional>

// kcv
#include "core/constants/equipment.hpp"
#include "core/sortie/entities/equipment.hpp"
#include "core/sortie/entities/ship.hpp"
#include "core/sortie/entities/slot.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_data.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_value.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/api_type.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"

namespace {

/// @brief 述語関数を満たす電探を搭載しているかを検証する.
constexpr bool has_radar(
    const kcv::sortie::ship& ship,                                                        //
    const std::predicate<const kcv::kcsapi::api_mst_slotitem::value_type&> auto is_radar  //
) {
    // any_of
    for (const auto& slots = ship.slots(); const auto& slot : slots) {
        if (const auto& e = slot.equipment(); e.has_value() and is_radar(e->mst())) {
            return true;
        }
    }
    return false;
}

/// @brief 装備種3(カテゴリ)で指定された装備を搭載しているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_equipment(
    const kcv::sortie::ship& ship,                                       //
    const std::optional<std::vector<kcv::kcsapi::category>>& categories  //
) {
    if (not categories.has_value()) {
        return false;
    }

    // any_of
    for (const auto& slots = ship.slots(); const auto& slot : slots) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            const auto category = std::get<kcv::kcsapi::idx_type::category>(e->mst().api_type);
            if (std::ranges::contains(*categories, category)) {
                return true;
            }
        }
    }
    return false;
}

/// @brief 装備IDで指定された装備を搭載しているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_equipment(
    const kcv::sortie::ship& ship,                                    //
    const std::optional<std::vector<kcv::kcsapi::equipment_id>>& ids  //
) {
    if (not ids.has_value()) {
        return false;
    }

    // any_of
    for (const auto& slots = ship.slots(); const auto& slot : slots) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            const auto id = e->mst().api_id;
            if (std::ranges::contains(*ids, id)) {
                return true;
            }
        }
    }
    return false;
}

/// @brief 指定された装備を搭載しているかを検証する.
/// 搭載していないならば, ボーナス付与なし. 次のボーナスへ.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_per_equipment(
    const kcv::sortie::ship& ship,                                                     //
    const kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment& per_equipment  //
) {
    const auto& [categories, ids, _] = per_equipment;
    return matches_equipment(ship, categories) or matches_equipment(ship, ids);
}

/// @brief 指定された艦娘の条件を満たしているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_ship(
    const kcv::sortie::ship& ship,                                   //
    const kcv::eoen::serialization::fit_bonus::fit_bonus_data& data  //
) {
    // clang-format off

    return (not data.original_id.has_value() or std::ranges::contains(*data.original_id, ship.base_id()))
       and (not data.ship_class.has_value()  or std::ranges::contains(*data.ship_class,  ship.mst().api_ctype))
       and (not data.nationality.has_value() or std::ranges::contains(*data.nationality, ship.nationality()))
       and (not data.ship_type.has_value()   or std::ranges::contains(*data.ship_type,   ship.mst().api_stype))
       and (not data.ship_id.has_value()     or std::ranges::contains(*data.ship_id,     ship.mst().api_id));

    // clang-format on
}

/// @brief 指定された装備の条件を満たしているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_required_id(
    const kcv::sortie::ship& ship,                                   //
    const kcv::eoen::serialization::fit_bonus::fit_bonus_data& data  //
) {
    if (not data.requires_id.has_value()) {
        return true;
    }

    // count_if
    int count = 0;
    for (const auto& slots = ship.slots(); const auto& slot : slots) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            if (data.requires_level <= e->level() and std::ranges::contains(*data.requires_id, e->mst().api_id)) {
                count++;
            }
        }
    }

    return count >= data.requires_num.value_or(1);
}

/// @brief 指定された装備の条件を満たしているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_required_category(
    const kcv::sortie::ship& ship,                                   //
    const kcv::eoen::serialization::fit_bonus::fit_bonus_data& data  //
) {
    if (not data.requires_type.has_value()) {
        return true;
    }

    // count_if
    int count = 0;
    for (const auto& slots = ship.slots(); const auto& slot : slots) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            const auto category = std::get<kcv::kcsapi::idx_type::category>(e->mst().api_type);
            if (std::ranges::contains(*data.requires_type, category)) {
                count++;
            }
        }
    }

    return count >= data.requires_num_type.value_or(1);
}

/// @brief 指定された条件を満たしているかを検証する.
/// 満たしていないならば, ボーナス付与なし. 次のボーナスへ.
/// もとより指定されていなければ, 無条件として通過する.
constexpr bool matches_data(
    const kcv::sortie::ship& ship,                                   //
    const kcv::eoen::serialization::fit_bonus::fit_bonus_data& data  //
) {
    return matches_ship(ship, data) and matches_required_id(ship, data) and matches_required_category(ship, data);
}

/// @brief 指定された条件を満たす装備の搭載数を数え上げる.
constexpr int count_fit_equipment(
    const kcv::sortie::ship& ship,                                                      //
    const kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment& per_equipment,  //
    const kcv::eoen::serialization::fit_bonus::fit_bonus_data& data                     //
) {
    const auto& [categories, ids, _] = per_equipment;

    int count = 0;
    for (const auto& slots = ship.slots(); const auto& slot : slots) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            const auto id         = e->mst().api_id;
            const bool matches_id = ids.has_value() and std::ranges::contains(*ids, id);

            const auto category         = std::get<kcv::kcsapi::idx_type::category>(e->mst().api_type);
            const bool matches_category = categories.has_value() and std::ranges::contains(*categories, category);

            if ((matches_id or matches_category) and e->level() >= data.level) {
                count++;
            }
        }
    }

    return count;
}

}  // namespace

auto kcv::get_equipment_bonus(
    const kcv::sortie::ship& ship,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& bonus_object
) -> kcv::eoen::serialization::fit_bonus::fit_bonus_value {
    auto total = kcv::eoen::serialization::fit_bonus::fit_bonus_value{};

    const bool has_anti_air_radar = has_radar(ship, &kcv::is_anti_air_radar);
    const bool has_surface_radar  = has_radar(ship, &kcv::is_surface_radar);
    const bool has_accuracy_radar = has_radar(ship, &kcv::is_accuracy_radar);

    for (const auto& per_equipment : bonus_object) {
        if (not matches_per_equipment(ship, per_equipment)) {
            continue;
        }

        for (const auto& data : per_equipment.bonuses) {
            if (not matches_data(ship, data)) {
                continue;
            }

            if (data.bonus.has_value()) {
                const int count = count_fit_equipment(ship, per_equipment, data);

                if (count == 0 or (data.num.has_value() and count < *data.num)) {
                    // 算入しない
                } else if (data.requires_id.has_value() and not data.requires_num.has_value()) {
                    total += *data.bonus * count;
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