// std
#include <cassert>
#include <cmath>
#include <optional>
#include <print>
#include <random>

// kcv
#include "core/damage_formula/functions/composed_function.hpp"
#include "core/damage_formula/functions/modifier_functions.hpp"
#include "extensions/formatter.hpp"
#include "extensions/interval.hpp"

int main() {
    auto seed_gen = std::random_device{};
    auto engine   = std::default_random_engine{seed_gen()};
    auto r_1_2    = std::uniform_real_distribution<>{1, 2};
    auto r_0_50   = std::uniform_real_distribution<>{0, 50};

    for (int _ = 0; _ < 10; _++) {
        const auto f1 = kcv::modifiers::liner{.a = kcv::number{r_1_2(engine)}, .b = kcv::number{r_0_50(engine)}};
        const auto f2 = kcv::modifiers::liner{.a = kcv::number{r_1_2(engine)}, .b = kcv::number{r_0_50(engine)}};
        const auto air_attack = kcv::modifiers::air_attack{.is_enabled = true};
        const auto softcap    = kcv::modifiers::softcap{.cap = kcv::number{220}};
        const auto floor      = kcv::modifiers::floor{};
        const auto f3       = kcv::modifiers::liner{.a = kcv::number{r_1_2(engine)}, .b = kcv::number{r_0_50(engine)}};
        const auto pt       = kcv::modifiers::pt_imp{};
        const auto critical = kcv::modifiers::critical{.is_enabled = true};
        const auto floor_if = kcv::modifiers::floor{.is_enabled = true};

        const auto f = f1 | f2 | air_attack | softcap | floor | f3 | pt | critical | floor_if;
        const auto x = std::fabs(r_0_50(engine) * 2 + 20);
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