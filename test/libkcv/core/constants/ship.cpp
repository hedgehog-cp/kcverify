#include "core/constants/ship.hpp"

// std
#include <cstdlib>
#include <filesystem>

// kcv
#include "core/common/kcsapi.hpp"
#include "core/common/read_json.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"

int main() {
    using kcv::literals::ship_literals::operator""_id;

    static_assert("Jervis"_id == kcv::kcsapi::ship_id{519});
    static_assert("金剛改二丙"_id == kcv::kcsapi::ship_id{591});

    const auto api_mst_ship = []() static -> kcv::kcsapi::api_mst_ship {
        auto temp = kcv::kcsapi::api_mst_ship{};
        kcv::read_json(temp, std::filesystem::path{"./assets/api_mst_ship.json"});
        return temp;
    }();

    const auto& maruyu = kcv::binary_search(api_mst_ship, "まるゆ"_id);
    if (not kcv::is_submarine(maruyu)) {
        return EXIT_FAILURE;
    }
}