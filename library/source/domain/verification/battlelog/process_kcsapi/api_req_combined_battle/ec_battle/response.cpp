#include "domain/verification/battlelog/process_kcsapi.hpp"

// std
#include <array>
#include <ranges>
#include <tuple>
#include <vector>

// kcv
#include "domain/verification/battlelog/common.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/entity/ship.hpp"
#include "kcv/external/kcsapi/api_req_combined_battle/ec_battle/response.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_ship.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcv/external/kcsapi/extensions/utility.hpp"
#include "kcv/external/kcsapi/types/api_kouku.hpp"
#include "kcv/external/kcsapi/types/api_stage_flag.hpp"
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"
#include "kcv/external/kcsapi/types/enum/ship_id.hpp"
#include "kcv/external/kcsapi/types/enum/support_type.hpp"
#include "kcv/external/kcsapi/types/svdata.hpp"

namespace {

/// @brief 状況開始.
void initialize_situation(
    kcv::battlelog& current,
    const kcv::kcsapi::api_req_combined_battle::ec_battle::response& data
) {
    current.x_al01            = data.api_x_al01;
    current.balloon_cell      = data.api_balloon_cell;
    current.atoll_cell        = data.api_atoll_cell;
    current.girls_formation   = std::get<0>(data.api_formation);
    current.abyssal_formation = std::get<1>(data.api_formation);
    current.engagement        = std::get<2>(data.api_formation);
}

auto make_abyssal_ships(
    const std::vector<kcv::kcsapi::ship_id>& ship_ke,
    const std::vector<std::int32_t>& ship_lv,
    const std::vector<std::int32_t>& e_maxhps,
    const std::vector<std::int32_t>& e_nowhps,
    const std::vector<std::tuple<std::int32_t, std::int32_t, std::int32_t, std::int32_t>>& eParam,
    const std::vector<std::array<kcv::kcsapi::equipment_id, 5>>& eSlot,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> std::vector<kcv::ship> {
    const std::ranges::random_access_range auto zip = std::ranges::views::zip(
        ship_ke,   //
        ship_lv,   //
        e_maxhps,  //
        e_nowhps,  //
        eParam,    //
        eSlot      //
    );

    auto ships = std::vector<kcv::ship>{};
    ships.reserve(zip.size());
    for (const auto& [ship_ke, ship_lv, maxhp, nowhp, param, slot] : zip) {
        const auto& mst        = kcv::find_mst(api_mst_ship, ship_ke);
        const auto base_id     = kcv::kcsapi::ship_id{};
        const auto nationality = kcv::kcsapi::nationality::abyssal;

        /// FIXME: 深海棲艦の搭載数は基本的に不明なため, 0で初期化している.
        auto slots = std::vector<kcv::slot>{};
        slots.reserve(slot.size());
        for (const auto id : slot) {
            auto equipment = id == kcv::kcsapi::invalid_equipment_id
                               ? std::nullopt
                               : std::make_optional<kcv::equipment>(kcv::find_mst(api_mst_slotitem, id), 0, 0);
            slots.emplace_back(0, 0, std::move(equipment));
        }

        const auto exslot     = std::nullopt;
        const auto condition  = 49;
        const auto ammo       = 0;  // 深海棲艦の弾薬量補正は常に1.
        const auto kyouka     = kcv::kcsapi::api_kyouka{};
        const auto maximum_hp = kcv::to_integer(maxhp).value();
        const auto hp         = kcv::to_integer(nowhp).value();
        const auto firepower  = std::get<kcv::kcsapi::idx_param::houg>(param);
        const auto torpedo    = std::get<kcv::kcsapi::idx_param::raig>(param);
        const auto armor      = std::get<kcv::kcsapi::idx_param::souk>(param);
        const auto speed      = mst.api_soku;                                                       // ?
        const auto asw        = std::get<kcv::kcsapi::idx_minmax::max>(mst.api_tais.value_or({}));  // ?

        ships.emplace_back(
            mst, base_id, nationality, std::move(slots), exslot, ship_lv, condition, ammo, kyouka, maximum_hp, hp,
            firepower, torpedo, armor, speed, asw
        );
    }

    return ships;
}

/// @brief 深海棲艦の艦隊データを更新する. 艦隊名はこのAPIに存在しないないため未設定.
void initialize_abyssal_fleet_data(
    kcv::battlelog& current,
    const kcv::kcsapi::api_req_combined_battle::ec_battle::response& data,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) {
    auto main_ships = make_abyssal_ships(
        data.api_ship_ke,   //
        data.api_ship_lv,   //
        data.api_e_maxhps,  //
        data.api_e_nowhps,  //
        data.api_eParam,    //
        data.api_eSlot,     //
        api_mst_ship,       //
        api_mst_slotitem    //
    );

    auto escort_ships = make_abyssal_ships(
        data.api_ship_ke_combined,   //
        data.api_ship_lv_combined,   //
        data.api_e_maxhps_combined,  //
        data.api_e_nowhps_combined,  //
        data.api_eParam_combined,    //
        data.api_eSlot_combined,     //
        api_mst_ship,                //
        api_mst_slotitem             //
    );

    current.abyssal_fleet_data = kcv::fleet_data{
        1,   // 第1艦隊
        0,   // 道中支援なし
        0,   // 決戦支援なし
        -1,  // 敵連合 仮
        std::vector{
            std::make_optional<kcv::fleet>(kcv::uninitialized_enemy_fleet_name_tag, std::move(main_ships)),
            std::make_optional<kcv::fleet>(kcv::uninitialized_enemy_fleet_name_tag, std::move(escort_ships)),
        },
        {},  // 基地航空隊なし
    };
}

/// @brief 基地航空隊攻撃のデータをもって戦闘ログを更新する.
void update(kcv::battlelogs_t& battlelogs, kcv::battlelog& current, const kcv::kcsapi::api_air_base_attack& data) {
    for (const auto& datum : data) {
        if (datum.api_stage3.has_value()) {
            if (datum.api_stage3->api_fdam.has_value()) {
                const auto abyssal_attack = std::ranges::views::zip(
                    *datum.api_stage3->api_fdam,                             //
                    current.girls_fleet_data.fleets().at(0).value().ships()  //
                );
                for (const auto& [dam, defender] : abyssal_attack) {
                    defender.hp(defender.hp() - kcv::unprotected_damage(dam));
                }
            }

            {
                const auto girls_attack = std::ranges::views::zip(
                    datum.api_stage3->api_edam,                                //
                    current.abyssal_fleet_data.fleets().at(0).value().ships()  //
                );
                for (const auto& [dam, defender] : girls_attack) {
                    defender.hp(defender.hp() - kcv::unprotected_damage(dam));
                }
            }
        }

        if (datum.api_stage3_combined.has_value()) {
            if (datum.api_stage3_combined->api_fdam.has_value()) {
                const auto abyssal_attack = std::ranges::views::zip(
                    *datum.api_stage3_combined->api_fdam,                    //
                    current.girls_fleet_data.fleets().at(1).value().ships()  //
                );
                for (const auto& [dam, defender] : abyssal_attack) {
                    defender.hp(defender.hp() - kcv::unprotected_damage(dam));
                }
            }

            {
                const auto girls_attack = std::ranges::views::zip(
                    datum.api_stage3_combined->api_edam,                       //
                    current.abyssal_fleet_data.fleets().at(1).value().ships()  //
                );
                for (const auto& [dam, defender] : girls_attack) {
                    defender.hp(defender.hp() - kcv::unprotected_damage(dam));
                }
            }
        }
    }
}

/// @brief 友軍艦隊航空攻撃または航空戦のデータをもって戦闘ログを更新する.
void update(kcv::battlelogs_t& battlelogs, kcv::battlelog& current, const kcv::kcsapi::api_kouku& data) {
    if (data.api_stage3.has_value()) {
        if (data.api_stage3->api_fdam.has_value()) {
            const auto abyssal_attack = std::ranges::views::zip(
                *data.api_stage3->api_fdam,                              //
                current.girls_fleet_data.fleets().at(0).value().ships()  //
            );
            for (const auto& [dam, defender] : abyssal_attack) {
                defender.hp(defender.hp() - kcv::unprotected_damage(dam));
            }
        }

        {
            const auto girls_attack = std::ranges::views::zip(
                data.api_stage3->api_edam,                                 //
                current.abyssal_fleet_data.fleets().at(0).value().ships()  //
            );
            for (const auto& [dam, defender] : girls_attack) {
                defender.hp(defender.hp() - kcv::unprotected_damage(dam));
            }
        }
    }

    if (data.api_stage3_combined.has_value()) {
        if (data.api_stage3_combined->api_fdam.has_value()) {
            const auto abyssal_attack = std::ranges::views::zip(
                *data.api_stage3_combined->api_fdam,                     //
                current.girls_fleet_data.fleets().at(1).value().ships()  //
            );
            for (const auto& [dam, defender] : abyssal_attack) {
                defender.hp(defender.hp() - kcv::unprotected_damage(dam));
            }
        }

        {
            const auto girls_attack = std::ranges::views::zip(
                data.api_stage3_combined->api_edam,                        //
                current.abyssal_fleet_data.fleets().at(1).value().ships()  //
            );
            for (const auto& [dam, defender] : girls_attack) {
                defender.hp(defender.hp() - kcv::unprotected_damage(dam));
            }
        }
    }
}

/// @brief 支援艦隊攻撃をもって戦闘ログを更新する.
void update(
    kcv::battlelogs_t& battlelogs,
    kcv::battlelog& current,
    kcv::kcsapi::support_type flag,
    const kcv::kcsapi::api_support_info& info
) {}

/// @brief 先制対潜攻撃をもって戦闘ログを更新する.
void update(kcv::battlelogs_t& battlelogs, kcv::battlelog& current, const kcv::kcsapi::api_hougeki1& data) {}

/// @brief 開幕雷撃をもって戦闘ログを更新する.
void update(kcv::battlelogs_t& battlelogs, kcv::battlelog& current, const kcv::kcsapi::api_opening_atack& data) {}

/// @brief 雷撃戦をもって戦闘ログを更新する.
void update(kcv::battlelogs_t& battlelogs, kcv::battlelog& current, const kcv::kcsapi::api_raigeki& data) {}

}  // namespace

void kcv::process_kcsapi(
    [[maybe_unused]] kcv::battlelogs_t& battlelogs,
    [[maybe_unused]] kcv::battlelog& current,
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ec_battle::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] bool& error
) {
    if (kcv::success(svdata)) {
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

    // 噴式強襲

    // 基地航空隊航空戦
    if (data.api_air_base_attack.has_value()) {
        update(battlelogs, current, *data.api_air_base_attack);
    }
    // data.api_air_base_rescue_type;

    // 機動部隊航空友軍

    // 航空戦 制空権の決定を含む
    if (std::get<kcv::kcsapi::idx_stage_flag::stage3>(data.api_stage_flag) == 1 and data.api_kouku.has_value()) {
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