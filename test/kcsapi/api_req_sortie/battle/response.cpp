// std
#include <filesystem>

// kcv
#include "json/read_json.hpp"
#include "kcsapi/api_req_sortie/battle/response.hpp"
#include "kcsapi/types/svdata.hpp"

// kcv::test
#include "root.hpp"

int main() {
    const auto dir = kcv::test::root / "test/kcsapi/api_req_sortie/battle/response";
    for (const auto& e : std::filesystem::directory_iterator{dir}) {
        auto data = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>{};
        kcv::read_json(data, e.path());
    }
}
