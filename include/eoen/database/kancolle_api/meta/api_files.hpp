#ifndef KCVERIFY_EOEN_DATABASE_KANCOLLE_API_META_API_FILES_HPP_INCLUDED
#define KCVERIFY_EOEN_DATABASE_KANCOLLE_API_META_API_FILES_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "eoen/database/kancolle_api/api_files.hpp"

template <>
struct glz::meta<kcv::eoen::database::kancolle_api::api_files> {
    using T = kcv::eoen::database::kancolle_api::api_files;

    static constexpr auto value = object(
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

#endif  // KCVERIFY_EOEN_DATABASE_KANCOLLE_API_META_API_FILES_HPP_INCLUDED
