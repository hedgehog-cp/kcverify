#include <cassert>

#include "damage_formula/modifier/composition.hpp"
#include "damage_formula/modifier/liner.hpp"
#include "damage_formula/modifier/softcap.hpp"
#include "numeric.hpp"

namespace {

template <typename T>
constexpr auto f(const T x) {
    const auto f1      = kcv::mod::liner<T>{1.5, 10.0};
    const auto f2      = kcv::mod::liner<T>{1.2, 30.0};
    const auto f3      = kcv::mod::liner<T>{1.0, 100.0};
    const auto softcap = kcv::mod::softcap<220>{};
    const auto y       = (f1 | f2 | f2 ^ -1 | f3 | softcap | softcap ^ -1)(x);

    return y;
}

}  // namespace

int main() {
    constexpr int x = 120;

    {
        const auto eps = 1e-12;
        const auto y   = f<kcv::float64_t>(x).value();
        assert(std::abs(y - 290.0) <= eps);
    }

    {
        const auto y = f<kcv::interval>(x).value();
        assert(y.lower() <= 290.0 and 290.0 <= y.upper());
    }
}
