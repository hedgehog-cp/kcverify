#include "extensions/interval.hpp"

// std
#include <cstdlib>
#include <print>

// kcv
#include "extensions/formatter.hpp"

int main() {
    {
        const auto a = kcv::interval{0.1};
        const auto b = kcv::interval{0.2};
        const auto c = a + b;
        if (not kcv::in(0.3, c)) {
            std::println("{} ∉ {} + {}", c, a, b);
            return EXIT_FAILURE;
        }
    }

    {
        const auto x = kcv::interval{2};
        const auto y = kcv::sqrt(x);
        if (not kcv::in(2.0, y * y)) {
            std::println("{} ∉ {} * {}", 2.0, y, y);
            return EXIT_FAILURE;
        }
        if (not kcv::in(2.0, kcv::square(y))) {
            std::println("{} ∉ {} ^ 2", 2.0, y);
            return EXIT_FAILURE;
        }
    }
}