#include "models/eoen/database/sortie/sortie_record.hpp"

// std
#include <filesystem>
#include <vector>

// kcv
#include "core/common/read_json.hpp"

int main() {
    constexpr auto dir = "./test/libkcv/models/eoen/sortie_record/data";
    for (const auto& file : std::filesystem::directory_iterator{dir}) {
        auto dst = std::vector<kcv::eoen::database::sortie::sortie_record>{};
        kcv::read_json(dst, file.path());
    }
}