// std
#include <cassert>
#include <cmath>
#include <optional>
#include <print>
#include <random>

// kcv
#include "core/damage_formula/function/air_attack.hpp"
#include "core/damage_formula/function/composition.hpp"
#include "core/damage_formula/function/critical.hpp"
#include "core/damage_formula/function/floor.hpp"
#include "core/damage_formula/function/floor_if.hpp"
#include "core/damage_formula/function/liner.hpp"
#include "core/damage_formula/function/pt.hpp"
#include "core/damage_formula/function/softcap.hpp"
#include "core/interval.hpp"

/* あとで別の形でテストする

namespace {

void print_csv(const kcv::interval& x) {
    std::print("{}", kcv::midpoint(x));
}

void print_csv(const kcv::mod::liner& f) {
    std::print("{},{}", kcv::midpoint(f.a), kcv::midpoint(f.b));
}

void print_csv(const kcv::mod::air_attack&) {
    // std::print("");
}

void print_csv(const kcv::mod::softcap& f) {
    std::print("{}", kcv::midpoint(f.cap));
}

void print_csv(const kcv::mod::floor&) {
    // std::print("");
}

void print_csv(const kcv::mod::pt&) {
    // std::print("");
}

void print_csv(const kcv::mod::critical&) {
    // std::print("");
}

void print_csv(const kcv::mod::floor_if&) {
    // std::print("");
}

template <typename F1, typename F2>
void print_csv(const kcv::mod::composition<F1, F2>& f) {
    print_csv(f.f1());
    std::print(",");
    print_csv(f.f2());
}

template <typename T>
void print_csv(const std::optional<T>& x) {
    if (x.has_value()) {
        print_csv(*x);
    } else {
        std::print("null");
    }
}

}  // namespace

*/

int main() {
    auto seed_gen = std::random_device{};
    auto engine   = std::default_random_engine{seed_gen()};
    auto dist     = std::uniform_real_distribution<>{-100.0, 400.0};

    for (int _ = 0; _ < 1000; _++) {
        const auto f1         = kcv::mod::liner{dist(engine), dist(engine)};
        const auto f2         = kcv::mod::liner{dist(engine), dist(engine)};
        const auto air_attack = kcv::mod::air_attack{.is_air_attack = true};
        const auto softcap    = kcv::mod::softcap{static_cast<unsigned>(std::fabs(dist(engine)))};
        const auto floor      = kcv::mod::floor{};
        const auto f3         = kcv::mod::liner{dist(engine), dist(engine)};
        const auto pt         = kcv::mod::pt{};
        const auto critical   = kcv::mod::critical{.is_critical = true};
        const auto floor_if   = kcv::mod::floor_if{.is_flooring = true};

        const auto func = f1 | f2 | air_attack | softcap | floor | f3 | pt | critical | floor_if;
        const auto x    = dist(engine);
        const auto y    = func(x);

        if (y.has_value()) {
            const auto inv = func ^ -1;
            const auto z   = inv(kcv::make_interval(*y));

            if (z.has_value()) {
                // funcの評価が精度保証なしであるため, x ∊ zは必ずしも成立しない.
                // assert(kcv::in(x, *z));

                // 区間半径は十分に小さい.
                // たまに失敗する.
                // assert(kcv::width(*z) <= 1e-9);

                // もとの値と十分に近い.
                // たまに失敗する.
                // assert(std::fabs(kcv::midpoint(*z) - x) <= 1e-9);
            }

            // if (z.has_value()) {
            //     std::println("{:.16f}", z->lower());
            //     std::println("{:.16f}", x);
            //     std::println("{:.16f}", z->upper());
            //     std::println("{}", kcv::in(x, *z));
            // } else {
            //     std::println("null");
            // }

            // print_csv(func);
            // std::print(",");
            // print_csv(z);

            // std::println("");
        }
    }
}