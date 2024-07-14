#ifndef KCVERIFY_BATTLELOG_SLOTDATA_HPP_INCLUDED
#define KCVERIFY_BATTLELOG_SLOTDATA_HPP_INCLUDED

#include "fixed_string.hpp"

namespace kcv {
namespace slotdata {

// 静的な文字列結合をしたいので, fixed_stringをNTTPで利用する.

struct name final {
    static constexpr auto suffix = fixstr::fixed_string<6>{"名前"};
};

struct level final {
    static constexpr auto suffix = fixstr::fixed_string<6>{"改修"};
};

struct alv final {
    static constexpr auto suffix = fixstr::fixed_string<9>{"熟練度"};
};

struct onslot final {
    static constexpr auto suffix = fixstr::fixed_string<9>{"搭載数"};
};

struct after_onslot final {
    static constexpr auto suffix = fixstr::fixed_string<18>{"戦闘後搭載数"};
};

}  // namespace slotdata
}  // namespace kcv

#endif  // KCVERIFY_BATTLELOG_SLOTDATA_HPP_INCLUDED
