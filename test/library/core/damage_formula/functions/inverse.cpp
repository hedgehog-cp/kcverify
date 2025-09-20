#include "core/damage_formula/functions/inverse.hpp"

// std
#include <cassert>
#include <cmath>
#include <cstddef>
#include <optional>
#include <print>
#include <random>
#include <tuple>
#include <type_traits>
#include <utility>

// kcv
#include "core/damage_formula/functions/function_composition.hpp"
#include "core/damage_formula/functions/modifier_functions.hpp"
#include "extensions/formatter.hpp"
#include "extensions/interval.hpp"
#include "extensions/utility.hpp"

int main() {
    auto seed_gen  = std::random_device{};
    auto engine    = std::default_random_engine{seed_gen()};
    auto dist_1_2  = std::uniform_real_distribution<>{1, 2};
    auto dist_0_50 = std::uniform_real_distribution<>{0, 50};

    for (int _ = 0; _ < 1; _++) {
        const auto f1 = kcv::liner_fn{dist_1_2(engine), dist_0_50(engine)};
        const auto f2 = kcv::liner_fn{dist_1_2(engine), dist_0_50(engine)};
        const auto f3 = kcv::liner_fn{dist_1_2(engine), dist_0_50(engine)};
        const auto f4 = kcv::liner_fn{dist_1_2(engine), dist_0_50(engine)};

        const auto f = f1 | f2 | f3 | f4;
        const auto x = std::fabs(dist_0_50(engine) * 2 + 20);
        const auto y = f(x);

        std::println("x = {}", x);
        std::println("y = {}", y);

        const auto result = kcv::inverse(x, kcv::make_interval(y) + kcv::interval{-1, 1}, f);

        []<std::size_t... I>(const auto& tuple, std::index_sequence<I...>) {
            const auto print = kcv::overloaded{
                [](const auto&) { std::println("---"); },
                [](const std::optional<kcv::inverse_result<kcv::liner_fn>>& v) {
                    std::println("a ∊ {}; b ∊ {}", v->a, v->b);
                },
            };
            (..., print(std::get<I>(tuple)));
        }(result, std::make_index_sequence<std::tuple_size_v<decltype(result)>>{});

        std::println("");
    }
}
