#include "models/kcsapi/api_req_map/start/request.hpp"

// std
#include <filesystem>

// kcv
#include "core/common/read_json.hpp"

int main() {
    constexpr auto dir = "./test/libkcv/models/kcsapi/api_req_map/start/data/request";
    for (const auto& file : std::filesystem::directory_iterator{dir}) {
        auto dst = kcv::kcsapi::api_req_map::start::request{};
        kcv::read_json(dst, file.path());
    }
}