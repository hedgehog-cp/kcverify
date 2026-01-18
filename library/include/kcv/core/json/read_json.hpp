#ifndef KCV_CORE_JSON_READ_JSON_HPP_INCLUDED
#define KCV_CORE_JSON_READ_JSON_HPP_INCLUDED

// コンパイル時間を短縮するため, kcv::read_jsonの定義をsource配下に分割している.
// extern templateではないので, 必要に応じて実装に追加する必要あり.

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

#endif  // KCV_CORE_JSON_READ_JSON_HPP_INCLUDED
