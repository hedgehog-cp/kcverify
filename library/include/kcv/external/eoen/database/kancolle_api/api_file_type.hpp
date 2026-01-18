#ifndef KCV_EXTERNAL_EOEN_DATABASE_KANCOLLE_API_API_FILE_TYPE_HPP_INCLUDED
#define KCV_EXTERNAL_EOEN_DATABASE_KANCOLLE_API_API_FILE_TYPE_HPP_INCLUDED

namespace kcv {
namespace eoen {
namespace database {
namespace kancolle_api {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `ApiFileType`.
/// @see namespace ElectronicObserver.Database.KancolleApi; public enum ApiFileType { ... }
enum class api_file_type {
    request  = 0,
    response = 1,
};

}  // namespace kancolle_api
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCV_EXTERNAL_EOEN_DATABASE_KANCOLLE_API_API_FILE_TYPE_HPP_INCLUDED
