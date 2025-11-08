#include "core/battlelog/generate_battlelog/process_kcsapi.hpp"

// std
#include <vector>

// kcv
#include "core/battlelog/battlelog.hpp"
#include "core/battlelog/generate_battlelog/process_kcsapi/common.hpp"
#include "core/utility/kcsapi.hpp"
#include "models/kcsapi/api_req_battle_midnight/sp_midnight/response.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"
#include "models/kcsapi/types/svdata.hpp"

namespace {

void initialize_situation(
    kcv::battlelog& current,
    const kcv::kcsapi::api_req_battle_midnight::sp_midnight::response& data
) {
    current.x_al01                   = data.api_x_al01;
    current.balloon_cell             = data.api_balloon_cell;
    current.atoll_cell               = data.api_atoll_cell;
    current.girls_formation          = std::get<0>(data.api_formation);
    current.abyssal_formation        = std::get<1>(data.api_formation);
    current.engagement               = std::get<2>(data.api_formation);
    std::get<0>(current.touch_plane) = kcv::to_equipment_id(std::get<0>(data.api_touch_plane));
    std::get<1>(current.touch_plane) = kcv::to_equipment_id(std::get<1>(data.api_touch_plane));
}

/// @brief 改修値および熟練度が0の装備を作成する.
auto make_ungrown_equipment(
    kcv::kcsapi::equipment_id id,                          //
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem  //
) -> std::optional<kcv::equipment> {
    return id == kcv::kcsapi::invalid_equipment_id
             ? std::nullopt
             : std::make_optional<kcv::equipment>(kcv::find_mst(api_mst_slotitem, id), 0, 0);
}

/// @brief 深海棲艦の艦隊データを更新する. 艦隊名はこのAPIに存在しないないため未設定.
/// 例えば耐久値が負から0に更新されるため, 単に昼間戦闘の結果を引き継ぐわけではない.
void initialize_abyssal_fleet_data(
    kcv::battlelog& current,
    const kcv::kcsapi::api_req_battle_midnight::sp_midnight::response& data,
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
            auto equipment = make_ungrown_equipment(id, api_mst_slotitem);
            slots.emplace_back(0, 0, std::move(equipment));
        }

        const auto exslot     = std::nullopt;
        const auto maximum_hp = kcv::to_integer(maxhp).value();
        const auto hp         = kcv::to_integer(nowhp).value();

        ships.emplace_back(mst, base_id, nationality, std::move(slots), exslot, ship_lv, maximum_hp, hp);
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

/// @brief 友軍艦隊を構築する. 艦隊名はこのAPIに存在しないないため未設定.
auto make_friend_fleet_data(
    const kcv::kcsapi::api_friendly_info& data,
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
) -> kcv::fleet_data {
    const std::ranges::random_access_range auto zip = std::ranges::views::zip(
        data.api_ship_id,  //
        data.api_ship_lv,  //
        data.api_nowhps,   //
        data.api_maxhps,   //
        data.api_Param,    //
        data.api_Slot,     //
        data.api_slot_ex   // 深海棲艦には無いが友軍艦隊にはある
    );

    auto ships = std::vector<kcv::ship>{};
    ships.reserve(zip.size());
    for (const auto& [ship_id, ship_lv, maxhp, nowhp, param, slot, slot_ex] : zip) {
        const auto& mst        = kcv::find_mst(api_mst_ship, ship_id);
        const auto base_id     = kcv::base_id(api_mst_ship, mst);
        const auto nationality = kcv::nationality(mst);

        /// HACK: 友軍の搭載数は艦船マスタを参照している.
        auto slots = std::vector<kcv::slot>{};
        slots.reserve(slot.size());
        for (const auto [id, maxeq] : std::ranges::views::zip(slot, mst.api_maxeq.value())) {
            auto equipment = make_ungrown_equipment(id, api_mst_slotitem);
            slots.emplace_back(maxeq, maxeq, std::move(equipment));
        }

        auto exslot           = kcv::slot{0, 0, make_ungrown_equipment(slot_ex, api_mst_slotitem)};
        const auto maximum_hp = kcv::to_integer(maxhp).value();
        const auto hp         = kcv::to_integer(nowhp).value();

        ships.emplace_back(mst, base_id, nationality, std::move(slots), std::move(exslot), ship_lv, maximum_hp, hp);
    }

    return kcv::fleet_data{
        1,  // 第1艦隊
        0,  // 道中支援なし
        0,  // 決戦支援なし
        0,  // 通常艦隊
        std::vector{
            std::make_optional<kcv::fleet>(kcv::uninitialized_friend_fleet_name_tag, std::move(ships)),
        },
        {},  // 基地航空隊なし
    };
}

/// @brief 支援艦隊攻撃をもって戦闘ログを更新する.
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
                    const auto abyssal_attack = std::ranges::views::zip(
                        *data.api_stage3->api_fdam,
                        current.girls_fleet_data.fleets().at(current.girls_fleet_data.fleet_id() - 1).value().ships()
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

/// @brief 友軍艦隊夜戦攻撃をもって戦闘ログを更新する.
void update(
    kcv::battlelog& current,
    std::vector<kcv::battlelog>& battlelogs,
    kcv::fleet_data& friend_fleet_data,
    const kcv::kcsapi::api_friendly_battle& data
) {
    const auto& hougeki = data.api_hougeki;

    if (const bool has_attack = hougeki.api_at_eflag.has_value()       //
                            and hougeki.api_at_list.has_value()        //
                            and hougeki.api_cl_list.has_value()        //
                            and hougeki.api_damage.has_value()         //
                            and hougeki.api_df_list.has_value()        //
                            and hougeki.api_n_mother_list.has_value()  //
                            and hougeki.api_si_list.has_value()        //
                            and hougeki.api_sp_list.has_value();
        not has_attack) {
        return;
    }

    const std::ranges::random_access_range auto zip = std::ranges::views::zip(
        std::ranges::views::iota(0uz),  //
        *hougeki.api_at_eflag,          //
        *hougeki.api_at_list,           //
        *hougeki.api_cl_list,           //
        *hougeki.api_damage,            //
        *hougeki.api_df_list,           //
        *hougeki.api_n_mother_list,     //
        *hougeki.api_si_list,           //
        *hougeki.api_sp_list            //
    );
    for (const auto& [index, at_eflag, at_list, cl_list, damage, df_list, n_mother_list, si_list, sp_list] : zip) {
        const auto attack             = std::ranges::views::zip(cl_list, damage, df_list);
        const auto attacker_fleet     = at_eflag == kcv::kcsapi::fleet_flag::player  //
                                          ? static_cast<std::size_t>(friend_fleet_data.fleet_id() - 1)
                                          : 0uz;
        const auto defender_fleet     = at_eflag == kcv::kcsapi::fleet_flag::player  //
                                          ? 0uz
                                          : static_cast<std::size_t>(friend_fleet_data.fleet_id() - 1);
        const auto display_equipments = si_list  //
                                      | std::ranges::views::transform(&kcv::to_equipment_id)
                                      | std::ranges::to<std::vector>();
        for (const auto& [cl, dam, df] : attack) {
            battlelogs.push_back(
                kcv::battlelog{
                    .world              = current.world,
                    .map                = current.map,
                    .cell               = current.cell,
                    .x_al01             = current.x_al01,
                    .balloon_cell       = current.balloon_cell,
                    .atoll_cell         = current.atoll_cell,
                    .girls_fleet_data   = friend_fleet_data,
                    .abyssal_fleet_data = current.abyssal_fleet_data,
                    .girls_formation    = current.girls_formation,
                    .abyssal_formation  = current.abyssal_formation,
                    .engagement         = current.engagement,
                    .touch_plane        = {kcv::kcsapi::invalid_equipment_id, kcv::kcsapi::invalid_equipment_id},  // ?
                    .attacker_side      = at_eflag,
                    .attacker_fleet     = attacker_fleet,
                    .attacker_ship      = static_cast<std::size_t>(at_list),
                    .defender_fleet     = defender_fleet,
                    .defender_ship      = static_cast<std::size_t>(df),
                    .attack_kind        = sp_list,
                    .display_equipments = display_equipments,
                    .clitical           = cl,
                    .is_protected       = kcv::is_protected(dam),
                    .damage             = kcv::unprotected_damage(dam),
                }
            );

            auto& defender = at_eflag == kcv::kcsapi::fleet_flag::player  //
                               ? current.abyssal_fleet_data.fleets().at(defender_fleet).value().ships().at(df)
                               : friend_fleet_data.fleets().at(defender_fleet).value().ships().at(df);
            defender.hp(defender.hp() - kcv::unprotected_damage(dam));
        }
    }
}

/// @brief 夜戦攻撃をもって戦闘ログを更新する.
void update(kcv::battlelog& current, std::vector<kcv::battlelog>& battlelogs, const kcv::kcsapi::api_hougeki& data) {
    if (const bool has_attack = data.api_at_eflag.has_value()       //
                            and data.api_at_list.has_value()        //
                            and data.api_cl_list.has_value()        //
                            and data.api_damage.has_value()         //
                            and data.api_df_list.has_value()        //
                            and data.api_n_mother_list.has_value()  //
                            and data.api_si_list.has_value()        //
                            and data.api_sp_list.has_value();
        not has_attack) {
        return;
    }

    const std::ranges::random_access_range auto zip = std::ranges::views::zip(
        std::ranges::views::iota(0uz),  //
        *data.api_at_eflag,             //
        *data.api_at_list,              //
        *data.api_cl_list,              //
        *data.api_damage,               //
        *data.api_df_list,              //
        *data.api_n_mother_list,        //
        *data.api_si_list,              //
        *data.api_sp_list               //
    );
    for (const auto& [index, at_eflag, at_list, cl_list, damage, df_list, n_mother_list, si_list, sp_list] : zip) {
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
            battlelogs.push_back(
                kcv::battlelog{
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
                    .touch_plane        = current.touch_plane,
                    .attacker_side      = at_eflag,
                    .attacker_fleet     = attacker_fleet,
                    .attacker_ship      = static_cast<std::size_t>(at_list),
                    .defender_fleet     = defender_fleet,
                    .defender_ship      = static_cast<std::size_t>(df),
                    .attack_kind        = sp_list,
                    .display_equipments = display_equipments,
                    .clitical           = cl,
                    .is_protected       = kcv::is_protected(dam),
                    .damage             = kcv::unprotected_damage(dam),
                }
            );

            auto& defender = at_eflag == kcv::kcsapi::fleet_flag::player  //
                               ? current.abyssal_fleet_data.fleets().at(defender_fleet).value().ships().at(df)
                               : current.girls_fleet_data.fleets().at(defender_fleet).value().ships().at(df);
            defender.hp(defender.hp() - kcv::unprotected_damage(dam));
        }
    }
}

}  // namespace

void kcv::process_kcsapi(
    [[maybe_unused]] std::vector<kcv::battlelog>& battlelogs,
    [[maybe_unused]] kcv::battlelog& current,
    [[maybe_unused]] const kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::sp_midnight::response>& svdata,
    [[maybe_unused]] const kcv::kcsapi::api_mst_ship& api_mst_ship,
    [[maybe_unused]] const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    [[maybe_unused]] bool& error
) {
    if (not kcv::success(svdata)) {
        error = true;
        return;
    }

    const auto& data = svdata.api_data;

    // 状況開始.
    initialize_situation(current, data);
    initialize_abyssal_fleet_data(current, data, api_mst_ship, api_mst_slotitem);

    // 支援艦隊攻撃
    if (data.api_n_support_flag != kcv::kcsapi::support_type::none and data.api_n_support_info.has_value()) {
        update(battlelogs, current, data.api_n_support_flag, *data.api_n_support_info);
    }

    // 友軍.
    if (data.api_friendly_info.has_value() and data.api_friendly_battle.has_value()) {
        // 友軍艦隊を構築.
        auto friend_fleet_data = make_friend_fleet_data(*data.api_friendly_info, api_mst_ship, api_mst_slotitem);

        // ダメージ更新.
        update(current, battlelogs, friend_fleet_data, *data.api_friendly_battle);
    }

    // 本隊.
    if (data.api_hougeki.has_value()) {
        update(current, battlelogs, *data.api_hougeki);
    }
}
