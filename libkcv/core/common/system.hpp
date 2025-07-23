#ifndef KCVERIFY_CORE_UTILITY_SYSTEM_HPP_INCLUDED
#define KCVERIFY_CORE_UTILITY_SYSTEM_HPP_INCLUDED

// std
#include <filesystem>
#include <system_error>

namespace kcv {

/// @brief ファイルを読み込めるかを検証する.
/// @param fname 検査対象のファイル名.
/// @param ec エラーコード.
/// @return 読み込めるならばtrueを返す. エラーの場合, ecにエラーコードをセットするとともにfalseを返す.
/// @see https://stackoverflow.com/questions/1383617/how-to-check-if-a-file-exists-and-is-readable-in-c
bool is_readable(const std::filesystem::path& fname, std::error_code& ec) noexcept;

}  // namespace kcv

#endif  // KCVERIFY_CORE_UTILITY_SYSTEM_HPP_INCLUDED
