#include "models/kcsapi/api_get_member/ship_deck/response.hpp"

// std
#include <filesystem>

// kcv
#include "core/common/read_json.hpp"
#include "models/kcsapi/types/svdata.hpp"

int main() {
    constexpr auto dir = "./test/library/models/kcsapi/api_get_member/ship_deck/data/response";
    for (const auto& file : std::filesystem::directory_iterator{dir}) {
        auto dst = kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>{};
        kcv::read_json(dst, file.path());
    }
}