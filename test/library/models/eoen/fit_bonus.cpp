#include "kcv/external/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"

// std
#include <filesystem>
#include <vector>

// kcv
#include "core/json/read_json.hpp"

int main() {
    constexpr auto dir = "./test/library/models/eoen/fit_bonus/data";
    for (const auto& file : std::filesystem::directory_iterator{dir}) {
        auto dst = std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>{};
        kcv::read_json(dst, file.path());
    }
}