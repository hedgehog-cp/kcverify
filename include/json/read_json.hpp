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

/// @brief jsonファイルを読み込んで型Tの値にparseします.
/// ファイルを読み込めなければプロセスを終了します.
/// @tparam T
/// @param fname このファイルを読み込みます.
/// @param buffer `std::string&` または `std::string&&`.
/// @return 成功すれば返ります. 失敗すれば返りません.
// template <typename T, typename U = std::string>
// void read_json(const std::filesystem::path& fname, T& dst, U&& buffer = std::string{}) try {
//     namespace fs = std::filesystem;

//     if (not fs::exists(fname)) {
//         std::println(stderr, "ERROR: '{}' not found.", fname.c_str());
//         std::exit(EXIT_FAILURE);
//     }

//     if (fname.extension() != ".json") {
//         std::println(stderr, "ERROR: '{}' is not JSON file.", fname.c_str());
//         std::exit(EXIT_FAILURE);
//     }

//     if ((fs::status(fname).permissions() & fs::perms::owner_read) != fs::perms::owner_read) {
//         std::println(stderr, "ERROR: failed to open '{}' (Permission denied).", fname.c_str());
//         std::exit(EXIT_FAILURE);
//     }

//     if (auto ifs = std::ifstream{fname}; ifs.is_open() and ifs.good()) {
//         buffer.resize_and_overwrite(std::filesystem::file_size(fname), [&](char* data, std::size_t size) {
//             ifs.read(data, size);
//             return size;
//         });

//         if (const auto error = glz::read_json(dst, buffer); error) {
//             std::println(stderr, "ERROR: {} in '{}'.", glz::format_error(error), fname.c_str());
//             std::exit(EXIT_FAILURE);
//         }

//         return;  // ok
//     }

//     std::println(stderr, "ERROR: failed to open '{}'.", fname.c_str());
//     std::exit(EXIT_FAILURE);
// } catch (const std::exception& e) {
//     std::println(stderr, "{}", e.what());
//     std::println(stderr, "ERROR: Could not read file '{}'.", fname.c_str());
//     std::exit(EXIT_FAILURE);
// } catch (...) {
//     std::println(stderr, "ERROR: Could not read file '{}'.", fname.c_str());
//     std::exit(EXIT_FAILURE);
// }

}  // namespace kcv

#endif  // KCVERIFY_JSON_READ_JSON_HPP_INCLUDED
