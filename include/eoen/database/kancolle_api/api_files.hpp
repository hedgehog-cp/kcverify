#ifndef KCVERIFY_EOEN_DATABASE_KANCOLLE_API_API_FILES_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_KANCOLLE_API_API_FILES_HPP_INCLUDED

// std
#include <optional>
#include <string>

// kcv
#include "eoen/database/kancolle_api/api_file_type.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace kancolle_api {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `ApiFiles` の要素型.
/// /0/ApiFiles/0
/// @see namespace ElectronicObserver.Database.KancolleApi; public class ApiFile { ... }
struct api_files final {
    int id;
    enum api_file_type api_file_type;

    /// @brief apiの名前.
    /// @example `api_req_map/start`など.
    std::string name;

    /// @brief apiの本体.
    std::string content;

    std::string time_stamp;
    int version;
    std::optional<int> sortie_record_id;
};

}  // namespace kancolle_api
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_DATABASE_KANCOLLE_API_API_FILES_HPP_INCLUDED
