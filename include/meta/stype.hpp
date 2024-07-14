#ifndef KCVERIFY_META_STYPE_HPP_INCLUDED
#define KCVERIFY_META_STYPE_HPP_INCLUDED

namespace kcv {

enum class stype_t {
    de  = 1,   // 海防艦
    dd  = 2,   // 駆逐艦
    cl  = 3,   // 軽巡洋艦
    clt = 4,   // 重雷装巡洋艦
    ca  = 5,   // 重巡洋艦
    cav = 6,   // 航空巡洋艦
    cvl = 7,   // 軽空母
    fbb = 8,   // 戦艦
    bb  = 9,   // 戦艦
    bbv = 10,  // 航空戦艦
    cv  = 11,  // 正規空母
    xbb = 12,  // 超弩級戦艦
    ss  = 13,  // 潜水艦
    ssv = 14,  // 潜水空母
    ap  = 15,  // 補給艦
    av  = 16,  // 水上機母艦
    lha = 17,  // 揚陸艦
    cvb = 18,  // 装甲空母
    ar  = 19,  // 工作艦
    as  = 20,  // 潜水母艦
    ct  = 21,  // 練習巡洋艦
    ao  = 22,  // 補給艦
};

}  // namespace kcv

#endif  // KCVERIFY_META_STYPE_HPP_INCLUDED
