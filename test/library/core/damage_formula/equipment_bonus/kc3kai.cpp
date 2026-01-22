// std
#include <cstdlib>
#include <filesystem>
#include <format>
#include <print>
#include <ranges>
#include <vector>

// kcv
#include "core/damage_formula/equipment_bonus.hpp"
#include "core/entity/adapter/from_eoen.hpp"
#include "core/entity/ship.hpp"
#include "core/json/read_json.hpp"
#include "kcv/external/eoen/database/sortie/sortie_record.hpp"
#include "kcv/external/kc3kai/mst_slotitem_bonus.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_ship.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"

template <>
struct std::formatter<kcv::kc3kai::bonus_value> {
    std::formatter<std::int32_t> int32_t_formatter;

    constexpr auto parse(std::format_parse_context& ctx) {
        return int32_t_formatter.parse(ctx);
    }

    template <typename FormatContext>
    constexpr auto format(const kcv::kc3kai::bonus_value& bonus, FormatContext& ctx) const {
        auto out = ctx.out();
        out      = std::format_to(out, "houg: ");
        out      = int32_t_formatter.format(bonus.houg, ctx);
        out      = std::format_to(out, ", tyku: ");
        out      = int32_t_formatter.format(bonus.tyku, ctx);
        out      = std::format_to(out, ", kaih: ");
        out      = int32_t_formatter.format(bonus.kaih, ctx);
        out      = std::format_to(out, ", souk: ");
        out      = int32_t_formatter.format(bonus.souk, ctx);
        out      = std::format_to(out, ", houm: ");
        out      = int32_t_formatter.format(bonus.houm, ctx);
        out      = std::format_to(out, ", tais: ");
        out      = int32_t_formatter.format(bonus.tais, ctx);
        out      = std::format_to(out, ", raig: ");
        out      = int32_t_formatter.format(bonus.raig, ctx);
        out      = std::format_to(out, ", saku: ");
        out      = int32_t_formatter.format(bonus.saku, ctx);
        out      = std::format_to(out, ", leng: ");
        out      = int32_t_formatter.format(bonus.leng, ctx);
        out      = std::format_to(out, ", baku: ");
        out      = int32_t_formatter.format(bonus.baku, ctx);
        return out;
    }
};

namespace {

bool operator==(const kcv::kc3kai::bonus_value& lhs, const kcv::kc3kai::bonus_value& rhs) noexcept {
    return lhs.houg == rhs.houg   //
       and lhs.tyku == rhs.tyku   //
       and lhs.kaih == rhs.kaih   //
       and lhs.souk == rhs.souk   //
       and lhs.houm == rhs.houm   //
       and lhs.tais == rhs.tais   //
       and lhs.raig == rhs.raig   //
       and lhs.saku == rhs.saku   //
       and lhs.leng == rhs.leng   //
       and lhs.baku == rhs.baku;  //
}

}  // namespace

int main() {
    const auto api_mst_ship = []() static -> kcv::kcsapi::api_mst_ship {
        auto temp = kcv::kcsapi::api_mst_ship{};
        kcv::read_json(temp, std::filesystem::path{"./assets/api_mst_ship.json"});
        return temp;
    }();

    const auto api_mst_slotitem = []() static -> kcv::kcsapi::api_mst_slotitem {
        auto temp = kcv::kcsapi::api_mst_slotitem{};
        kcv::read_json(temp, std::filesystem::path{"./assets/api_mst_slotitem.json"});
        return temp;
    }();

    const auto bonus_list = []() static -> std::vector<kcv::kc3kai::mst_slotitem_bonus> {
        auto temp = std::vector<kcv::kc3kai::mst_slotitem_bonus>{};
        kcv::read_json(temp, std::filesystem::path{"./assets/kc3kai/mst_slotitem_bonus.json"});
        return temp;
    }();

    constexpr auto dir = "./test/library/core/damage_formula/equipment_bonus/data";
    for (const auto& dir : std::filesystem::directory_iterator{dir}) {
        const auto sortie_record = [](const auto& fname) static {
            auto temp = std::vector<kcv::eoen::database::sortie::sortie_record>{};
            kcv::read_json(temp, fname);
            return temp.front();
        }(dir.path() / "sortie_record.json");

        const auto expected = [](const auto& fname) static {
            auto temp = std::vector<kcv::kc3kai::bonus_value>{};
            kcv::read_json(temp, fname);
            return temp;
        }(dir.path() / "expected.json");

        const auto& ships = sortie_record.fleet_data.fleets.front()->ships;
        if (ships.size() != expected.size()) {
            return EXIT_FAILURE;
        }

        for (const auto& [eoen_ship, bonus] : std::ranges::views::zip(ships, expected)) {
            const auto sortie_ship     = kcv::ship_from_eoen(eoen_ship, api_mst_ship, api_mst_slotitem);
            const auto equipment_bonus = kcv::total_equipment_bonus(sortie_ship, bonus_list);
            if (equipment_bonus != bonus) {
                std::println("{}", sortie_ship.mst().api_name);
                std::println("calculated: {:>2}", equipment_bonus);
                std::println("expected:   {:>2}", bonus);
                std::println("");

                return EXIT_FAILURE;
            }
        }
    }
}