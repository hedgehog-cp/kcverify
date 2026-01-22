#ifndef KCV_EXTERNAL_EOEN_DATABASE_KANCOLLE_API_API_FILES_HPP_INCLUDED
#define KCV_EXTERNAL_EOEN_DATABASE_KANCOLLE_API_API_FILES_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <string>

// kcv
#include "kcv/external/eoen/database/kancolle_api/api_file_type.hpp"

namespace kcv {
namespace eoen {
namespace database {
namespace kancolle_api {

/// @brief `ツール` -> `出撃記録` -> `出撃詳細` より出力される `ApiFiles` の要素型.
/// @brief namespace ElectronicObserver.Database.KancolleApi; public class ApiFile { ... }
/// @see ElectronicObserver/Database/KancolleApi/ApiFile.cs
struct api_files final {
    /// @brief 74式ENの何某かの管理用ID.
    std::int32_t id;

    /// @brief request or response.
    kcv::eoen::database::kancolle_api::api_file_type api_file_type;

    /// @brief apiファイルの名前.
    std::string name;

    /// @brief apiの本体.
    std::string content;

    /// @brief タイムスタンプ.
    std::string time_stamp;

    /// @brief 74式ENの何某かの管理用Version.
    std::int32_t version;

    /// @brief 74式ENの何某かの管理用ID.
    std::optional<std::int32_t> sortie_record_id;
};

}  // namespace kancolle_api
}  // namespace database
}  // namespace eoen
}  // namespace kcv

#endif  // KCV_EXTERNAL_EOEN_DATABASE_KANCOLLE_API_API_FILES_HPP_INCLUDED
