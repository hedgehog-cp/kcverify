#ifndef KCVERIFY_JSON_READ_JSON_HPP_INCLUDED
#define KCVERIFY_JSON_READ_JSON_HPP_INCLUDED

// std
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <print>
#include <string>

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
#include "common.hpp"

// meta files
#include "eoen/database/kancolle_api/meta.hpp"
#include "eoen/database/sortie/meta.hpp"
#include "eoen/serialization/fit_bonus/meta.hpp"

namespace kcv {

/// @brief bufferをJSONとしてdstに読み込む.
/// @param dst 宛先.
/// @param buffer JSON文字列が格納されたバッファ.
/// @return エラーの場合,  エラーとしてプログラムを終了する.
void read_json(auto& dst, const std::string& buffer) {
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

/// @brief fnameが表すファイルをJSONとしてdstに読み込む.
/// @param dst 宛先.
/// @param fname JSONファイル.
/// @return エラーの場合,  エラーとしてプログラムを終了する.
void read_json(auto& dst, const std::filesystem::path& fname) {
    auto ec          = std::error_code{};
    const auto fsize = std::filesystem::file_size(fname, ec);

    if (fsize == static_cast<std::uintmax_t>(-1) or not kcv::is_readable(fname, ec)) {
        // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2024/p2319r0.html
        // https://onihusube.hatenablog.com/#P2319R0-Prevent-path-presentation-problems
        // [[deprecated("P2319: std::filesystemm::string")]]
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

}  // namespace kcv

#endif  // KCVERIFY_JSON_READ_JSON_HPP_INCLUDED
