#ifndef KCVERIFY_kcsapi_TYPES_ENUM_CELL_TYPE_HPP_INCLUDED
#define KCVERIFY_kcsapi_TYPES_ENUM_CELL_TYPE_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

/// @brief セルタイプ.
enum class cell_type {
    unknown = -1,

    /// @brief 初期位置.
    start = 0,

    /// @brief 資源獲得.
    resource = 2,

    /// @brief 渦潮.
    maelstrom = 3,

    /// @brief 通常戦闘, 気のせいだった.
    normal_battle_or_it_was_just_my_imagination = 4,

    /// @brief ボス戦闘.
    boss_battle = 5,

    /// @brief 揚陸地点.
    landing_point = 6,

    /// @brief 航空戦.
    air_battle = 7,

    /// @brief 船団護衛成功.
    successful_convoy_escort = 8,

    /// @brief 航空偵察.
    aerial_reconnaissance = 9,

    /// @brief 長距離空襲戦.
    long_range_air_battle = 10,

    /// @brief 開幕夜戦.
    night_battle = 11,

    /// @brief レーダー射撃.
    radar_fire = 13,

    /// @brief 泊地.
    anchorage = 14,

    /// @brief 対潜空襲.
    sub_air = 15,
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_kcsapi_TYPES_ENUM_CELL_TYPE_HPP_INCLUDED
