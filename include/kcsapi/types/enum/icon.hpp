#ifndef KCVERIFY_kcsapi_TYPES_ENUM_ICON_HPP_INCLUDED
#define KCVERIFY_kcsapi_TYPES_ENUM_ICON_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

// TODO: 艦これに即した名前にする
/// @brief 装備.アイコンID. 装備種4. api_type[3].
enum class icon {
    small_main_gun = 1,           //  1=小口径主砲
    medium_main_gun,              //  2=中口径主砲
    large_main_gun,               //  3=大口径主砲
    secondary_gun,                //  4=副砲
    torpedo,                      //  5=魚雷
    cb_fighter,                   //  6=艦上戦闘機
    cb_dive_bomber,               //  7=艦上爆撃機
    cb_torpedo_bomber,            //  8=艦上攻撃機
    cb_recon,                     //  9=艦上偵察機
    seaplane,                     // 10=水上機
    radar,                        // 11=電探
    anti_air_shell,               // 12=対空強化弾
    ap_shell,                     // 13=対艦強化弾
    emergency_repair,             // 14=応急修理要員
    anti_air_gun,                 // 15=対空機銃
    high_angle_gun,               // 16=高角砲
    depth_charge,                 // 17=爆雷
    sonar,                        // 18=ソナー
    engine_mod,                   // 19=機関部強化
    landing_craft,                // 20=上陸用舟艇
    rotorcraft,                   // 21=オートジャイロ
    anti_sub_patrol_aircraft,     // 22=対潜哨戒機
    extra_armor,                  // 23=追加装甲
    searchlight,                  // 24=探照灯
    supply_container,             // 25=簡易輸送部材
    ship_repair_facility,         // 26=艦艇修理施設
    starshell,                    // 27=照明弾
    command_facility,             // 28=司令部施設
    aviation_personnel,           // 29=航空要員
    anti_air_fire_director,       // 30=高射装置
    anti_ground_equipment,        // 31=対地装備
    ship_personnel,               // 32=水上艦要員
    large_flying_boat,            // 33=大型飛行艇
    combat_ration,                // 34=戦闘糧食
    supplies,                     // 35=補給物資
    amphibious_tank,              // 36=特型内火艇
    lb_attacker,                  // 37=陸上攻撃機
    lb_fighter,                   // 38=局地戦闘機
    jet_fighter_bomber_keiun,     // 39=噴式戦闘爆撃機(噴式景雲改)
    jet_fighter_bomber_kikka,     // 40=噴式戦闘爆撃機(橘花改)
    transportation_material,      // 41=輸送機材
    submarine_equipment,          // 42=潜水艦装備
    seaplane_fighter,             // 43=水上戦闘機
    army_fighter,                 // 44=陸軍戦闘機
    night_fighter  = 45,          // 45=夜間戦闘機
    night_attacker = 46,          // 46=夜間攻撃機
    lb_anti_sub_patrol_aircraft,  // 47=陸上対潜哨戒機
    army_strike_aircraft,         // 48=陸軍襲撃機
    large_lb_aircraft,            // 49=大型陸上機
    night_seaplane_recon,         // 50=夜間水上偵察機
    night_attack_seaplane,        // 51=夜間作戦汎用攻撃水上機
    landing_force,                // 52=陸戦部隊
    ship_smoke_generator = 54     // 54=艦載発煙装置
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_kcsapi_TYPES_ENUM_ICON_HPP_INCLUDED
