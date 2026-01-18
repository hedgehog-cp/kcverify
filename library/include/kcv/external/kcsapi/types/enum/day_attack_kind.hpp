#ifndef KCV_EXTERNAL_KCSAPI_TYPES_ENUM_DAY_ATTACK_KIND_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_ENUM_DAY_ATTACK_KIND_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

/// @brief 昼戦攻撃種別
enum class day_attack_kind {
    /// @brief 不明
    unknown = -1,

    /// @brief 通常攻撃 (API上でのみ使用されます)
    normal_attack,

    /// @brief レーザー攻撃
    laser,

    /// @brief 連続射撃
    double_shelling,

    /// @brief カットイン(主砲/副砲)
    cutin_main_sub,

    /// @brief カットイン(主砲/電探)
    cutin_main_radar,

    /// @brief カットイン(主砲/徹甲弾)
    cutin_main_ap,

    /// @brief カットイン(主砲/主砲)
    cutin_main_main,

    /// @brief 空母カットイン
    cutin_air_attack,

    /// @brief Nelson Touch
    special_nelson = 100,

    /// @brief 一斉射かッ…胸が熱いな！
    special_nagato = 101,

    /// @brief 長門、いい？ いくわよ！ 主砲一斉射ッ！
    special_mutsu = 102,

    /// @brief Colorado Touch
    special_colorado = 103,

    /// @brief 僚艦夜戦突撃
    special_kongo = 104,

    /// @brief Richelieuよ！圧倒しなさいっ！
    special_richelieu = 105,

    /// @brief Queen Elizabeth Class special attack
    special_queen_elizabeth_class = 106,

    /// @brief 瑞雲立体攻撃
    zuiun_multi_angle = 200,

    /// @brief 海空立体攻撃
    sea_air_multi_angle = 201,

    /// @brief 潜水艦隊攻撃 (参加潜水艦ポジション2・3)
    special_submarine_tender_23 = 300,

    /// @brief 潜水艦隊攻撃 (参加潜水艦ポジション3・4)
    special_submarine_tender_34 = 301,

    /// @brief 潜水艦隊攻撃 (参加潜水艦ポジション2・4)
    special_submarine_tender_24 = 302,

    /// @brief 大和、突撃します！二番艦も続いてください！
    special_yamato_3_ships = 400,

    /// @brief 第一戦隊、突撃！主砲、全力斉射ッ！
    special_yamato_2_ships = 401,

    /// @brief 砲撃
    shelling = 1000,

    /// @brief 空撃
    air_attack,

    /// @brief 爆雷攻撃
    depth_charge,

    /// @brief 雷撃
    torpedo,

    /// @brief ロケット攻撃
    rocket = 2000,

    /// @brief 揚陸攻撃(大発動艇)
    landing_daihatsu = 3000,

    /// @brief 揚陸攻撃(特大発動艇)
    landing_toku_daihatsu,

    /// @brief 揚陸攻撃(大発動艇(八九式中戦車&陸戦隊))
    landing_daihatsu_tank,

    /// @brief 揚陸攻撃(特二式内火艇)
    landing_amphibious,

    /// @brief 揚陸攻撃(特大発動艇+戦車第11連隊)
    landing_toku_daihatsu_tank,
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_ENUM_DAY_ATTACK_KIND_HPP_INCLUDED
