#ifndef KCV_META_EOEN_DESTINATION_HPP_INCLUDED
#define KCV_META_EOEN_DESTINATION_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "kcv/external/eoen/destination.hpp"

template <>
struct glz::meta<kcv::eoen::destination> final {
    using T = kcv::eoen::destination;

    static constexpr auto value = glz::object(&T::version);

    /// HACK: "World (\d+)-(\d+)"のようなキーをメンバ名で表現することが困難であるため, 不明なキー名として扱う.
    static constexpr auto unknown_read = &T::worlds;
};

#endif  // KCV_META_EOEN_DESTINATION_HPP_INCLUDED
