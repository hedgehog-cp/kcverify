#include "core/battlelog/equipment_bonus.hpp"

// std
#include <algorithm>
#include <concepts>
#include <memory>
#include <optional>
#include <vector>

// kcv
#include "core/attributes/equipment.hpp"
#include "core/constants/constants.hpp"
#include "core/entity/equipment.hpp"
#include "core/entity/ship.hpp"
#include "core/entity/slot.hpp"
#include "extensions/exception.hpp"
#include "extensions/inplace_vector.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_data.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_value.hpp"
#include "models/kc3kai/mst_slotitem_bonus.hpp"
#include "models/kcsapi/types/api_type.hpp"
#include "models/kcsapi/types/enum/category.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"

// MARK: 共通

namespace {

/// @brief 装備ボーナスのベースとなる装備を抽出する.
void append_fit_equipments(
    kcv::inplace_vector<const kcv::equipment*, kcv::max_slot_size>& fit_equipments,
    const kcv::ship& ship,
    const std::optional<std::vector<kcv::kcsapi::category>>& types
) {
    for (const auto& slot : ship.slots()) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            const auto type = std::get<kcv::kcsapi::idx_type::category>(e->mst().api_type);
            if (std::ranges::contains(*types, type)) {
                fit_equipments.push_back(std::to_address(e));
            }
        }
    }
}

/// @brief 装備ボーナスのベースとなる装備を抽出する.
void append_fit_equipments(
    kcv::inplace_vector<const kcv::equipment*, kcv::max_slot_size>& fit_equipments,
    const kcv::ship& ship,
    const std::optional<std::vector<kcv::kcsapi::equipment_id>>& ids
) {
    for (const auto& slot : ship.slots()) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            const auto id = e->mst().api_id;
            if (std::ranges::contains(*ids, id)) {
                fit_equipments.push_back(std::to_address(e));
            }
        }
    }
}

/// @brief 装備ボーナスのベースとなる装備を抽出する.
void append_fit_equipments(
    kcv::inplace_vector<const kcv::equipment*, kcv::max_slot_size>& fit_equipments,
    const kcv::ship& ship,
    const std::optional<std::vector<kcv::kcsapi::category>>& types,
    const std::optional<std::vector<kcv::kcsapi::equipment_id>>& ids
) {
    if (types.has_value() xor ids.has_value()) [[likely]] {
        if (types.has_value()) {
            append_fit_equipments(fit_equipments, ship, types);
            return;
        }

        if (ids.has_value()) {
            append_fit_equipments(fit_equipments, ship, ids);
            return;
        }
    }

    throw kcv::exception{"unexpected `fit_bonuses`."};
}

/// @brief 指定した改修値以上の装備の個数を数え上げ, これを返す.
int count_if(const kcv::inplace_vector<const kcv::equipment*, kcv::max_slot_size>& fit_equipments, std::int32_t level) {
    int count = 0;
    for (const auto& e : fit_equipments) {
        if (e->level() >= level) {
            count++;
        }
    }
    return count;
}

/// @brief 条件を満たす装備を搭載しているかを検証する.
/// 増設スロットを含まない装備スロットを対象に呼び出したい場合が存在するため, `slots`を引数にとる.
/// @param slots 装備スロット.
/// @param pred 装備マスタを引数にとる単項述語関数.
/// @todo この関数を大域に移動する.
bool contains_matching_equipment(
    const kcv::ranges::range_of<kcv::slot> auto& slots,
    const std::predicate<const kcv::kcsapi::api_mst_slotitem_value_t&> auto& pred
) {
    for (const auto& slot : slots) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            if (pred(e->mst())) {
                return true;
            }
        }
    }
    return false;
}

/// @brief 装備ボーナス型に対して各メンバごとの複合代入演算子を提供する.
/// @tparam T 装備ボーナス型.
template <typename T>
auto operator+=(T& lhs, const T& rhs) noexcept -> T& {
    lhs.houg += rhs.houg;
    lhs.tyku += rhs.tyku;
    lhs.kaih += rhs.kaih;
    lhs.souk += rhs.souk;
    lhs.houm += rhs.houm;
    lhs.tais += rhs.tais;
    lhs.raig += rhs.raig;
    lhs.saku += rhs.saku;
    lhs.leng += rhs.leng;
    lhs.baku += rhs.baku;
    return lhs;
}

/// @brief 装備ボーナス型に対して各メンバごとの乗算演算子を提供する.
/// @tparam T 装備ボーナス型.
template <typename T>
auto operator*(const T& lhs, std::integral auto rhs) noexcept -> T {
    return T{
        .houg = lhs.houg * rhs,
        .tyku = lhs.tyku * rhs,
        .kaih = lhs.kaih * rhs,
        .souk = lhs.souk * rhs,
        .houm = lhs.houm * rhs,
        .tais = lhs.tais * rhs,
        .raig = lhs.raig * rhs,
        .saku = lhs.saku * rhs,
        .leng = lhs.leng * rhs,
        .baku = lhs.baku * rhs,
    };
}

}  // namespace

// MARK: eoen

namespace {

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
            const auto type = std::get<kcv::kcsapi::idx_type::category>(e->mst().api_type);
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

}  // namespace

auto kcv::total_equipment_bonus(
    const kcv::ship& ship,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses
) -> kcv::eoen::serialization::fit_bonus::fit_bonus_value {
    auto total = kcv::eoen::serialization::fit_bonus::fit_bonus_value{};

    const bool has_anti_air_radar = contains_matching_equipment(ship.slots(), kcv::is_anti_air_radar);
    const bool has_surface_radar  = contains_matching_equipment(ship.slots(), kcv::is_surface_radar);
    const bool has_accuracy_radar = contains_matching_equipment(ship.slots(), kcv::is_accuracy_radar);

    for (const auto& [types, ids, bonuses] : fit_bonuses) {
        auto fit_equipments = kcv::inplace_vector<const kcv::equipment*, kcv::max_slot_size>{};
        append_fit_equipments(fit_equipments, ship, types, ids);
        if (fit_equipments.empty()) {
            continue;
        }

        for (const auto& data : bonuses) {
            if (not matches_data(ship, data)) {
                continue;
            }

            if (data.bonus.has_value()) {
                // 改修値指定による個数指定または個数指定があるならばそれに従い, なければ比例.
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

/// @brief 指定された艦船の条件を全て満たしているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
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

/// @brief 指定された装備の条件を満たしているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
bool matches_requires_id(const kcv::ship& ship, const kcv::kc3kai::bonus_data& data) {
    if (not data.requires_id.has_value()) {
        return true;
    }

    // count_if
    int count = 0;
    for (const auto& slot : ship.slots()) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            const auto id = e->mst().api_id;
            if (std::ranges::contains(*data.requires_id, id) and e->level() >= data.requires_id_level) {
                count++;
            }
        }
    }

    return count >= data.requires_id_num.value_or(1);
}

/// @brief 指定された装備の条件を満たしているかを検証する.
/// もとより指定されていなければ, 無条件として通過する.
bool matches_requires_type(const kcv::ship& ship, const kcv::kc3kai::bonus_data& data) {
    if (not data.requires_type.has_value()) {
        return true;
    }

    // count_if
    int count = 0;
    for (const auto& slot : ship.slots()) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            const auto type = std::get<kcv::kcsapi::category>(e->mst().api_type);
            if (std::ranges::contains(*data.requires_type, type)) {
                count++;
            }
        }
    }

    return count >= data.requires_type_num.value_or(1);
}

/// @brief 指定された条件を全て満たしているかを検証する.
/// 満たしていないならば, ボーナス付与なし. 次のボーナスへ.
/// もとより指定されていなければ, 無条件として通過する.
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

auto kcv::total_equipment_bonus(const kcv::ship& ship, const std::vector<kcv::kc3kai::mst_slotitem_bonus>& fit_bonuses)
    -> kcv::kc3kai::bonus_value {
    auto total = kcv::kc3kai::bonus_value{};

    const bool has_anti_air_radar = contains_matching_equipment(ship.slots(), kcv::is_anti_air_radar);
    const bool has_surface_radar  = contains_matching_equipment(ship.slots(), kcv::is_surface_radar);
    const bool has_accuracy_radar = contains_matching_equipment(ship.slots(), kcv::is_accuracy_radar);

    for (const auto& [types, ids, bonuses] : fit_bonuses) {
        auto fit_equipments = kcv::inplace_vector<const kcv::equipment*, kcv::max_slot_size>{};
        append_fit_equipments(fit_equipments, ship, types, ids);
        if (fit_equipments.empty()) {
            continue;
        }

        for (const auto& data : bonuses) {
            if (not matches_data(ship, has_anti_air_radar, has_surface_radar, has_accuracy_radar, data)) {
                continue;
            }

            // 改修値指定による個数指定または個数指定があるならばそれに従い, なければ比例.
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