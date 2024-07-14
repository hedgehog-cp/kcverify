#include <print>

#include "battlelog/battlelog.hpp"
#include "csv/document.hpp"

int main() {
    for (auto doc = kcv::csv::document{"赤仮砲撃戦.csv"}; const auto& row : doc) {
        const auto battlelog = kcv::battlelog{row};
        const auto& attacker = battlelog.attacker();

        const auto name = attacker.name();
        std::print("{} ", name.view());

        for (const auto slot = attacker.mst_slot(); const auto& e : slot) {
            std::print("{}, ", e.name());
        }
        std::println("");
    }
}