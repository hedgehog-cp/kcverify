// std
#include <cassert>
#include <limits>
#include <print>

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

constexpr auto g1(const auto &x) noexcept {
    return x;
}

}  // namespace mod
}  // namespace kcv

namespace {

constexpr auto g2(const auto &x) noexcept {
    return x;
}

template <typename T>
constexpr auto f(const T &x) {
    const auto f1     = kcv::mod::liner<T>{1.5, 10.0};
    const auto f2     = kcv::mod::liner<T>{1.25, 20.0};
    const auto precap = &kcv::mod::g1<T> | f1 | f2 | &g2<const T &>;

    const auto softcap = kcv::mod::softcap<220>{};

    const auto floor    = kcv::mod::floor_if{true};
    const auto f3       = kcv::mod::liner<T>{1.0, 100.0};
    const auto pt       = kcv::mod::pt{};
    const auto critical = kcv::mod::critical{true};
    const auto postcap  = floor | f3 | pt | critical;

    const auto func = precap | softcap | postcap;
    const auto inv  = (critical ^ -1) | (pt ^ -1) | (f3 ^ -1) | (floor ^ -1) | (softcap ^ -1) | (f2 ^ -1) | (f1 ^ -1);

    const auto y = (func | inv)(x);

    return y;
}

void test(auto x) {
    {
        if (const auto y = f<kcv::float64_t>(x); y.has_value()) {
            std::println("[{:.16f}, {:.16f}]", y->lower(), y->upper());
            assert(y->lower() <= x and x <= y->upper());
        } else {
            std::println("no value");
        }
    }

    if (const auto y = f<kcv::interval>(x); y.has_value()) {
        std::println("[{:.16f}, {:.16f}]", y->lower(), y->upper());
        assert(y->lower() <= x and x <= y->upper());
    } else {
        std::println("no value");
    }
}

}  // namespace

int main() {
    test(100);
    test(0);
    test(1);

    test(99);
    test(101);
    test(99.999999999999999);
    test(100.99999999999999);

    test(-17.33333333333332);
    test(-17.33333333333333);
    test(-17.33333333333334);

    test(-9999);

    // 未対応:
    // test(std::numeric_limits<kcv::float64_t>::quiet_NaN());
    // test(-std::numeric_limits<kcv::float64_t>::infinity());
    // test(std::numeric_limits<kcv::float64_t>::infinity());
}
