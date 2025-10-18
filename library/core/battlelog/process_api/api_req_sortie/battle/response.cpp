#include "core/battlelog/process_api.hpp"

// std
#include <cassert>
#include <cmath>
#include <cstddef>
#include <optional>
#include <print>
#include <ranges>
#include <utility>
#include <vector>

// kcv
#include "core/battlelog/battlelog.hpp"
#include "core/battlelog/process_api/common.hpp"
#include "core/entity/equipment.hpp"
#include "core/entity/fleet_data.hpp"
#include "core/entity/ship.hpp"
#include "core/entity/slot.hpp"
#include "core/utility/kcsapi.hpp"
#include "extensions/exception.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/kcsapi/api_req_sortie/battle/response.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/api_air_base_attack.hpp"
#include "models/kcsapi/types/api_air_base_injection.hpp"
#include "models/kcsapi/types/api_hougeki1.hpp"
#include "models/kcsapi/types/api_injection_kouku.hpp"
#include "models/kcsapi/types/api_kouku.hpp"
#include "models/kcsapi/types/api_raigeki.hpp"
#include "models/kcsapi/types/api_support_info.hpp"
#include "models/kcsapi/types/enum/day_attack_kind.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"
#include "models/kcsapi/types/enum/fleet_flag.hpp"
#include "models/kcsapi/types/enum/nationality.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"
#include "models/kcsapi/types/enum/support_type.hpp"
#include "models/kcsapi/types/svdata.hpp"

namespace {

/// @brief 状況開始.
void initialize_situation(kcv::battlelog& current, const kcv::kcsapi::api_req_sortie::battle::response& data) {
    current.x_al01            = data.api_x_al01;
    current.balloon_cell      = data.api_balloon_cell;
    current.atoll_cell        = data.api_atoll_cell;
    current.girls_formation   = std::get<0>(data.api_formation);
    current.abyssal_formation = std::get<1>(data.api_formation);
    current.engagement        = std::get<2>(data.api_formation);
}

/// @brief 深海棲艦の艦隊データを更新する. 艦隊名はこのAPIに存在しないないため未設定.
void initialize_abyssal_fleet_data(
    kcv::battlelog& current,
    const kcv::kcsapi::api_req_sortie::battle::response& data,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) {
    auto ships = std::vector<kcv::ship>{};

    const std::ranges::random_access_range auto zip_enemy_ships = std::ranges::views::zip(
        data.api_ship_ke,   //
        data.api_ship_lv,   //
        data.api_e_maxhps,  //
        data.api_e_nowhps,  //
        data.api_eParam,    //
        data.api_eSlot      //
    );
    ships.reserve(zip_enemy_ships.size());
    for (const auto& [ship_ke, ship_lv, maxhp, nowhp, param, slot] : zip_enemy_ships) {
        const auto& mst    = kcv::find_mst(api_mst_ship, ship_ke);
        const auto base_id = kcv::kcsapi::ship_id{};
        const auto exslot  = std::nullopt;
        const auto slots   = slot  //
                         | std::ranges::views::transform([&](const auto& id) -> std::optional<kcv::equipment> {
                               if (id == kcv::kcsapi::equipment_id::invalid) {
                                   return std::nullopt;
                               }
                               const auto& mst           = kcv::find_mst(api_mst_slotitem, id);
                               const auto level          = 0;
                               const auto aircraft_level = 0;
                               return kcv::equipment{mst, level, aircraft_level};
                           })
                         | std::ranges::views::transform([](const auto& equipment) -> kcv::slot {
                               const auto current = 0;
                               const auto max     = 0;
                               return kcv::slot{current, max, std::move(equipment)};
                           })
                         | std::ranges::to<std::vector>();
        const auto hp = kcv::to_integer(nowhp).value();

        /// TODO: maxhp, paramを使う.
        ships.emplace_back(mst, base_id, kcv::kcsapi::nationality::abyssal, std::move(slots), exslot, hp);
    }

    // battleresultに敵艦隊名が存在するため, ここでは設定できない.
    const auto deck_name = kcv::uninitialized_enemy_fleet_name_tag;
    const auto fleets    = std::vector<std::optional<kcv::fleet>>{
        std::make_optional<kcv::fleet>(deck_name, std::move(ships)),
    };

    const auto fleet_id              = 1;                             // 第1艦隊
    const auto node_support_fleet_id = 0;                             // 道中支援なし
    const auto boss_support_fleet_id = 0;                             // 決戦支援なし
    const auto combined_flag         = 0;                             // 通常艦隊
    const auto air_base              = std::vector<kcv::air_base>{};  // 基地航空隊なし

    current.abyssal_fleet_data = kcv::fleet_data{
        fleet_id, node_support_fleet_id, boss_support_fleet_id, combined_flag, std::move(fleets), std::move(air_base),
    };
}

/// @brief 基地航空隊噴式強襲のデータをもって戦闘ログを更新する.
/// 基地航空隊の各中隊の詳細な彼我の撃墜状況はこのAPIに存在しないため, 艦船のダメージのみ更新する.
void update(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::api_air_base_injection& data
) {
    if (data.api_stage3.has_value()) {
        const auto abyssal = std::ranges::views::zip(
            data.api_stage3->api_edam,                                 //
            current.abyssal_fleet_data.fleets().at(0).value().ships()  //
        );
        for (auto&& [dam, defender] : abyssal) {
            defender.hp(defender.hp() - kcv::unprotected_damage(dam));
        }
    }

    if (data.api_stage3_combined.has_value()) {
        throw kcv::exception{"unexpected data."};
    }
}

/// @brief 噴式強襲のデータをもって戦闘ログを更新する.
void update(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::api_injection_kouku& data
) {
    if (data.api_stage3.has_value()) {
        if (data.api_stage3->api_fdam.has_value()) {
            const auto girls = std::ranges::views::zip(
                *data.api_stage3->api_fdam,                                                                    //
                current.girls_fleet_data.fleets().at(current.girls_fleet_data.fleet_id() - 1).value().ships()  //
            );

            for (const auto& [dam, defender] : girls) {
                defender.hp(defender.hp() - kcv::unprotected_damage(dam));
            }
        }

        {
            const auto abyssal = std::ranges::views::zip(
                data.api_stage3->api_edam,                          //
                current.abyssal_fleet_data.fleets().at(0)->ships()  //
            );

            for (const auto& [dam, defender] : abyssal) {
                defender.hp(defender.hp() - kcv::unprotected_damage(dam));
            }
        }
    }
}

/// @brief 基地航空隊攻撃のデータをもって戦闘ログを更新する.
void update(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::api_air_base_attack& data
) {
    for (const auto& datum : data) {
        if (datum.api_stage3.has_value()) {
            if (datum.api_stage3->api_fdam.has_value()) {
                const auto girls = std::ranges::views::zip(
                    *datum.api_stage3->api_fdam,                                                            //
                    current.girls_fleet_data.fleets().at(current.girls_fleet_data.fleet_id() - 1)->ships()  //
                );

                for (const auto& [dam, defender] : girls) {
                    defender.hp(defender.hp() - kcv::unprotected_damage(dam));
                }
            }

            {
                const auto abyssal = std::ranges::views::zip(
                    datum.api_stage3->api_edam,                         //
                    current.abyssal_fleet_data.fleets().at(0)->ships()  //
                );

                for (const auto& [dam, defender] : abyssal) {
                    defender.hp(defender.hp() - kcv::unprotected_damage(dam));
                }
            }
        }

        if (datum.api_stage3_combined.has_value()) {
            throw kcv::exception{"unexpected data."};
        }
    }
}

/// @brief 友軍艦隊航空攻撃または航空戦のデータをもって戦闘ログを更新する.
void update(std::vector<kcv::battlelog>& battlelogs, kcv::battlelog& current, const kcv::kcsapi::api_kouku& data) {
    if (data.api_stage3.has_value()) {
        if (data.api_stage3->api_fdam.has_value()) {
            const auto girls = std::ranges::views::zip(
                *data.api_stage3->api_fdam,                                                                    //
                current.girls_fleet_data.fleets().at(current.girls_fleet_data.fleet_id() - 1).value().ships()  //
            );

            for (const auto& [dam, defender] : girls) {
                defender.hp(defender.hp() - kcv::unprotected_damage(dam));
            }
        }

        {
            const auto abyssal = std::ranges::views::zip(
                data.api_stage3->api_edam,                          //
                current.abyssal_fleet_data.fleets().at(0)->ships()  //
            );

            for (const auto& [dam, defender] : abyssal) {
                defender.hp(defender.hp() - kcv::unprotected_damage(dam));
            }
        }
    }
}

/// @brief 支援艦隊攻撃をもって戦闘ログを更新する.
/// 型未実装.
void update(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    kcv::kcsapi::support_type flag,
    const kcv::kcsapi::api_support_info& info
) {
    if (flag == kcv::kcsapi::support_type::aerial or flag == kcv::kcsapi::support_type::anti_submarine) {
        if (info.api_support_airatack.has_value()) {
            const auto& data = *info.api_support_airatack;

            if (data.api_stage3.has_value()) {
                if (data.api_stage3->api_fdam.has_value()) {
                    const auto girls = std::ranges::views::zip(
                        *data.api_stage3->api_fdam,
                        current.girls_fleet_data.fleets().at(current.girls_fleet_data.fleet_id() - 1).value().ships()
                    );

                    for (const auto& [dam, defender] : girls) {
                        defender.hp(defender.hp() - kcv::unprotected_damage(dam));
                    }
                }

                {
                    const auto abyssal = std::ranges::views::zip(
                        data.api_stage3->api_edam,                                 //
                        current.abyssal_fleet_data.fleets().at(0).value().ships()  //
                    );

                    for (const auto& [dam, defender] : abyssal) {
                        defender.hp(defender.hp() - kcv::unprotected_damage(dam));
                    }
                }
            }
        }
    }
    if (flag == kcv::kcsapi::support_type::shelling or flag == kcv::kcsapi::support_type::torpedo) {
        if (info.api_support_hourai.has_value()) {
            const auto& data = *info.api_support_hourai;

            // 7隻存在しない場合に境界外アクセスしないようにするため.
            const std::ranges::random_access_range auto zip = std::ranges::views::zip(
                data.api_damage,                                           //
                current.abyssal_fleet_data.fleets().at(0).value().ships()  //
            );
            for (const auto& [damage, defender] : zip) {
                defender.hp(defender.hp() - kcv::unprotected_damage(damage));
            }
        }
    }
}

/// @brief 先制対潜攻撃をもって戦闘ログを更新する.
void update(std::vector<kcv::battlelog>& battlelogs, kcv::battlelog& current, const kcv::kcsapi::api_hougeki1& data) {
    const std::ranges::random_access_range auto zip = std::ranges::views::zip(
        data.api_at_eflag,        //
        data.api_at_list,         //
        data.api_at_type,         //
        data.api_cl_list,         //
        data.api_damage,          //
        data.api_df_list,         //
        data.api_si_list.value()  //
    );
    for (const auto& [at_eflag, at_list, at_type, cl_list, damage, df_list, si_list] : zip) {
        const auto attack             = std::ranges::views::zip(cl_list, damage, df_list);
        const auto attacker_fleet     = at_eflag == kcv::kcsapi::fleet_flag::player  //
                                          ? static_cast<std::size_t>(current.girls_fleet_data.fleet_id() - 1)
                                          : 0uz;
        const auto defender_fleet     = at_eflag == kcv::kcsapi::fleet_flag::player  //
                                          ? 0uz
                                          : static_cast<std::size_t>(current.girls_fleet_data.fleet_id() - 1);
        const auto display_equipments = si_list  //
                                      | std::ranges::views::transform(&kcv::to_equipment_id)
                                      | std::ranges::to<std::vector>();
        for (const auto& [cl, dam, df] : attack) {
            battlelogs.push_back(kcv::battlelog{
                .world              = current.world,
                .map                = current.map,
                .cell               = current.cell,
                .x_al01             = current.x_al01,
                .balloon_cell       = current.balloon_cell,
                .atoll_cell         = current.atoll_cell,
                .girls_fleet_data   = current.girls_fleet_data,
                .abyssal_fleet_data = current.abyssal_fleet_data,
                .girls_formation    = current.girls_formation,
                .abyssal_formation  = current.abyssal_formation,
                .engagement         = current.engagement,
                .touch_plane        = {kcv::kcsapi::equipment_id::invalid, kcv::kcsapi::equipment_id::invalid},
                .attacker_side      = at_eflag,
                .attacker_fleet     = attacker_fleet,
                .attacker_ship      = static_cast<std::size_t>(at_list),
                .defender_fleet     = defender_fleet,
                .defender_ship      = static_cast<std::size_t>(df),
                .attack_kind        = at_type,
                .display_equipments = display_equipments,
                .clitical           = cl,
                .is_protected       = kcv::is_protected(dam),
                .damage             = kcv::unprotected_damage(dam),
            });

            auto& defender = at_eflag == kcv::kcsapi::fleet_flag::player  //
                               ? current.abyssal_fleet_data.fleets().at(defender_fleet).value().ships().at(df)
                               : current.girls_fleet_data.fleets().at(defender_fleet).value().ships().at(df);
            defender.hp(defender.hp() - kcv::unprotected_damage(dam));
        }
    }
}

/// @brief 開幕雷撃をもって戦闘ログを更新する.
void update(
    std::vector<kcv::battlelog>& battlelogs,
    kcv::battlelog& current,
    const kcv::kcsapi::api_opening_atack& data
) {
    const std::ranges::random_access_range auto girls_attack = std::ranges::views::zip(
        std::ranges::views::iota(0uz),  //
        data.api_frai_list_items,       //
        data.api_fcl_list_items,        //
        data.api_fydam_list_items       //
    );
    for (const auto& [index, frai_list_items, fcl_list_items, fydam_list_items] : girls_attack) {
        if (not frai_list_items.has_value()) continue;

        const std::ranges::random_access_range auto attack = std::ranges::views::zip(
            frai_list_items.value(),  //
            fcl_list_items.value(),   //
            fydam_list_items.value()  //
        );
        for (const auto& [frai, fcl, fydam] : attack) {
            const auto defender_fleet = 0uz;
            const auto defender_ship  = static_cast<std::size_t>(frai);

            battlelogs.push_back(kcv::battlelog{
                .world              = current.world,
                .map                = current.map,
                .cell               = current.cell,
                .x_al01             = current.x_al01,
                .balloon_cell       = current.balloon_cell,
                .atoll_cell         = current.atoll_cell,
                .girls_fleet_data   = current.girls_fleet_data,
                .abyssal_fleet_data = current.abyssal_fleet_data,
                .girls_formation    = current.girls_formation,
                .abyssal_formation  = current.abyssal_formation,
                .engagement         = current.engagement,
                .touch_plane        = {kcv::kcsapi::equipment_id::invalid, kcv::kcsapi::equipment_id::invalid},
                .attacker_side      = kcv::kcsapi::fleet_flag::player,
                .attacker_fleet     = static_cast<std::size_t>(current.girls_fleet_data.fleet_id() - 1),
                .attacker_ship      = index,
                .defender_fleet     = defender_fleet,
                .defender_ship      = defender_ship,
                .attack_kind        = kcv::kcsapi::day_attack_kind::torpedo,
                .display_equipments = {},
                .clitical           = fcl,
                .is_protected       = kcv::is_protected(fydam),
                .damage             = kcv::unprotected_damage(fydam),
            });

            auto& defender = current.abyssal_fleet_data.fleets().at(defender_fleet).value().ships().at(defender_ship);
            defender.hp(defender.hp() - kcv::unprotected_damage(fydam));
        }
    }

    const std::ranges::random_access_range auto abyssal_attack = std::ranges::views::zip(
        std::ranges::views::iota(0uz),  //
        data.api_erai_list_items,       //
        data.api_ecl_list_items,        //
        data.api_eydam_list_items       //
    );
    for (const auto& [index, erai_list_items, ecl_list_items, eydam_list_items] : abyssal_attack) {
        if (not erai_list_items.has_value()) continue;

        const std::ranges::random_access_range auto attack = std::ranges::views::zip(
            erai_list_items.value(),  //
            ecl_list_items.value(),   //
            eydam_list_items.value()  //
        );
        for (const auto& [erai, ecl, eydam] : attack) {
            if (erai == -1) continue;

            const auto defender_fleet = static_cast<std::size_t>(current.girls_fleet_data.fleet_id() - 1);
            const auto defender_ship  = static_cast<std::size_t>(erai);

            battlelogs.push_back(kcv::battlelog{
                .world              = current.world,
                .map                = current.map,
                .cell               = current.cell,
                .x_al01             = current.x_al01,
                .balloon_cell       = current.balloon_cell,
                .atoll_cell         = current.atoll_cell,
                .girls_fleet_data   = current.girls_fleet_data,
                .abyssal_fleet_data = current.abyssal_fleet_data,
                .girls_formation    = current.girls_formation,
                .abyssal_formation  = current.abyssal_formation,
                .engagement         = current.engagement,
                .touch_plane        = {kcv::kcsapi::equipment_id::invalid, kcv::kcsapi::equipment_id::invalid},
                .attacker_side      = kcv::kcsapi::fleet_flag::enemy,
                .attacker_fleet     = 0uz,
                .attacker_ship      = index,
                .defender_fleet     = defender_fleet,
                .defender_ship      = defender_ship,
                .attack_kind        = kcv::kcsapi::day_attack_kind::torpedo,
                .display_equipments = {},
                .clitical           = ecl,
                .is_protected       = kcv::is_protected(eydam),
                .damage             = kcv::unprotected_damage(eydam),
            });

            auto& defender = current.girls_fleet_data.fleets().at(defender_fleet).value().ships().at(defender_ship);
            defender.hp(defender.hp() - kcv::unprotected_damage(eydam));
        }
    }
}

/// @brief 雷撃戦をもって戦闘ログを更新する.
void update(std::vector<kcv::battlelog>& battlelogs, kcv::battlelog& current, const kcv::kcsapi::api_raigeki& data) {
    const std::ranges::random_access_range auto girls_attack = std::ranges::views::zip(
        std::ranges::views::iota(0uz),  //
        data.api_frai,                  //
        data.api_fcl,                   //
        data.api_fydam                  //
    );
    for (const auto& [index, frai, fcl, fydam] : girls_attack) {
        if (frai == -1) continue;

        const auto defender_fleet = 0uz;
        const auto defender_ship  = static_cast<std::size_t>(frai);

        battlelogs.push_back(kcv::battlelog{
            .world              = current.world,
            .map                = current.map,
            .cell               = current.cell,
            .x_al01             = current.x_al01,
            .balloon_cell       = current.balloon_cell,
            .atoll_cell         = current.atoll_cell,
            .girls_fleet_data   = current.girls_fleet_data,
            .abyssal_fleet_data = current.abyssal_fleet_data,
            .girls_formation    = current.girls_formation,
            .abyssal_formation  = current.abyssal_formation,
            .engagement         = current.engagement,
            .touch_plane        = {kcv::kcsapi::equipment_id::invalid, kcv::kcsapi::equipment_id::invalid},
            .attacker_side      = kcv::kcsapi::fleet_flag::player,
            .attacker_fleet     = static_cast<std::size_t>(current.girls_fleet_data.fleet_id() - 1),
            .attacker_ship      = index,
            .defender_fleet     = defender_fleet,
            .defender_ship      = defender_ship,
            .attack_kind        = kcv::kcsapi::day_attack_kind::torpedo,
            .display_equipments = {},
            .clitical           = fcl,
            .is_protected       = kcv::is_protected(fydam),
            .damage             = kcv::unprotected_damage(fydam),
        });

        auto& defender = current.abyssal_fleet_data.fleets().at(defender_fleet).value().ships().at(defender_ship);
        defender.hp(defender.hp() - kcv::unprotected_damage(fydam));
    }

    const std::ranges::random_access_range auto abyssal_attack = std::ranges::views::zip(
        std::ranges::views::iota(0uz),  //
        data.api_erai,                  //
        data.api_ecl,                   //
        data.api_eydam                  //
    );
    for (const auto& [index, erai, ecl, eydam] : abyssal_attack) {
        if (erai == -1) continue;

        const auto defender_fleet = static_cast<std::size_t>(current.girls_fleet_data.fleet_id() - 1);
        const auto defender_ship  = static_cast<std::size_t>(erai);

        battlelogs.push_back(kcv::battlelog{
            .world              = current.world,
            .map                = current.map,
            .cell               = current.cell,
            .x_al01             = current.x_al01,
            .balloon_cell       = current.balloon_cell,
            .atoll_cell         = current.atoll_cell,
            .girls_fleet_data   = current.girls_fleet_data,
            .abyssal_fleet_data = current.abyssal_fleet_data,
            .girls_formation    = current.girls_formation,
            .abyssal_formation  = current.abyssal_formation,
            .engagement         = current.engagement,
            .touch_plane        = {kcv::kcsapi::equipment_id::invalid, kcv::kcsapi::equipment_id::invalid},
            .attacker_side      = kcv::kcsapi::fleet_flag::enemy,
            .attacker_fleet     = 0uz,
            .attacker_ship      = index,
            .defender_fleet     = defender_fleet,
            .defender_ship      = defender_ship,
            .attack_kind        = kcv::kcsapi::day_attack_kind::torpedo,
            .display_equipments = {},
            .clitical           = ecl,
            .is_protected       = kcv::is_protected(eydam),
            .damage             = kcv::unprotected_damage(eydam),
        });

        auto& defender = current.girls_fleet_data.fleets().at(defender_fleet).value().ships().at(defender_ship);
        defender.hp(defender.hp() - kcv::unprotected_damage(eydam));
    }
}

}  // namespace

void kcv::process_api(
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs,
    [[maybe_unused]] kcv::battlelog& current,
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    [[maybe_unused]] bool& error
) {
    if (not kcv::success(svdata)) {
        error = true;
        return;
    }

    const auto& data = svdata.api_data;

    // 状況開始.
    initialize_situation(current, data);

    // 索敵
    // data.api_search;

    // 会敵.
    initialize_abyssal_fleet_data(current, data, api_mst_ship, api_mst_slotitem);

    // 基地航空隊噴式強襲
    if (data.api_air_base_injection.has_value()) {
        update(battlelogs, current, *data.api_air_base_injection);
    }

    // 噴式強襲
    if (data.api_injection_kouku.has_value()) {
        update(battlelogs, current, *data.api_injection_kouku);
    }

    // 基地航空隊航空戦
    if (data.api_air_base_attack.has_value()) {
        update(battlelogs, current, *data.api_air_base_attack);
    }

    // 機動部隊航空友軍
    if (data.api_friendly_kouku.has_value()) {
        update(battlelogs, current, *data.api_friendly_kouku);
    }

    // 航空戦 制空権の決定を含む
    if (data.api_kouku.has_value()) {
        update(battlelogs, current, *data.api_kouku);
    }

    // 支援艦隊攻撃
    if (data.api_support_flag != kcv::kcsapi::support_type::none and data.api_support_info.has_value()) {
        update(battlelogs, current, data.api_support_flag, *data.api_support_info);
    }

    // 先制対潜攻撃
    if (data.api_opening_taisen_flag == 1 and data.api_opening_taisen.has_value()) {
        update(battlelogs, current, *data.api_opening_taisen);
    }

    // 開幕雷撃
    if (data.api_opening_flag == 1 and data.api_opening_atack.has_value()) {
        update(battlelogs, current, *data.api_opening_atack);
    }

    // 砲雷撃 1巡目
    if (std::get<0>(data.api_hourai_flag) == 1 and data.api_hougeki1.has_value()) {
        update(battlelogs, current, *data.api_hougeki1);
    }

    // 砲雷撃 2巡目
    if (std::get<1>(data.api_hourai_flag) == 1 and data.api_hougeki2.has_value()) {
        update(battlelogs, current, *data.api_hougeki2);
    }

    // 砲雷撃 3巡目
    if (std::get<2>(data.api_hourai_flag) == 1 and data.api_hougeki3.has_value()) {
        update(battlelogs, current, *data.api_hougeki3);
    }

    // 雷撃戦
    if (std::get<3>(data.api_hourai_flag) == 1 and data.api_raigeki.has_value()) {
        update(battlelogs, current, *data.api_raigeki);
    }

    // 戦闘終了or夜戦突入判定
    if (data.api_midnight_flag == 1) {
        // 友軍艦隊攻撃
        // 夜戦
    }
}