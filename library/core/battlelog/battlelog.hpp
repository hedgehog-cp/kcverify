#ifndef KCVERIFY_CORE_BATTLELOG_BATTLELOG_HPP_INCLUDED
#define KCVERIFY_CORE_BATTLELOG_BATTLELOG_HPP_INCLUDED

// std
#include <cstdint>

// kcv
#include "core/entity/ship.hpp"

namespace kcv {

struct battlelog final {
    kcv::ship attacker;
    kcv::ship defender;
    std::int32_t damage;
    bool is_protected;
};

}  // namespace kcv

#endif  // KCVERIFY_CORE_BATTLELOG_BATTLELOG_HPP_INCLUDED
