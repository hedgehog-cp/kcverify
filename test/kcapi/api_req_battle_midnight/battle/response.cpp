// std
#include <filesystem>

// kcv
#include "json/read_json.hpp"
#include "kcapi/api_req_battle_midnight/battle/response.hpp"
#include "kcapi/types/svdata.hpp"

// kcv::test
#include "root.hpp"

int main() {
    const auto dir = kcv::test::root / "test/kcapi/api_req_battle_midnight/battle/response";
    for (const auto& e : std::filesystem::directory_iterator{dir}) {
        auto data = kcv::kcapi::svdata<kcv::kcapi::api_req_battle_midnight::battle::response>{};
        kcv::read_json(data, e.path());
    }
}