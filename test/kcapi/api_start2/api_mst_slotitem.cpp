// std
#include <filesystem>

// kcv
#include "kcapi/api_start2/api_mst_slotitem.hpp"

// kcv::test
#include "read_and_write_json.hpp"
#include "root.hpp"

int main() {
    using value_type = kcv::kcapi::api_mst_slotitem;
    const auto dir   = std::filesystem::path{"test/kcapi/api_start2"};

    const int result = kcv::test::read_and_write_json<value_type>(kcv::test::root / dir / "api_mst_slotitem.json");

    return result;
}
