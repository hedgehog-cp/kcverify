// std
#include <cassert>
#include <cmath>
#include <optional>
#include <print>
#include <random>

// kcv
#include "core/common/formatter.hpp"
#include "core/damage_formula/functions/function_composition.hpp"
#include "core/damage_formula/functions/interval.hpp"
#include "core/damage_formula/functions/interval_formatter.hpp"
#include "core/damage_formula/functions/modifier_functions.hpp"

int main() {
    auto seed_gen  = std::random_device{};
    auto engine    = std::default_random_engine{seed_gen()};
    auto dist_1_2  = std::uniform_real_distribution<>{1, 2};
    auto dist_0_50 = std::uniform_real_distribution<>{0, 50};

    for (int _ = 0; _ < 10; _++) {
        const auto f1         = kcv::liner_fn{kcv::number{dist_1_2(engine)}, kcv::number{dist_0_50(engine)}};
        const auto f2         = kcv::liner_fn{kcv::number{dist_1_2(engine)}, kcv::number{dist_0_50(engine)}};
        const auto air_attack = kcv::air_attack_fn{.is_air_attack = true};
        const auto softcap    = kcv::softcap_fn{kcv::number{220}};
        const auto floor      = kcv::floor_fn{};
        const auto f3         = kcv::liner_fn{kcv::number{dist_1_2(engine)}, kcv::number{dist_0_50(engine)}};
        const auto pt         = kcv::pt_fn{};
        const auto critical   = kcv::critical_fn{.is_critical = true};
        const auto floor_if   = kcv::floor_if_fn{.is_flooring = true};

        const auto f = f1 | f2 | air_attack | softcap | floor | f3 | pt | critical | floor_if;
        const auto x = std::fabs(dist_0_50(engine) * 2 + 20);
        const auto y = f(kcv::number{x});

        std::println("x = {:.3f}", x);
        std::println("y = {:.3f}", y);

        const auto inv_x = (f ^ -1)(kcv::make_interval(*y));
        if (inv_x.has_value()) {
            if (kcv::in(x, *inv_x)) {
                std::println("x ∊ {:.3f}", *inv_x);
            } else {
                std::println("x ∉ {:.3f}", *inv_x);
            }
        } else {
            std::println("x = (null)");
        }

        std::println("");
    }
}