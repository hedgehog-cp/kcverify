#include "kcv/external/eoen/destination.hpp"

// std
#include <filesystem>
#include <print>

// kcv
#include "core/json/read_json.hpp"

int main() {
    const auto fname = std::filesystem::path{"assets/eoen/destination.json"};

    auto dst = kcv::eoen::destination{};
    kcv::read_json(dst, fname);

    std::println("{}", dst.version);
    for (int i = 2; const auto& [world, cells] : dst.worlds) {
        std::println("{}", world);
        for (const auto& [cell, names] : cells) {
            std::println("    {}: {}", cell, names);
        }

        if (--i == 0) break;
    }
}