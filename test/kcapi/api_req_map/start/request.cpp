// std
#include <filesystem>

// kcv
#include "json/read_json.hpp"
#include "kcapi/api_req_map/start/request.hpp"

// kcv::test
#include "root.hpp"

int main() {
    const auto dir = kcv::test::root / "test/kcapi/api_req_map/start/request";
    for (const auto& e : std::filesystem::directory_iterator{dir}) {
        auto data = kcv::kcapi::api_req_map::start::request{};
        kcv::read_json(data, e.path());
    }
}