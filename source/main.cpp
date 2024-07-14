#include <print>
#include <ranges>
#include <string_view>
#include <utility>
#include <vector>

#include "csv/document.hpp"
#include "master/equipment/convert.hpp"
#include "master/equipment/equipment.hpp"
#include "master/ship/ship.hpp"

int main() {
    for (auto doc = kcv::csv::document{"赤仮砲撃戦.csv"}; const auto& row : doc) {
        const auto id   = row["攻撃艦.ID"].optional<kcv::ship_t::id_type>().value_or(kcv::ship_t::id_type{0});
        const auto name = row["攻撃艦.名前"].view();

        const auto slot = std::array<std::string_view, 6>{
            row["攻撃艦.装備1.名前"].view(),  //
            row["攻撃艦.装備2.名前"].view(),  //
            row["攻撃艦.装備3.名前"].view(),  //
            row["攻撃艦.装備4.名前"].view(),  //
            row["攻撃艦.装備5.名前"].view(),  //
            row["攻撃艦.装備6.名前"].view(),  //
        };

        std::print("{:6}, {} ", std::to_underlying(id), name);

        const auto slot_mst = slot  //
                            | std::ranges::views::transform([&](const auto& e) { return kcv::to_master(e); })
                            | std::ranges::to<std::vector<kcv::equipment_t>>();

        for (const auto& e : slot_mst) {
            std::print("{}, ", e.name());
        }
        std::println("");
    }
}