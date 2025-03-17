// std
#include <filesystem>
#include <vector>

// kcv
#include "eoen/database/sortie/sortie_record.hpp"
#include "read_json.hpp"

// kcv::test
#include "root.hpp"

int main() {
    const auto dir = kcv::test::root / "test/eoen/sortie_record/sortie_record";

    for (const auto& fname : std::filesystem::directory_iterator{dir}) {
        auto dst = std::vector<kcv::eoen::database::sortie::sortie_record>{};
        kcv::read_json(dst, fname.path());
    }
}