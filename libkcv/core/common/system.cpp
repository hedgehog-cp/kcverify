#include "core/common/system.hpp"

// std
#include <cstdlib>
#include <filesystem>
#include <print>
#include <system_error>

bool kcv::is_readable(const std::filesystem::path& fname, std::error_code& ec) noexcept {
    const auto perms = std::filesystem::status(fname, ec).permissions();
    return (perms & std::filesystem::perms::owner_read) != std::filesystem::perms::none
        && (perms & std::filesystem::perms::group_read) != std::filesystem::perms::none
        && (perms & std::filesystem::perms::others_read) != std::filesystem::perms::none;
}
