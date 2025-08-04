#include "core/constants/equipment.hpp"

// std
#include <cstdlib>
#include <filesystem>

// kcv
#include "core/utility/kcsapi.hpp"
#include "core/utility/read_json.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"

int main() {
    using kcv::literals::equipment_literals::operator""_id;

    static_assert("烈風改二(一航戦/熟練)"_id == kcv::kcsapi::equipment_id{337});
    static_assert("流星改(一航戦/熟練)"_id == kcv::kcsapi::equipment_id{343});

    const auto api_mst_slotitem = []() static -> kcv::kcsapi::api_mst_slotitem {
        auto temp = kcv::kcsapi::api_mst_slotitem{};
        kcv::read_json(temp, std::filesystem::path{"./assets/api_mst_slotitem.json"});
        return temp;
    }();

    const auto& bogata = kcv::find_mst(api_mst_slotitem, "烈風改二戊型(一航戦/熟練)"_id);
    if (not kcv::is_night_plane(bogata)) {
        return EXIT_FAILURE;
    }
}