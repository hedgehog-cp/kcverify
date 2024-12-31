#ifndef KCVERIFY_kcsapi_TYPES_ENUM_NIGHT_ATTACK_KIND_HPP_INCLUDED
#define KCVERIFY_kcsapi_TYPES_ENUM_NIGHT_ATTACK_KIND_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

/// @brief 夜戦攻撃種別
enum class night_attack_kind {
    /// @brief 不明
    unknown = -1,

    /// @brief 通常攻撃 (API上でのみ使用されます)
    normal_attack = 0,

    /// @brief 連続攻撃
    double_shelling = 1,

    /// @brief カットイン(主砲/魚雷)
    cutin_main_torpedo = 2,

    /// @brief カットイン(魚雷/魚雷)
    cutin_torpedo_torpedo = 3,

    /// @brief カットイン(主砲/主砲/副砲)
    cutin_main_sub = 4,

    /// @brief カットイン(主砲/主砲/主砲)
    cutin_main_main = 5,

    /// @brief 空母カットイン
    cutin_air_attack = 6,

    /// @brief 駆逐カットイン(主砲/魚雷/電探) 1Hit
    cutin_torpedo_radar = 7,

    /// @brief 駆逐カットイン(魚雷/見張員/電探) 1Hit
    cutin_torpedo_picket = 8,

    /// @brief 駆逐カットイン(魚雷/魚雷/水雷見張員) 1Hit
    cutin_torpedo_destroyer_picket = 9,

    /// @brief 駆逐カットイン(魚雷/ドラム/水雷見張員) 1Hit
    cutin_torpedo_drum = 10,

    /// @brief 駆逐カットイン(主砲/魚雷/電探) 2Hit
    cutin_torpedo_radar_2 = 11,

    /// @brief 駆逐カットイン(魚雷/見張員/電探) 2Hit
    cutin_torpedo_picket_2 = 12,

    /// @brief 駆逐カットイン(魚雷/魚雷/水雷見張員) 2Hit
    cutin_torpedo_destroyer_picket_2 = 13,

    /// @brief 駆逐カットイン(魚雷/ドラム/水雷見張員) 2Hit
    cutin_torpedo_drum_2 = 14,

    /// @brief Nelson Touch
    special_nelson = 100,

    /// @brief 一斉射かッ…胸が熱いな！
    special_nagato = 101,

    /// @brief 長門、いい？ いくわよ！ 主砲一斉射ッ！
    special_mutsu = 102,

    /// @brief Colorado Touch
    special_colorado = 103,

    /// @brief 僚艦夜戦突撃
    special_kongou = 104,

    /// @brief Richelieuよ！圧倒しなさいっ！
    special_richelieu = 105,

    /// @brief 夜間瑞雲カットイン
    cutin_zuiun = 200,

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
    air_attack = 1001,

    /// @brief 爆雷攻撃
    depth_charge = 1002,

    /// @brief 雷撃
    torpedo = 1003,

    /// @brief ロケット攻撃
    rocket = 2000,

    /// @brief 揚陸攻撃(大発動艇)
    landing_daihatsu = 3000,

    /// @brief 揚陸攻撃(特大発動艇)
    landing_toku_daihatsu = 3001,

    /// @brief 揚陸攻撃(大発動艇(八九式中戦車&陸戦隊))
    landing_daihatsu_tank = 3002,

    /// @brief 揚陸攻撃(特二式内火艇)
    landing_amphibious = 3004,

    /// @brief 揚陸攻撃(特大発動艇+戦車第11連隊)
    landing_toku_daihatsu_tank = 3005,
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_kcsapi_TYPES_ENUM_NIGHT_ATTACK_KIND_HPP_INCLUDED
