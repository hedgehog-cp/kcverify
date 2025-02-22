#ifndef KCVERIFY_JSON_READ_JSON_HPP_INCLUDED
#define KCVERIFY_JSON_READ_JSON_HPP_INCLUDED

// std
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <print>
#include <string>

#include "exit.hpp"

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

// meta files
#include "eoen/database/kancolle_api/meta.hpp"
#include "eoen/database/sortie/meta.hpp"
#include "eoen/serialization/fit_bonus/meta.hpp"

namespace kcv {

void read_json(auto& dst, const std::string& buffer, const std::string& src_name = "raw string") noexcept try {
    if (const auto error = glz::read_json(dst, buffer); error) {
        const auto msg = std::format("could not read {}.\n{}", src_name, glz::format_error(error, buffer));
        kcv::exit_with_error(msg);
    }
} catch (const std::exception& e) {
    const auto msg = std::format("could not read {}.\n{}", src_name, e.what());
    kcv::exit_with_error(msg);
} catch (...) {
    const auto msg = std::format("could not read {}.", src_name);
    kcv::exit_with_error(msg);
}

void read_json(auto& dst, const std::filesystem::path& fname) noexcept try {
    auto buffer = std::string{};
    buffer.resize_and_overwrite(std::filesystem::file_size(fname), [&](char* data, std::size_t size) -> std::size_t {
        std::ifstream{fname}.read(data, size);
        return size;
    });
    kcv::read_json(dst, buffer, fname);
} catch (const std::exception& e) {
    const auto msg = std::format("could not read {}.\n{}", fname.string(), e.what());
    kcv::exit_with_error(msg);
} catch (...) {
    const auto msg = std::format("could not read {}.", fname.string());
    kcv::exit_with_error(msg);
}

}  // namespace kcv

#endif  // KCVERIFY_JSON_READ_JSON_HPP_INCLUDED
