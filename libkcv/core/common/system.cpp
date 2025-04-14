#include "core/common/system.hpp"

// std
#include <cstdlib>
#include <filesystem>
#include <format>
#include <print>
#include <source_location>
#include <string>
#include <system_error>

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
