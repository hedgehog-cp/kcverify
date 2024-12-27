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

// glz
#include <glaze/json.hpp>

namespace kcv {

void read_json(auto& dst, const std::string& buffer) noexcept try {
    if (const auto error = glz::read_json(dst, buffer); error) {
        std::println(stderr, "{}.", glz::format_error(error, buffer));
        std::exit(EXIT_FAILURE);
    }
} catch (const std::exception& e) {
    std::println(stderr, "{}.", e.what());
    std::println(stderr, "could not read {}.", buffer);
    std::exit(EXIT_FAILURE);
} catch (...) {
    std::println(stderr, "could not read {}.", buffer);
    std::exit(EXIT_FAILURE);
}

template <typename T = std::string>
void read_json(auto& dst, const std::filesystem::path& fname, T&& buffer = std::string{}) noexcept try {
    buffer.resize_and_overwrite(std::filesystem::file_size(fname), [&](char* data, std::size_t size) -> std::size_t {
        std::ifstream{fname}.read(data, size);
        return size;
    });
    kcv::read_json(dst, buffer);
} catch (const std::exception& e) {
    std::println(stderr, "{}.", e.what());
    std::println(stderr, "could not read {}.", fname.c_str());
    std::exit(EXIT_FAILURE);
} catch (...) {
    std::println(stderr, "could not read {}.", fname.c_str());
    std::exit(EXIT_FAILURE);
}

}  // namespace kcv

#endif  // KCVERIFY_JSON_READ_JSON_HPP_INCLUDED
