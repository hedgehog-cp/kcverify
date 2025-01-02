#ifndef KCVERIFY_FIT_BONUSES_FIT_BONUSES_HPP_INCLUDED
#define KCVERIFY_FIT_BONUSES_FIT_BONUSES_HPP_INCLUDED

// std
#include <algorithm>
#include <print>

// kcv
#include "eoen/serialization/fit_bonus/fit_bonus_data.hpp"
#include "eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "eoen/serialization/fit_bonus/fit_bonus_value.hpp"
#include "kcsapi/types/api_type.hpp"
#include "sortie_data/equipment.hpp"
#include "sortie_data/ship.hpp"
#include "sortie_data/slot.hpp"

namespace kcv {
namespace fit_bonuses {

using bonus_data      = eoen::serialization::fit_bonus::fit_bonus_data;
using bonus_equipment = eoen::serialization::fit_bonus::fit_bonus_per_equipment;
using bonus_value     = eoen::serialization::fit_bonus::fit_bonus_value;

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

constexpr auto calc_bonus(const ship& attacker, const std::vector<bonus_equipment>& bonus_list) -> bonus_value {
    auto result = bonus_value{};

    for (const auto radar = kcv::fit_bonuses::radar{attacker}; const auto& [types, ids, bonuses] : bonus_list) {
        // 計算すべきボーナスがない. 運用上あり得ない.
        // あり得ないからここで早期returnせずともいいし, emptyであるとしてもfor文を0回反復するだけ.
        // if (bonuses.empty()) [[unlikely]] {
        //     continue;
        // }

        // 装備種3(カテゴリ)で指定された装備を搭載しているかを検証.
        // 搭載していないならば, ボーナス付与なし, 次のボーナスへ.
        // もとより指定されていなければ, 無条件として通過.
        if (types.has_value()) {
            const bool has_fit_equipment = std::ranges::any_of(
                attacker.slots(),
                [&types](const std::optional<equipment>& e) -> bool {
                    if (not e.has_value()) return false;
                    const auto category = std::get<kcsapi::idx_type::category>(e->mst().api_type);
                    return std::ranges::contains(*types, category);
                },
                &slot::equipment
            );
            if (not has_fit_equipment) {
                continue;
            }
        }

        // 装備IDで指定された装備を搭載しているかを検証.
        // 搭載していないならば, ボーナス付与なし. 次のボーナスへ.
        // もとより指定されていなければ, 無条件として通過.
        if (ids.has_value()) {
            const bool has_fit_equipment = std::ranges::any_of(
                attacker.slots(),
                [&ids](const std::optional<equipment>& e) -> bool {
                    if (not e.has_value()) return false;
                    const auto id = e->mst().api_id;
                    return std::ranges::contains(*ids, id);
                },
                &slot::equipment
            );
            if (not has_fit_equipment) {
                continue;
            }
        }

        for (const auto& data : bonuses) {
            if (data.original_id.has_value() and not std::ranges::contains(*data.original_id, attacker.original_id())) {
                continue;
            }

            if (data.ship_class.has_value() and not std::ranges::contains(*data.ship_class, attacker.mst().api_ctype)) {
                continue;
            }

            if (data.nationality.has_value() and not std::ranges::contains(*data.nationality, attacker.nationality())) {
                continue;
            }

            if (data.ship_type.has_value() and not std::ranges::contains(*data.ship_type, attacker.mst().api_stype)) {
                continue;
            }

            if (data.ship_id.has_value() and not std::ranges::contains(*data.ship_id, attacker.mst().api_id)) {
                continue;
            }

            // 要求されたidの数を満たさなければボーナス付与なし.
            if (data.requires_id.has_value()) {
                const auto count = std::ranges::count_if(
                    attacker.slots(),
                    [&data](const auto& equipment) -> bool {
                        if (not equipment.has_value()) return false;
                        return std::ranges::contains(*data.requires_id, equipment->mst().api_id)
                           and (not data.requires_level.has_value() or equipment->level() >= *data.requires_level);
                    },
                    &slot::equipment
                );
                if (count < data.requires_num.value_or(1)) {
                    continue;
                }
            }

            // 要求されたcategoryの数を満たさなければボーナス付与なし.
            if (data.requires_type.has_value()) {
                const auto count = std::ranges::count_if(
                    attacker.slots(),
                    [&types = *data.requires_type](const std::optional<equipment>& e) -> bool {
                        if (not e.has_value()) return false;
                        const auto category = std::get<kcsapi::idx_type::category>(e->mst().api_type);
                        return std::ranges::contains(types, category);
                    },
                    &slot::equipment
                );
                if (count < data.requires_num_type.value_or(1)) {
                    continue;
                }
            }

            if (data.bonus.has_value()) {
                const auto count = std::ranges::count_if(
                    attacker.slots(),
                    [&](const auto& equipment) -> bool {
                        if (not equipment.has_value()) return false;

                        if (ids.has_value()) {
                            const auto id = equipment->mst().api_id;
                            if (not std::ranges::contains(*ids, id)) {
                                return false;
                            }
                        }

                        if (types.has_value()) {
                            const auto category = std::get<kcsapi::idx_type::category>(equipment->mst().api_type);
                            if (not std::ranges::contains(*types, category)) {
                                return false;
                            }
                        }

                        if (data.level.has_value()) {
                            return equipment->level() >= *data.level;
                        }

                        return true;
                    },
                    &slot::equipment
                );

                if (data.num.has_value() and *data.num > count) {
                    continue;
                }

                if (data.num.has_value() or data.requires_id.has_value() or data.requires_type.has_value()) {
                    result += *data.bonus;
                    continue;
                }

                result += (*data.bonus) * count;
            }

            if (data.air_radar.has_value() and radar.has_anti_air_radar) {
                result += *data.air_radar;
            }

            if (data.accuracy_radar.has_value() and radar.has_accuracy_radar) {
                result += *data.accuracy_radar;
            }

            if (data.surface_radar.has_value() and radar.has_surface_radar) {
                result += *data.surface_radar;
            }
        }
    }

    return result;
}

// constexpr bool matches_equipment_id_type(const bonus_equipment& bonus_equipment, const ship& attacker) {
//     const auto& [types, ids, bonuses] = bonus_equipment;

//     // 抽出すべきボーナスがない. 運用上あり得ない.
//     if (bonuses.empty()) [[unlikely]] {
//         return false;
//     }

//     // 装備種3(カテゴリ)で指定された装備を搭載しているかを検証.
//     if (types.has_value()) {
//         return std::ranges::any_of(attacker.slots(), [&types](const auto& slot) -> bool {
//             if (not slot.equipment().has_value()) return false;
//             const auto category = std::get<kcsapi::idx_type::category>(slot.equipment()->mst().api_type);
//             return std::ranges::contains(*types, category);
//         });
//     }

//     // 装備IDで指定された装備を搭載しているかを検証.
//     if (ids.has_value()) {
//         return std::ranges::any_of(attacker.slots(), [&ids](const auto& slot) -> bool {
//             if (not slot.equipment().has_value()) return false;
//             const auto id = slot.equipment()->mst().api_id;
//             return std::ranges::contains(*ids, id);
//         });
//     }

//     // 装備ボーナスを付与する装備条件なし.
//     return true;
// }

// constexpr bool matches_ship(const bonus_data& bonus_data, const ship& attacker) {
//     if (bonus_data.original_id.has_value()
//         and not std::ranges::contains(*bonus_data.original_id, attacker.original_id())) {
//         return false;
//     }

//     if (bonus_data.ship_class.has_value()
//         and not std::ranges::contains(*bonus_data.ship_class, attacker.mst().api_ctype)) {
//         return false;
//     }

//     if (bonus_data.nationality.has_value()
//         and not std::ranges::contains(*bonus_data.nationality, attacker.nationality())) {
//         return false;
//     }

//     if (bonus_data.ship_type.has_value()
//         and not std::ranges::contains(*bonus_data.ship_type, attacker.mst().api_stype)) {
//         return false;
//     }

//     if (bonus_data.ship_id.has_value() and not std::ranges::contains(*bonus_data.ship_id, attacker.mst().api_id)) {
//         return false;
//     }

//     return true;
// }

// constexpr bool matches_radar(const bonus_data& bonus_data, const radar& radar) noexcept {
//     if (bonus_data.air_radar.has_value() and not radar.has_anti_air_radar) {
//         return false;
//     }

//     if (bonus_data.surface_radar.has_value() and not radar.has_surface_radar) {
//         return false;
//     }

//     if (bonus_data.accuracy_radar.has_value() and not radar.has_accuracy_radar) {
//         return false;
//     }

//     return true;
// }

// constexpr int multiplier(
//     const bonus_data& bonus_data,                                //
//     const ship& attacker,                                        //
//     const radar& radar,                                          //
//     const std::optional<std::vector<kcsapi::category>>& types,   //
//     const std::optional<std::vector<kcsapi::equipment_id>>& ids  //
// ) {
//     if (not matches_ship(bonus_data, attacker)) {
//         return 0;
//     }

//     // if (not matches_radar(bonus_data, radar)) {
//     //     return 0;
//     // }

//     // 要求されたidの数を満たさなければボーナス付与なし.
//     if (bonus_data.requires_id.has_value()) {
//         const auto count = std::ranges::count_if(
//             attacker.slots(),
//             [&](const auto& equipment) -> bool {
//                 if (not equipment.has_value()) return false;

//                 const auto id = equipment->mst().api_id;
//                 if (not std::ranges::contains(*bonus_data.requires_id, id)) {
//                     return false;
//                 }

//                 return equipment->level() >= bonus_data.requires_level.value_or(0);
//             },
//             &slot::equipment
//         );
//         if (count < bonus_data.requires_num.value_or(1)) {
//             return 0;
//         }
//     }

//     // 要求されたcategoryの数を満たさなければボーナス付与なし.
//     if (bonus_data.requires_type.has_value()) {
//         const auto count = std::ranges::count_if(attacker.slots(), [&](const auto& slot) -> bool {
//             if (not slot.equipment().has_value()) return false;
//             const auto category = std::get<kcsapi::idx_type::category>(slot.equipment()->mst().api_type);
//             return std::ranges::contains(*bonus_data.requires_type, category);
//         });
//         if (count < bonus_data.requires_num_type.value_or(1)) {
//             return 0;
//         }
//     }

//     const auto count = std::ranges::count_if(
//         attacker.slots(),
//         [&](const auto& equipment) -> bool {
//             if (not equipment.has_value()) return false;

//             if (ids.has_value()) {
//                 const auto id = equipment->mst().api_id;
//                 if (not std::ranges::contains(*ids, id)) {
//                     return false;
//                 }
//             }

//             if (types.has_value()) {
//                 const auto category = std::get<kcsapi::idx_type::category>(equipment->mst().api_type);
//                 if (not std::ranges::contains(*types, category)) {
//                     return false;
//                 }
//             }

//             if (bonus_data.level.has_value()) {
//                 return equipment->level() >= *bonus_data.level;
//             }

//             return true;
//         },
//         &slot::equipment
//     );

//     if (bonus_data.num.has_value() and *bonus_data.num > count) {
//         return 0;
//     }

//     if (bonus_data.num.has_value() or bonus_data.requires_id.has_value() or bonus_data.requires_type.has_value()) {
//         return 1;
//     }

//     // いわゆるシナジー. 1限.
//     if (bonus_data.requires_id.has_value() or bonus_data.requires_type.has_value()) {
//         return 1;
//     }

//     return count;
// }

// constexpr auto extract_bonuses(const ship& attacker, const std::vector<bonus_equipment>& bonuses)
//     -> kcv::ranges::range_of<std::tuple<const bonus_value&, int>> auto  //
// {
//     const auto radar = kcv::fit_bonuses::radar{attacker};
//     return bonuses
//          | std::ranges::views::filter([&](const auto& e) -> bool { return matches_equipment_id_type(e, attacker); })
//          | std::ranges::views::transform([&](const auto& e) {
//                const auto& [types, ids, bonuses] = e;
//                return bonuses  //
//                     | std::ranges::views::filter([](const auto& e) -> bool { return e.bonus.has_value(); })
//                     | std::ranges::views::transform([&](const auto& e) -> std::tuple<const bonus_value&, int> {
//                           return {
//                               *e.bonus,
//                               multiplier(e, attacker, radar, types, ids),
//                           };
//                       });
//            })
//          | std::ranges::views::join;
// }

}  // namespace fit_bonuses
}  // namespace kcv

#endif  // KCVERIFY_FIT_BONUSES_FIT_BONUSES_HPP_INCLUDED
