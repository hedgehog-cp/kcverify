#include "core/battlelog/equipment_bonus.hpp"

// std
#include <algorithm>
#include <functional>
#include <optional>
#include <stdexcept>
#include <vector>

// kcv
#include "core/battlelog/equipment.hpp"
#include "core/battlelog/ship.hpp"
#include "core/constants/equipment.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_data.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_value.hpp"
#include "models/kc3kai/mst_slotitem_bonus.hpp"
#include "models/kcsapi/types/api_type.hpp"
#include "models/kcsapi/types/enum/category.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"

// MARK: eoen

namespace {

/// @brief 装備ボーナスのベースとなる装備を抽出する.
auto extract_fit_equipments(const kcv::ship& ship, const std::optional<std::vector<kcv::kcsapi::category>>& types)
    -> std::vector<std::reference_wrapper<const kcv::equipment>> {
    auto fit_equipments = std::vector<std::reference_wrapper<const kcv::equipment>>{};
    for (const auto& slot : ship.slots()) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            const auto& type = std::get<kcv::kcsapi::idx_type::category>(e->mst().api_type);
            if (std::ranges::contains(*types, type)) {
                fit_equipments.push_back(*e);
            }
        }
    }
    return fit_equipments;
}

/// @brief 装備ボーナスのベースとなる装備を抽出する.
auto extract_fit_equipments(const kcv::ship& ship, const std::optional<std::vector<kcv::kcsapi::equipment_id>>& ids)
    -> std::vector<std::reference_wrapper<const kcv::equipment>> {
    auto fit_equipments = std::vector<std::reference_wrapper<const kcv::equipment>>{};
    for (const auto& slot : ship.slots()) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            const auto& id = e->mst().api_id;
            if (std::ranges::contains(*ids, id)) {
                fit_equipments.push_back(*e);
            }
        }
    }
    return fit_equipments;
}

/// @brief 装備ボーナスのベースとなる装備を抽出する.
auto extract_fit_equipments(
    const kcv::ship& ship,
    const std::optional<std::vector<kcv::kcsapi::category>>& types,
    const std::optional<std::vector<kcv::kcsapi::equipment_id>>& ids
) -> std::vector<std::reference_wrapper<const kcv::equipment>> {
    if (types.has_value() xor ids.has_value()) [[likely]] {
        if (types.has_value()) {
            return extract_fit_equipments(ship, types);
        }

        if (ids.has_value()) {
            return extract_fit_equipments(ship, ids);
        }
    }

    throw std::invalid_argument{"unexpected `bonus_list`"};
}

/// @brief 指定された艦船の条件を全て満たしているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
bool matches_ship(const kcv::ship& ship, const kcv::eoen::serialization::fit_bonus::fit_bonus_data& data) {
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
bool matches_requires_id(const kcv::ship& ship, const kcv::eoen::serialization::fit_bonus::fit_bonus_data& data) {
    if (not data.requires_id.has_value()) {
        return true;
    }

    // count_if
    int count = 0;
    for (const auto& slot : ship.slots()) {
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
bool matches_requires_type(const kcv::ship& ship, const kcv::eoen::serialization::fit_bonus::fit_bonus_data& data) {
    if (not data.requires_type.has_value()) {
        return true;
    }

    // count_if
    int count = 0;
    for (const auto& slot : ship.slots()) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            const auto& type = std::get<kcv::kcsapi::idx_type::category>(e->mst().api_type);
            if (std::ranges::contains(*data.requires_type, type)) {
                count++;
            }
        }
    }

    return count >= data.requires_num_type.value_or(1);
}

/// @brief 指定された条件を全て満たしているかを検証する.
/// 満たしていないならば, ボーナス付与なし. 次のボーナスへ.
/// もとより指定されていなければ, 無条件として通過する.
bool matches_data(const kcv::ship& ship, const kcv::eoen::serialization::fit_bonus::fit_bonus_data& data) {
    return matches_ship(ship, data) and matches_requires_id(ship, data) and matches_requires_type(ship, data);
}

/// @brief 指定した改修値以上の装備の個数を数え上げ, これを返す.
int count_if(const std::vector<std::reference_wrapper<const kcv::equipment>>& fit_equipments, std::int32_t level) {
    int count = 0;
    for (const auto& e : fit_equipments) {
        if (e.get().level() >= level) {
            count++;
        }
    }
    return count;
}

}  // namespace

auto kcv::get_equipment_bonus(
    const kcv::ship& ship,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& bonus_list
) -> kcv::eoen::serialization::fit_bonus::fit_bonus_value {
    auto total = kcv::eoen::serialization::fit_bonus::fit_bonus_value{};

    const bool has_anti_air_radar = kcv::has_equipment_if(ship.slots(), kcv::is_anti_air_radar);
    const bool has_surface_radar  = kcv::has_equipment_if(ship.slots(), kcv::is_surface_radar);
    const bool has_accuracy_radar = kcv::has_equipment_if(ship.slots(), kcv::is_accuracy_radar);

    for (const auto& [types, ids, bonuses] : bonus_list) {
        const auto fit_equipments = extract_fit_equipments(ship, types, ids);
        if (fit_equipments.empty()) {
            continue;
        }

        for (const auto& data : bonuses) {
            if (not matches_data(ship, data)) {
                continue;
            }

            if (data.bonus.has_value()) {
                const int num = data.level.has_value() ? count_if(fit_equipments, *data.level) : fit_equipments.size();
                if (data.num.has_value()) {
                    if (num >= *data.num) {
                        total += *data.bonus;
                    }
                } else {
                    total += *data.bonus * num;
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

// MARK: kc3kai

namespace {

bool matches_ship(const kcv::ship& ship, const kcv::kc3kai::bonus_data& data) {
    if (data.ship_base.has_value() and not std::ranges::contains(*data.ship_base, ship.base_id())) {
        return false;
    }

    if (data.ship_class.has_value() and not std::ranges::contains(*data.ship_class, ship.mst().api_ctype)) {
        return false;
    }

    if (data.ship_country.has_value() and not std::ranges::contains(*data.ship_country, ship.nationality())) {
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

bool matches_requires_id(const kcv::ship& ship, const kcv::kc3kai::bonus_data& data) {
    if (not data.requires_id.has_value()) {
        return true;
    }

    int count = 0;
    for (const auto& slot : ship.slots()) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            const auto& id = e->mst().api_id;
            if (std::ranges::contains(*data.requires_id, id) and e->level() >= data.requires_id_level) {
                count++;
            }
        }
    }

    return count >= data.requires_id_num.value_or(1);
}

bool matches_requires_type(const kcv::ship& ship, const kcv::kc3kai::bonus_data& data) {
    if (not data.requires_type.has_value()) {
        return true;
    }

    int count = 0;
    for (const auto& slot : ship.slots()) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            const auto& type = std::get<kcv::kcsapi::category>(e->mst().api_type);
            if (std::ranges::contains(*data.requires_type, type)) {
                count++;
            }
        }
    }

    return count >= data.requires_type_num.value_or(1);
}

bool matches_data(
    const kcv::ship& ship,
    bool has_anti_air_radar,
    bool has_surface_radar,
    bool has_accuracy_radar,
    const kcv::kc3kai::bonus_data& data
) {
    if (data.requires_anti_air_radar.has_value() and not has_anti_air_radar) {
        return false;
    }

    if (data.requires_surface_radar.has_value() and not has_surface_radar) {
        return false;
    }

    if (data.requires_accuracy_radar.has_value() and not has_accuracy_radar) {
        return false;
    }

    if (not matches_ship(ship, data)) {
        return false;
    }

    if (not matches_requires_id(ship, data)) {
        return false;
    }

    if (not matches_requires_type(ship, data)) {
        return false;
    }

    return true;
}

}  // namespace

auto kcv::get_equipment_bonus(const kcv::ship& ship, const std::vector<kcv::kc3kai::mst_slotitem_bonus>& bonus_list)
    -> kcv::kc3kai::bonus_value {
    auto total = kcv::kc3kai::bonus_value{};

    const bool has_anti_air_radar = kcv::has_equipment_if(ship.slots(), kcv::is_anti_air_radar);
    const bool has_surface_radar  = kcv::has_equipment_if(ship.slots(), kcv::is_surface_radar);
    const bool has_accuracy_radar = kcv::has_equipment_if(ship.slots(), kcv::is_accuracy_radar);

    for (const auto& [types, ids, bonuses] : bonus_list) {
        const auto fit_equipments = extract_fit_equipments(ship, types, ids);
        if (fit_equipments.empty()) {
            continue;
        }

        for (const auto& data : bonuses) {
            if (not matches_data(ship, has_anti_air_radar, has_surface_radar, has_accuracy_radar, data)) {
                continue;
            }

            const int num = data.level.has_value() ? count_if(fit_equipments, *data.level) : fit_equipments.size();
            if (data.num.has_value()) {
                if (num >= *data.num) {
                    total += data.bonus;
                }
            } else {
                total += data.bonus * num;
            }
        }
    }

    return total;
}