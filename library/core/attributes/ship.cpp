#include "core/attributes/ship.hpp"

// std
#include <algorithm>
#include <ranges>
#include <string_view>

// kcv
#include "core/constants/ship.hpp"
#include "extensions/inplace_vector.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"

bool kcv::is_abyssal_ship(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    return kcv::is_abyssal_ship_id(mst.api_id);
}

bool kcv::is_installation(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    return mst.api_soku == 0;
}

bool kcv::is_pillbox(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    static constexpr auto ids = kcv::detail::api_mst_ship
                              | std::ranges::views::filter([](const auto& e) static -> bool {
                                    const auto& [_, api_name] = e;
                                    using std::literals::string_view_literals::operator""sv;
                                    return api_name == "砲台小鬼"sv              //
                                        or api_name == "トーチカ小鬼"sv          //
                                        or api_name == "対空小鬼"sv              //
                                        or api_name == "トーチカ要塞棲姫"sv      //
                                        or api_name == "トーチカ要塞棲姫-壊"sv;  //
                                })
                              | std::ranges::views::transform([](const auto& e) static -> kcv::kcsapi::ship_id {
                                    const auto& [api_id, _] = e;
                                    return kcv::kcsapi::ship_id{api_id};
                                })
                              | std::ranges::to<kcv::inplace_vector<kcv::kcsapi::ship_id, 13>>();

    return std::ranges::binary_search(ids, mst.api_id);
}

bool kcv::is_isolated_island(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    static constexpr auto ids = kcv::detail::api_mst_ship
                              | std::ranges::views::filter([](const auto& e) static -> bool {
                                    const auto& [_, api_name] = e;
                                    using std::literals::string_view_literals::operator""sv;
                                    return api_name == "離島棲姫"sv;
                                })
                              | std::ranges::views::transform([](const auto& e) static -> kcv::kcsapi::ship_id {
                                    const auto& [api_id, _] = e;
                                    return api_id;
                                })
                              | std::ranges::to<kcv::inplace_vector<kcv::kcsapi::ship_id, 5>>();

    static_assert(std::ranges::is_sorted(ids));
    return std::ranges::binary_search(ids, mst.api_id);
}

bool kcv::is_harbour_summer_princess(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    static constexpr auto ids = kcv::detail::api_mst_ship
                              | std::ranges::views::filter([](const auto& e) static -> bool {
                                    const auto& [_, api_name] = e;
                                    using std::literals::string_view_literals::operator""sv;
                                    return api_name == "港湾夏姫"sv               //
                                        or api_name == "港湾夏姫II"sv             //
                                        or api_name == "港湾夏姫II-壊"sv          //
                                        or api_name == "港湾夏姫-壊"sv            //
                                        or api_name == "港湾棲姫 休日mode"sv      //
                                        or api_name == "港湾棲姫 休日mode-壊"sv;  //
                                })
                              | std::ranges::views::transform([](const auto& e) static -> kcv::kcsapi::ship_id {
                                    const auto& [api_id, _] = e;
                                    return api_id;
                                })
                              | std::ranges::to<kcv::inplace_vector<kcv::kcsapi::ship_id, 16>>();

    static_assert(std::ranges::is_sorted(ids));
    return std::ranges::binary_search(ids, mst.api_id);
}

bool kcv::is_soft_skin(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    return is_installation(mst) and not(is_pillbox(mst) or is_isolated_island(mst) or is_harbour_summer_princess(mst));
}

bool kcv::is_pt_imp(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    static constexpr auto ids = kcv::detail::api_mst_ship
                              | std::ranges::views::filter([](const auto& e) static -> bool {
                                    const auto& [_, api_name] = e;
                                    using std::literals::string_view_literals::operator""sv;
                                    return api_name == "PT小鬼群"sv            //
                                        or api_name == "Schnellboot小鬼群"sv;  //
                                })
                              | std::ranges::views::transform([](const auto& e) static -> kcv::kcsapi::ship_id {
                                    const auto& [api_id, _] = e;
                                    return api_id;
                                })
                              | std::ranges::to<kcv::inplace_vector<kcv::kcsapi::ship_id, 7>>();

    static_assert(std::ranges::is_sorted(ids));
    return std::ranges::binary_search(ids, mst.api_id);
}

bool kcv::is_submarine(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    switch (mst.api_stype) {
        case kcv::kcsapi::stype::ss:
        case kcv::kcsapi::stype::ssv:
            return true;

        default:
            return false;
    }
}

bool kcv::is_aircraft_carrier(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    switch (mst.api_stype) {
        case kcv::kcsapi::stype::cvl:
        case kcv::kcsapi::stype::cv:
        case kcv::kcsapi::stype::cvb:
            return true;

        default:
            return false;
    }
}

bool kcv::is_night_operation_aircraft_carrier(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::ship_literals::operator""_id;
        case "Saratoga Mk.II"_id:
        case "赤城改二戊"_id:
        case "加賀改二戊"_id:
        case "龍鳳改二戊"_id:
            return true;

        default:
            return false;
    }
}

bool kcv::is_night_shellable_aircraft_carrier(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::ship_literals::operator""_id;
        case "Graf Zeppelin"_id:
        case "Graf Zeppelin改"_id:
        case "大鷹改二"_id:
        case "神鷹改二"_id:
        case "Saratoga"_id:
        case "加賀改二護"_id:
            return true;

        default:
            return false;
    }
}

bool kcv::is_ark_royal(const kcv::kcsapi::api_mst_ship_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::ship_literals::operator""_id;
        case "Ark Royal"_id:
        case "Ark Royal改"_id:
            return true;

        default:
            return false;
    }
}
