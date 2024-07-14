#ifndef KCVERIFY_BATTLELOG_SHIP_PREFIX_HPP_INCLUDED
#define KCVERIFY_BATTLELOG_SHIP_PREFIX_HPP_INCLUDED

#include "fixed_string.hpp"

namespace kcv {

struct attacker_prefix final {
    static constexpr auto value = fixstr::fixed_string<9>{"攻撃艦"};
};

struct defender_prefix final {
    static constexpr auto value = fixstr::fixed_string<9>{"防御艦"};
};

}  // namespace kcv

#endif  // KCVERIFY_BATTLELOG_SHIP_PREFIX_HPP_INCLUDED
