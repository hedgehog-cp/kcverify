#include "kcv/external/kc3kai/bonus/bonus.hpp"

#include <filesystem>

#include "core/json/read_json.hpp"

int main() {
    constexpr auto dir = "./assets/kc3kai/bonus";
    for (const auto& file : std::filesystem::directory_iterator{dir}) {
        auto dst = kcv::kc3kai::bonus_map_t{};
        kcv::read_json(dst, file.path());
    }
}