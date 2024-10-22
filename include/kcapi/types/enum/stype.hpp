#ifndef KCVERIFY_KCAPI_TYPES_ENUM_STYPE_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_ENUM_STYPE_HPP_INCLUDED

namespace kcv {
namespace kcapi {

/// @brief 艦種ID
enum class stype {
    /// @brief 海防艦
    de = 1,

    /// @brief 駆逐艦
    dd = 2,

    /// @brief 軽巡洋艦
    cl = 3,

    /// @brief 重雷装巡洋艦
    clt = 4,

    /// @brief 重巡洋艦
    ca = 5,

    /// @brief 航空巡洋艦
    cav = 6,

    /// @brief 軽空母
    cvl = 7,

    /// @brief 戦艦
    fbb = 8,

    /// @brief 戦艦
    bb = 9,

    /// @brief 航空戦艦
    bbv = 10,

    /// @brief 正規空母
    cv = 11,

    /// @brief 超弩級戦艦
    xbb = 12,

    /// @brief 潜水艦
    ss = 13,

    /// @brief 潜水空母
    ssv = 14,

    /// @brief 補給艦
    ap = 15,

    /// @brief 水上機母艦
    av = 16,

    /// @brief 揚陸艦
    lha = 17,

    /// @brief 装甲空母
    cvb = 18,

    /// @brief 工作艦
    ar = 19,

    /// @brief 潜水母艦
    as = 20,

    /// @brief 練習巡洋艦
    ct = 21,

    /// @brief 補給艦
    ao = 22,
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_ENUM_STYPE_HPP_INCLUDED
