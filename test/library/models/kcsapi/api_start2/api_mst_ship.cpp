#include "models/kcsapi/api_start2/api_mst_ship.hpp"

// std
#include <filesystem>

// kcv
#include "core/json/read_json.hpp"

int main() {
    constexpr auto dir = "./test/library/models/kcsapi/api_start2/data/api_mst_ship";
    for (const auto& file : std::filesystem::directory_iterator{dir}) {
        auto dst = kcv::kcsapi::api_mst_ship{};
        kcv::read_json(dst, file.path());
    }
}