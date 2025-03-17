#include "common.hpp"

// std
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <fstream>
#include <print>
#include <ranges>
#include <source_location>
#include <string>
#include <utility>

#include "kcsapi/api_start2/api_mst_ship.hpp"
#include "kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcsapi/types/enum/ship_id.hpp"

// clang-format off

auto kcv::format_location(const std::source_location& loc) -> std::string {
    return std::format(
        "{}: In function `{}`\n"
        "{}:{}:{}",
        loc.file_name(), loc.function_name(),
        loc.file_name(), loc.line(), loc.column()
    );
}

// clang-format on

void kcv::exit_with_error(const std::string& error, std::source_location loc) {
    std::println("{}: error: {}", kcv::format_location(loc), error);
    std::exit(EXIT_FAILURE);
}

bool kcv::is_readable(const std::filesystem::path& fname, std::error_code& ec) noexcept {
    const auto perms = std::filesystem::status(fname, ec).permissions();
    return (perms & std::filesystem::perms::owner_read) != std::filesystem::perms::none
        && (perms & std::filesystem::perms::group_read) != std::filesystem::perms::none
        && (perms & std::filesystem::perms::others_read) != std::filesystem::perms::none;
}

// clang-format off

auto kcv::binary_search_or_exit(const kcv::kcsapi::api_mst_ship& api_mst_ship, kcv::kcsapi::ship_id id)
    -> const kcv::kcsapi::api_mst_ship::value_type&
{
    using value_type = kcv::kcsapi::api_mst_ship::value_type;
    const auto itr   = std::ranges::lower_bound(api_mst_ship, id, {}, &value_type::api_id);
    if (itr != std::ranges::end(api_mst_ship) and itr->api_id == id) {
        return *itr;
    }

    const auto msg = std::format("ship id not found. [ship id = {}].", std::to_underlying(id));
    kcv::exit_with_error(msg);
}

// clang-format on

// clang-format off

auto kcv::binary_search_or_exit(const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem, kcv::kcsapi::equipment_id id)
    -> const kcv::kcsapi::api_mst_slotitem::value_type&
{
    using value_type = kcv::kcsapi::api_mst_slotitem::value_type;
    const auto itr   = std::ranges::lower_bound(api_mst_slotitem, id, {}, &value_type::api_id);
    if (itr != std::ranges::end(api_mst_slotitem) and itr->api_id == id) {
        return *itr;
    }

    const auto msg = std::format("equipment id not found. [equipment id = {}].", std::to_underlying(id));
    kcv::exit_with_error(msg);
}

// clang-format on

// clang-format off

auto kcv::original_id_or_exit(
    const kcv::kcsapi::api_mst_ship_value_t& mst,
    const kcv::kcsapi::api_mst_ship& api_mst_ship
) 
    -> kcv::kcsapi::ship_id
{
    auto ids = api_mst_ship
             | std::ranges::views::filter([&mst](const auto& e) -> bool {
                   return e.api_yomi == mst.api_yomi and e.api_sort_id % 10 == 1;
               })
             | std::ranges::views::transform(&kcv::kcsapi::api_mst_ship_value_t::api_id);

    for (const auto& id : ids) {
        return id;
    }

    const auto msg = std::format("original id not found in api_mst_ship. [id = {}]", std::to_underlying(mst.api_id));
    kcv::exit_with_error(msg);
}

// clang-format on