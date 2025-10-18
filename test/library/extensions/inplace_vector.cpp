#include "extensions/inplace_vector.hpp"

#include <cstdlib>
#include <new>
#include <ranges>
#include <variant>

int main() {
    static_assert(std::ranges::contiguous_range<kcv::inplace_vector<std::monostate, 1uz>>);

    {
        constexpr auto vec = kcv::inplace_vector<int, 5>{0, 1, 2};
        static_assert(vec.size() == 3uz);
        static_assert(vec[0] == 0);
        static_assert(vec[1] == 1);
        static_assert(vec[2] == 2);
    }

    try {
        const auto _ = kcv::inplace_vector<int, 2uz>{1, 2, 3};
        return EXIT_FAILURE;
    } catch (const std::bad_alloc &) {
        // ok
    }

    {
        constexpr auto vec = std::ranges::views::iota(0, 3) | std::ranges::to<kcv::inplace_vector<int, 5>>();
        static_assert(vec.size() == 3uz);
        static_assert(vec[0] == 0);
        static_assert(vec[1] == 1);
        static_assert(vec[2] == 2);
    }

    try {
        const auto _ = std::ranges::views::iota(0, 3) | std::ranges::to<kcv::inplace_vector<int, 2>>();
        return EXIT_FAILURE;
    } catch (const std::bad_alloc &) {
        // ok
    }
}