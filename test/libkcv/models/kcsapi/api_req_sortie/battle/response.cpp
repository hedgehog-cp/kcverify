#include "models/kcsapi/api_req_sortie/battle/response.hpp"

// std
#include <filesystem>

// kcv
#include "core/common/read_json.hpp"
#include "models/kcsapi/types/svdata.hpp"

int main() {
    constexpr auto dir = "./test/libkcv/models/kcsapi/api_req_sortie/battle/data/response";
    for (const auto& file : std::filesystem::directory_iterator{dir}) {
        auto dst = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>{};
        kcv::read_json(dst, file.path());
    }
}