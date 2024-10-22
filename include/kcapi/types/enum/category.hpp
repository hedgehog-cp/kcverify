#ifndef KCVERIFY_KCAPI_TYPES_ENUM_CATEGORY_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_ENUM_CATEGORY_HPP_INCLUDED

namespace kcv {
namespace kcapi {

/// @brief 装備.カテゴリID. 装備種3. api_type[2].
enum class category {
    small_main_gun = 1,        // 小口径主砲
    medium_main_gun,           // 中口径主砲
    large_main_gun,            // 大口径主砲
    secondary_gun,             // 副砲
    torpedo,                   // 魚雷
    cb_fighter,                // 艦上戦闘機
    cb_dive_bomber,            // 艦上爆撃機
    cb_torpedo_bomber,         // 艦上攻撃機
    cb_recon,                  // 艦上偵察機
    recon_seaplane,            // 水上偵察機
    seaplane_bomber,           // 水上爆撃機
    small_radar,               // 小型電探
    large_radar,               // 大型電探
    sonar,                     // ソナー
    depth_charge,              // 爆雷
    extra_armor,               // 追加装甲
    engine,                    // 機関部強化
    anti_air_shell,            // 対空強化弾
    ap_shell,                  // 対艦強化弾
    vt_fuze,                   // VT信管
    anti_air_gun,              // 対空機銃
    midget_submarine,          // 特殊潜航艇
    emergency_repair,          // 応急修理要員
    landing_craft,             // 上陸用舟艇
    rotorcraft,                // オートジャイロ
    anti_sub_patrol_aircraft,  // 対潜哨戒機
    medium_armor,              // 追加装甲(中型)
    large_armor,               // 追加装甲(大型)
    searchlight,               // 探照灯
    supply_container,          // 簡易輸送部材
    ship_repair_facility,      // 艦艇修理施設
    submarine_torpedo,         // 潜水艦魚雷
    starshell,                 // 照明弾
    command_facility,          // 司令部施設
    aviation_personnel,        // 航空要員
    anti_air_fire_director,    // 高射装置
    anti_ground_equipment,     // 対地装備
    large_main_gun2,           // 大口径主砲（II）
    ship_personnel,            // 水上艦要員
    large_sonar,               // 大型ソナー
    large_flying_boat,         // 大型飛行艇
    large_searchlight,         // 大型探照灯
    combat_ration,             // 戦闘糧食
    supplies,                  // 補給物資
    seaplane_fighter,          // 水上戦闘機
    amphibious_tank,           // 特型内火艇
    lb_attacker,               // 陸上攻撃機
    lb_fighter,                // 局地戦闘機
    lb_recon,                  // 陸上偵察機
    transportation_material,   // 輸送機材
    submarine_equipment,       // 潜水艦装備
    landing_force,             // 陸戦部隊
    large_lb_aircraft,         // 大型陸上機
    jet_fighter,               // 噴式戦闘機
    ship_equipment,            // 水上艦装備
    jet_fighter_bomber,        // 噴式戦闘爆撃機
    jet_torpedo_bomber,        // 噴式攻撃機
    jet_recon,                 // 噴式偵察機
    large_radar2 = 93,         // 大型電探（II）
    cb_recon2,                 // 艦上偵察機（II）
    secondary_gun2,            // 副砲（II）
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_ENUM_CATEGORY_HPP_INCLUDED
