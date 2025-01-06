#ifndef KCVERIFY_KCSAPI_TYPES_ENUM_CATEGORY_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_ENUM_CATEGORY_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

/// @brief 装備.カテゴリID. 装備種3. api_type[2].
enum class category {
    /// @brief 小口径主砲
    main_gun_small = 1,

    /// @brief 中口径主砲
    main_gun_medium = 2,

    /// @brief 大口径主砲
    main_gun_large = 3,

    /// @brief 副砲
    secondary_gun = 4,

    /// @brief 魚雷
    torpedo = 5,

    /// @brief 艦上戦闘機
    carrier_based_fighter = 6,

    /// @brief 艦上爆撃機
    carrier_based_bomber = 7,

    /// @brief 艦上攻撃機
    carrier_based_torpedo = 8,

    /// @brief 艦上偵察機
    carrier_based_recon = 9,

    /// @brief 水上偵察機
    seaplane_recon = 10,

    /// @brief 水上爆撃機
    seaplane_bomber = 11,

    /// @brief 小型電探
    radar_small = 12,

    /// @brief 大型電探
    radar_large = 13,

    /// @brief ソナー
    sonar = 14,

    /// @brief 爆雷
    depth_charge = 15,

    /// @brief 追加装甲
    extra_armor = 16,

    /// @brief 機関部強化
    engine = 17,

    /// @brief 対空強化弾
    aa_shell = 18,

    /// @brief 対艦強化弾
    ap_shell = 19,

    /// @brief VT信管
    vt_fuse = 20,

    /// @brief 対空機銃
    aa_gun = 21,

    /// @brief 特殊潜航艇
    midget_submarine = 22,

    /// @brief 応急修理要員
    damage_control = 23,

    /// @brief 上陸用舟艇
    landing_craft = 24,

    /// @brief オートジャイロ
    autogyro = 25,

    /// @brief 対潜哨戒機
    as_patrol = 26,

    /// @brief 追加装甲（中型）
    extra_armor_medium = 27,

    /// @brief 追加装甲（大型）
    extra_armor_large = 28,

    /// @brief 探照灯
    searchlight = 29,

    /// @brief 簡易輸送部材
    transport_container = 30,

    /// @brief 艦艇修理施設
    repair_facility = 31,

    /// @brief 潜水艦魚雷
    submarine_torpedo = 32,

    /// @brief 照明弾
    star_shell = 33,

    /// @brief 司令部施設
    command_facility = 34,

    /// @brief 航空要員
    aviation_personnel = 35,

    /// @brief 高射装置
    aa_director = 36,

    /// @brief 対地装備
    rocket = 37,

    /// @brief 大口径主砲(II)
    main_gun_large_2 = 38,

    /// @brief 水上艦要員
    surface_ship_personnel = 39,

    /// @brief 大型ソナー
    sonar_large = 40,

    /// @brief 大型飛行艇
    flying_boat = 41,

    /// @brief 大型探照灯
    searchlight_large = 42,

    /// @brief 戦闘糧食
    ration = 43,

    /// @brief 補給物資
    supplies = 44,

    /// @brief 水上戦闘機
    seaplane_fighter = 45,

    /// @brief 特型内火艇
    special_amphibious_tank = 46,

    /// @brief 陸上攻撃機
    land_based_attacker = 47,

    /// @brief 局地戦闘機
    interceptor = 48,

    /// @brief 陸上偵察機
    land_based_recon = 49,

    /// @brief 輸送機材
    transport_material = 50,

    /// @brief 潜水艦装備
    submarine_equipment = 51,

    /// @brief 陸戦部隊
    army_infantry = 52,

    /// @brief 大型陸上機
    heavy_bomber = 53,

    /// @brief 水上艦装備
    surface_ship_equipment = 54,

    /// @brief 噴式戦闘機
    jet_fighter = 56,

    /// @brief 噴式戦闘爆撃機
    jet_bomber = 57,

    /// @brief 噴式攻撃機
    jet_torpedo = 58,

    /// @brief 噴式索敵機
    jet_recon = 59,

    /// @brief 大型電探(II)
    radar_large_2 = 93,

    /// @brief 艦上偵察機(II)
    carrier_based_recon_2 = 94,

    /// @brief 副砲(II)
    secondary_gun_2 = 95,
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_ENUM_CATEGORY_HPP_INCLUDED
