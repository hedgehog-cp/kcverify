#ifndef KCVERIFY_CORE_JSON_READ_JSON_HPP_INCLUDED
#define KCVERIFY_CORE_JSON_READ_JSON_HPP_INCLUDED

#include <filesystem>
#include <string>

namespace kcv {

/// @brief bufferをJSONに解析してdstに読み込む.
/// @param dst 宛先.
/// @param buffer JSON文字列が格納されたバッファ.
template <typename T>
void read_json(T& dst, const std::string& buffer);

/// @brief fnameが表すファイルをJSONに解析してdstに読み込む.
/// @param dst 宛先.
/// @param fname JSONファイル.
template <typename T>
void read_json(T& dst, const std::filesystem::path& fname);

}  // namespace kcv

#endif  // KCVERIFY_CORE_JSON_READ_JSON_HPP_INCLUDED
