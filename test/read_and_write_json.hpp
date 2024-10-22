#ifndef KCVERIFY_READ_AND_WRITE_JSON_HPP_INCLUDED
#define KCVERIFY_READ_AND_WRITE_JSON_HPP_INCLUDED

// std
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>

// glz
#include <glaze/json.hpp>

namespace kcv::test {

template <typename T>
int read_and_write_json(const std::filesystem::path& fname) {
    auto dst = T{};

    auto buffer = std::string{};
    buffer.resize_and_overwrite(std::filesystem::file_size(fname), [&fname](char* data, std::size_t size) {
        std::ifstream{fname}.read(data, size);
        return size;
    });

    if (const auto error = glz::read_json(dst, buffer); error) {
        return EXIT_FAILURE;
    } else if (const auto result = glz::write_json(dst); result) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}

}  // namespace kcv::test

#endif  // KCVERIFY_READ_AND_WRITE_JSON_HPP_INCLUDED
