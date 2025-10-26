#include "core/battlelog/process_api.hpp"

// std
#include <optional>
#include <ranges>
#include <vector>

// kcv
#include "core/battlelog/battlelog.hpp"
#include "core/battlelog/process_api/common.hpp"
#include "core/utility/kcsapi.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/kcsapi/api_req_sortie/ld_airbattle/response.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/api_kouku.hpp"
#include "models/kcsapi/types/svdata.hpp"

namespace {

/// @brief 状況開始.
void initialize_situation(kcv::battlelog& current, const kcv::kcsapi::api_req_sortie::ld_airbattle::response& data) {
    current.x_al01            = std::nullopt;
    current.balloon_cell      = data.api_balloon_cell;
    current.atoll_cell        = data.api_atoll_cell;
    current.girls_formation   = std::get<0>(data.api_formation);
    current.abyssal_formation = std::get<1>(data.api_formation);
    current.engagement        = std::get<2>(data.api_formation);
}

void initialize_abyssal_fleet_data(
    kcv::battlelog& current,
    const kcv::kcsapi::api_req_sortie::ld_airbattle::response& data,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) {
    const std::ranges::random_access_range auto zip = std::ranges::views::zip(
        data.api_ship_ke,   //
        data.api_ship_lv,   //
        data.api_e_maxhps,  //
        data.api_e_nowhps,  //
        data.api_eParam,    //
        data.api_eSlot      //
    );

    auto ships = std::vector<kcv::ship>{};
    ships.reserve(ships.size());
    for (const auto& [ship_ke, ship_lv, maxhp, nowhp, param, slot] : zip) {
        const auto& mst        = kcv::find_mst(api_mst_ship, ship_ke);
        const auto base_id     = kcv::kcsapi::ship_id{};
        const auto nationality = kcv::kcsapi::nationality::abyssal;

        /// FIXME: 深海棲艦の搭載数は基本的に不明なため, 0で初期化している.
        auto slots = std::vector<kcv::slot>{};
        slots.reserve(slot.size());
        for (const auto id : slot) {
            auto equipment = id == kcv::kcsapi::equipment_id::invalid
                               ? std::nullopt
                               : std::make_optional<kcv::equipment>(kcv::find_mst(api_mst_slotitem, id), 0, 0);
            slots.emplace_back(0, 0, std::move(equipment));
        }

        const auto exslot = std::nullopt;
        const auto hp     = kcv::to_integer(nowhp).value();

        ships.emplace_back(mst, base_id, nationality, std::move(slots), exslot, ship_lv, hp);
    }

    current.abyssal_fleet_data = kcv::fleet_data{
        1,  // 第1艦隊
        0,  // 道中支援なし
        0,  // 決戦支援なし
        0,  // 通常艦隊
        std::vector{
            std::make_optional<kcv::fleet>(kcv::uninitialized_enemy_fleet_name_tag, std::move(ships)),
        },
        {},  // 基地航空隊なし
    };
}

void update(std::vector<kcv::battlelog>& battlelogs, kcv::battlelog& current, const kcv::kcsapi::api_kouku& data) {
    if (data.api_stage3.has_value()) {
        if (data.api_stage3->api_fdam.has_value()) {
            const auto abyssal_attack = std::ranges::views::zip(
                *data.api_stage3->api_fdam,                                                                    //
                current.girls_fleet_data.fleets().at(current.girls_fleet_data.fleet_id() - 1).value().ships()  //
            );
            for (const auto& [dam, defender] : abyssal_attack) {
                defender.hp(defender.hp() - kcv::unprotected_damage(dam));
            }
        }

        {
            const auto girls_attack = std::ranges::views::zip(
                data.api_stage3->api_edam,                          //
                current.abyssal_fleet_data.fleets().at(0)->ships()  //
            );
            for (const auto& [dam, defender] : girls_attack) {
                defender.hp(defender.hp() - kcv::unprotected_damage(dam));
            }
        }
    }
}

}  // namespace

void kcv::process_api(
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs,
    [[maybe_unused]] kcv::battlelog& current,
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::ld_airbattle::response>& svdata,
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

    // data.api_search;

    // 会敵.
    initialize_abyssal_fleet_data(current, data, api_mst_ship, api_mst_slotitem);

    // 航空戦.
    if (std::get<2>(data.api_stage_flag) == 1 and data.api_kouku.has_value()) {
        update(battlelogs, current, *data.api_kouku);
    }

    if (data.api_midnight_flag == 1) {
        //
    }
}
