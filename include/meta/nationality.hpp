#ifndef KCVERIFY_META_NATIONALITY_HPP_INCLUDED
#define KCVERIFY_META_NATIONALITY_HPP_INCLUDED

#include <cassert>
namespace kcv {

enum class nationality_t {
    abyssal    = 0,
    japanese   = 1,
    german     = 2,
    italian    = 3,
    american   = 4,
    british    = 5,
    french     = 6,
    russian    = 7,
    swedish    = 8,
    dutch      = 9,
    australian = 10,
};

consteval auto to_nationality(int sort_id) noexcept -> nationality_t {
    if (sort_id == 0) return nationality_t::abyssal;

    if (sort_id < 1000) {
        assert(false);
    }

    if (sort_id < 30000) return nationality_t::japanese;
    if (sort_id < 31000) return nationality_t::german;
    if (sort_id < 32000) return nationality_t::italian;
    if (sort_id < 33000) return nationality_t::american;
    if (sort_id < 34000) return nationality_t::british;
    if (sort_id < 35000) return nationality_t::french;
    if (sort_id < 36000) return nationality_t::russian;
    if (sort_id < 37000) return nationality_t::swedish;
    if (sort_id < 38000) return nationality_t::dutch;
    if (sort_id < 39000) return nationality_t::australian;

    assert(false);
}

}  // namespace kcv

#endif  // KCVERIFY_META_NATIONALITY_HPP_INCLUDED
