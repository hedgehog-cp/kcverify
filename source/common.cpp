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

// GCCの場合, 警告が発されるのでこれを抑制する.
// https://github.com/stephenberry/glaze/issues/1561
#if defined(__GNUC__) && !defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

// glz
#include <glaze/json.hpp>

#if defined(__GNUC__) && !defined(__clang__)
    #pragma GCC diagnostic pop
#endif

// kcv
#include "kcsapi/api_get_member/ship_deck/response.hpp"
#include "kcsapi/api_req_battle_midnight/battle/response.hpp"
#include "kcsapi/api_req_map/next/response.hpp"
#include "kcsapi/api_req_map/start/request.hpp"
#include "kcsapi/api_req_map/start/response.hpp"
#include "kcsapi/api_req_sortie/battle/response.hpp"
#include "kcsapi/api_req_sortie/battleresult/response.hpp"
#include "kcsapi/api_start2/api_mst_ship.hpp"
#include "kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcsapi/types/enum/ship_id.hpp"
#include "kcsapi/types/svdata.hpp"

// meta files
#include "eoen/database/kancolle_api/meta.hpp"
#include "eoen/database/sortie/meta.hpp"
#include "eoen/serialization/fit_bonus/meta.hpp"

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

void kcv::read_json(auto& dst, const std::string& buffer) {
    const auto error = glz::read_json(dst, buffer);

    if (error) {
        const auto msg = std::format(
            "could not read buffer. [buffer = see below].\n"
            "{}\n"
            "{}",
            glz::format_error(error, buffer), buffer
        );
        kcv::exit_with_error(msg);
    }
}

// clang-format off

template void kcv::read_json(kcv::kcsapi::api_req_map::start::request&, const std::string&);
template void kcv::read_json(kcv::kcsapi::api_mst_ship&, const std::string&);
template void kcv::read_json(kcv::kcsapi::api_mst_slotitem&, const std::string&);
template void kcv::read_json(std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>&, const std::string&);
template void kcv::read_json(std::vector<kcv::eoen::database::sortie::sortie_record>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>&, const std::string&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>&, const std::string&);

// clang-format on

// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2024/p2319r0.html
// https://onihusube.hatenablog.com/#P2319R0-Prevent-path-presentation-problems
// [[deprecated("P2319: std::filesystemm::string")]]
void kcv::read_json(auto& dst, const std::filesystem::path& fname) {
    auto ec          = std::error_code{};
    const auto fsize = std::filesystem::file_size(fname, ec);

    if (fsize == static_cast<std::uintmax_t>(-1) or not kcv::is_readable(fname, ec)) {
        const auto msg = std::format("could not read file. [file = {}].\n{}", fname.string(), ec.message());
        kcv::exit_with_error(msg);
    }

    auto buffer = std::string{};
    buffer.resize_and_overwrite(fsize, [&fname](char* data, std::size_t size) -> std::size_t {
        std::ifstream{fname}.read(data, size);
        return size;
    });

    kcv::read_json(dst, buffer);
}

// clang-format off

template void kcv::read_json(kcv::kcsapi::api_req_map::start::request&, const std::filesystem::path&);
template void kcv::read_json(kcv::kcsapi::api_mst_ship&, const std::filesystem::path&);
template void kcv::read_json(kcv::kcsapi::api_mst_slotitem&, const std::filesystem::path&);
template void kcv::read_json(std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>&, const std::filesystem::path&);
template void kcv::read_json(std::vector<kcv::eoen::database::sortie::sortie_record>&, const std::filesystem::path&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>&, const std::filesystem::path&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>&, const std::filesystem::path&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>&, const std::filesystem::path&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>&, const std::filesystem::path&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>&, const std::filesystem::path&);
template void kcv::read_json(kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>&, const std::filesystem::path&);

// clang-format on

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