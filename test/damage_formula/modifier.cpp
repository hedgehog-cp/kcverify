// std
#include <cassert>

// kcv
#include "damage_formula/modifier/composition.hpp"
#include "damage_formula/modifier/critical.hpp"
#include "damage_formula/modifier/floor_if.hpp"
#include "damage_formula/modifier/liner.hpp"
#include "damage_formula/modifier/pt.hpp"
#include "damage_formula/modifier/softcap.hpp"
#include "numeric.hpp"

namespace kcv {
namespace mod {

// using namespace kcv::mod;
constexpr auto g(const auto &x) noexcept {
    return x;
}
}  // namespace mod
}  // namespace kcv

namespace {

template <typename T>
constexpr auto f(const T &x) {
    const auto f1       = kcv::mod::liner<T>{1.5, 10.0};
    const auto f2       = kcv::mod::liner<T>{1.2, 30.0};
    const auto softcap  = kcv::mod::softcap<220>{};
    const auto floor    = kcv::mod::floor_if{true};
    const auto f3       = kcv::mod::liner<T>{1.0, 100.0};
    const auto pt       = kcv::mod::pt{};
    const auto critical = kcv::mod::critical{true};

    const auto func     = f1 | f2 | softcap | floor | f3 | pt | critical | &kcv::mod::g<T> | &kcv::mod::g<const T &>;
    const auto func_inv = critical ^ -1 | pt ^ 1 | f3 ^ -1 | floor ^ 1 | softcap ^ 1 | f2 ^ -1 | f1 ^ -1;

    const auto y = (func | func_inv)(x);

    return y;
}

}  // namespace

int main() {
    constexpr auto x = 123.4;

    {
        const auto y = f<kcv::float64_t>(x).value();
        assert(y.lower() <= x and x <= y.upper());
    }

    {
        const auto y = f<kcv::interval>(x).value();
        assert(y.lower() <= x and x <= y.upper());
    }
}
