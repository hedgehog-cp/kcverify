#include "models/kcsapi/api_req_map/next/response.hpp"

// std
#include <filesystem>

// kcv
#include "core/json/read_json.hpp"
#include "models/kcsapi/types/svdata.hpp"

int main() {
    constexpr auto dir = "./test/library/models/kcsapi/api_req_map/next/data/response";
    for (const auto& file : std::filesystem::directory_iterator{dir}) {
        auto dst = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>{};
        kcv::read_json(dst, file.path());
    }
}