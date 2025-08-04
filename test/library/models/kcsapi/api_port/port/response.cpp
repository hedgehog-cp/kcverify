/* データが無いため
#include "models/kcsapi/api_port/port/response.hpp"

// std
#include <filesystem>

// kcv
#include "core/common/read_json.hpp"

int main() {
    constexpr auto dir = "./test/library/models/kcsapi/api_port/port/data/response";
    for (const auto& file : std::filesystem::directory_iterator{dir}) {
        auto dst = kcv::kcsapi::api_port::port::response{};
        kcv::read_json(dst, file.path());
    }
}
*/