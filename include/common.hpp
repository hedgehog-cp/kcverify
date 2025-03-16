#ifndef KCVERIFY_COMMON_HPP_INCLUDED
#define KCVERIFY_COMMON_HPP_INCLUDED

// std
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <print>
#include <source_location>
#include <string>

// kcv
#include "kcsapi/api_start2/api_mst_ship.hpp"
#include "kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcsapi/types/enum/equipment_id.hpp"
#include "kcsapi/types/enum/ship_id.hpp"

namespace kcv {

/// @brief std::source_locationを文字列にフォーマットする.
/// @param loc ソースコードの位置.
/// @return フォーマットされたソースコードの位置.
[[nodiscard]]
auto format_location(const std::source_location& loc) -> std::string;

/// @brief エラーメッセージを標準エラー出力に書き出すとともに, エラーとしてプログラムを終了する.
/// この関数は決して返らない.
/// @param error エラーメッセージ.
/// @param loc ソースコードの位置.
/// @todo add std::stacktrace to error message.
[[noreturn]]
void exit_with_error(const std::string& error, std::source_location loc = std::source_location::current());

/// @brief ファイルを読み込めるかを検証する.
/// @param fname 検査対象のファイル名.
/// @param ec エラーコード.
/// @return 読み込めるならばtrueを返す. エラーの場合, ecにエラーコードをセットするとともにfalseを返す.
/// @see https://stackoverflow.com/questions/1383617/how-to-check-if-a-file-exists-and-is-readable-in-c
bool is_readable(const std::filesystem::path& fname, std::error_code& ec) noexcept;

/// @brief bufferをJSONとしてdstに読み込む.
/// @param dst 宛先.
/// @param buffer JSON文字列が格納されたバッファ.
/// @return エラーの場合,  エラーとしてプログラムを終了する.
void read_json(auto& dst, const std::string& buffer);

/// @brief fnameが表すファイルをJSONとしてdstに読み込む.
/// @param dst 宛先.
/// @param fname JSONファイル.
/// @return エラーの場合,  エラーとしてプログラムを終了する.
void read_json(auto& dst, const std::filesystem::path& fname);

/// @brief 艦船IDに一致する艦船マスタを二分探索で取得する. 存在しなければエラーとしてプログラムを終了する.
/// @param api_mst_ship 艦船マスタ.
/// @param id 艦船ID.
/// @return 艦船IDに一致する艦船マスタ.
auto binary_search_or_exit(const kcv::kcsapi::api_mst_ship& api_mst_ship, kcv::kcsapi::ship_id id)
    -> const kcv::kcsapi::api_mst_ship::value_type&;

/// @brief 装備IDに一致する装備マスタを二分探索で取得する. 存在しなければエラーとしてプログラムを終了する.
/// @param api_mst_ship 装備マスタ.
/// @param id 装備ID.
/// @return 装備IDに一致する装備マスタ.
auto binary_search_or_exit(const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem, kcv::kcsapi::equipment_id id)
    -> const kcv::kcsapi::api_mst_slotitem::value_type&;

/// @brief 艦娘の未改造IDを取得する. 存在しなければエラーとしてプログラムを終了する.
/// @param mst 艦船マスタ.
/// @param api_mst_ship 艦船マスタ.
[[deprecated]]
auto original_id_or_exit(const kcv::kcsapi::api_mst_ship_value_t& mst, const kcv::kcsapi::api_mst_ship& api_mst_ship)
    -> kcv::kcsapi::ship_id;

}  // namespace kcv

#endif  // KCVERIFY_COMMON_HPP_INCLUDED
