#ifndef KCVERIFY_EXIT_HPP_INCLUDED
#define KCVERIFY_EXIT_HPP_INCLUDED

// std
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <format>
#include <print>
#include <source_location>
#include <utility>

// kcv
#include "kcsapi/types/enum/equipment_id.hpp"
#include "kcsapi/types/enum/ship_id.hpp"

namespace kcv {

// clang-format off

[[nodiscard]]
inline auto format_location(const std::source_location& loc) -> std::string {
    return std::format(
        "{}: In function `{}`\n"
        "{}:{}:{}",
        loc.file_name(), loc.function_name(),
        loc.file_name(), loc.line(), loc.column()
    );
}

// clang-format on

[[noreturn]]
inline void exit_with_error(const std::string& msg, std::source_location loc = std::source_location::current()) {
    std::println(stderr, "{}: error: {}", format_location(loc), msg);
    std::exit(EXIT_FAILURE);
}

[[noreturn]]
inline void exit_with_error(kcv::kcsapi::equipment_id id, std::source_location loc = std::source_location::current()) {
    const auto msg = std::format("{} not found in api_mst_slotitem.", std::to_underlying(id));
    kcv::exit_with_error(msg, loc);
}

[[noreturn]]
inline void exit_with_error(kcv::kcsapi::ship_id id, std::source_location loc = std::source_location::current()) {
    const auto msg = std::format("{} not found in api_mst_ship.", std::to_underlying(id));
    kcv::exit_with_error(msg, loc);
}

template <typename T, typename C>
constexpr auto binary_search_or_exit(T id, const C& mst) -> const typename C::value_type& {
    using value_type = typename C::value_type;
    const auto itr   = std::ranges::lower_bound(mst, id, {}, &value_type::api_id);
    if (itr != std::ranges::end(mst) and itr->api_id == id) [[likely]] {
        return *itr;
    }

    kcv::exit_with_error(id);
}

}  // namespace kcv

#endif  // KCVERIFY_EXIT_HPP_INCLUDED
