// std
#include <filesystem>

// kcv
#include "common.hpp"
#include "kcsapi/api_get_member/ship_deck/response.hpp"
#include "kcsapi/types/svdata.hpp"

// kcv::test
#include "root.hpp"

int main() {
    const auto dir = kcv::test::root / "test/kcsapi/api_get_member/ship_deck/response";
    for (const auto& e : std::filesystem::directory_iterator{dir}) {
        auto data = kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>{};
        kcv::read_json(data, e.path());
    }
}