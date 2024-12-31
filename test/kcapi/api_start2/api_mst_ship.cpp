// std
#include <filesystem>

// kcv
#include "json/read_json.hpp"
#include "kcapi/api_start2/api_mst_ship.hpp"

// kcv::test
#include "root.hpp"

int main() {
    const auto dir = kcv::test::root / "test/kcapi/api_start2/api_mst_ship";
    for (const auto& e : std::filesystem::directory_iterator{dir}) {
        auto data = kcv::kcapi::api_mst_ship{};
        kcv::read_json(data, e.path());
    }
}
