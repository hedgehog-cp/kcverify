#include "extensions/ranges.hpp"

#include <array>
#include <cstdlib>
#include <optional>
#include <vector>

int main() {
    // kcv::ranges::views::concat
    {
        int total = 0;

        auto vec = std::vector<int>{1, 2, 3, 4, 5};
        auto opt = std::optional<int>{6};

        for (int &i : kcv::ranges::views::concat(vec, opt)) {
            i *= 100;
        }

        for (const int &i : kcv::ranges::views::concat(vec, opt)) {
            total += i;
        }

        if (total != 6 * (6 + 1) / 2 * 100) {
            return EXIT_FAILURE;
        }
    }

    // kcv::ranges::views::zip_members
    {
        auto total = std::array<int, 3>{0, 0, 0};

        struct aggregate_t {
            std::vector<int> vec1 = {1, 10, 100};
            std::vector<int> vec2 = {2, 20, 200};
            std::vector<int> vec3 = {3, 30, 300};
        } aggregate;

        for (auto i = 0uz; const auto &[v1, v2, v3] : kcv::ranges::views::zip_members(aggregate)) {
            total[i++] = v1 + v2 + v3;
        }

        if (total[0] != 1 + 2 + 3) {
            return EXIT_FAILURE;
        }
        if (total[1] != 10 + 20 + 30) {
            return EXIT_FAILURE;
        }
        if (total[2] != 100 + 200 + 300) {
            return EXIT_FAILURE;
        }
    }
}