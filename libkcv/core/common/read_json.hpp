#ifndef KCVERIFY_READ_JSON_HPP_INCLUDED
#define KCVERIFY_READ_JSON_HPP_INCLUDED

#include <filesystem>
#include <string>

namespace kcv {

/// @brief bufferをJSONとしてdstに読み込む.
/// @param dst 宛先.
/// @param buffer JSON文字列が格納されたバッファ.
void read_json(auto& dst, const std::string& buffer);

/// @brief fnameが表すファイルをJSONとしてdstに読み込む.
/// @param dst 宛先.
/// @param fname JSONファイル.
void read_json(auto& dst, const std::filesystem::path& fname);

}  // namespace kcv

#endif  // KCVERIFY_READ_JSON_HPP_INCLUDED
