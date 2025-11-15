#ifndef KCVERIFY_CORE_JSON_GLZ_META_EOEN_DATABASE_KANCOLLE_API_API_FILES_HPP_INCLUDED
#define KCVERIFY_CORE_JSON_GLZ_META_EOEN_DATABASE_KANCOLLE_API_API_FILES_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "models/eoen/database/kancolle_api/api_files.hpp"

template <>
struct glz::meta<kcv::eoen::database::kancolle_api::api_files> final {
    using T = kcv::eoen::database::kancolle_api::api_files;

    static constexpr auto value = glz::object(
        // clang-format off

        "Id",             &T::id,
        "ApiFileType",    &T::api_file_type,
        "Name",           &T::name,
        "Content",        &T::content,
        "TimeStamp",      &T::time_stamp,
        "Version",        &T::version,
        "SortieRecordId", &T::sortie_record_id

        // clang-format on
    );
};

#endif  // KCVERIFY_CORE_JSON_GLZ_META_EOEN_DATABASE_KANCOLLE_API_API_FILES_HPP_INCLUDED
