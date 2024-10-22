// std
#include <filesystem>

// kcv
#include "kcapi/api_req_map/start/request.hpp"

// kcv::test
#include "read_and_write_json.hpp"
#include "root.hpp"

int main() {
    using value_type = kcv::kcapi::api_req_map::start::request;
    const auto dir   = std::filesystem::path{"test/kcapi/api_req_map/start"};

    const int result = kcv::test::read_and_write_json<value_type>(kcv::test::root / dir / "request.json");

    return result;
}
