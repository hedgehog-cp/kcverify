#ifndef KCVERIFY_CORE_UTILITY_SYSTEM_HPP_INCLUDED
#define KCVERIFY_CORE_UTILITY_SYSTEM_HPP_INCLUDED

// std
#include <filesystem>
#include <source_location>
#include <string>
#include <system_error>

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

}  // namespace kcv

#endif  // KCVERIFY_CORE_UTILITY_SYSTEM_HPP_INCLUDED
