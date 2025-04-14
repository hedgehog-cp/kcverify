#ifndef KCVERIFY_KCSAPI_TYPES_ENUM_AIR_HIT_TYPE_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_ENUM_AIR_HIT_TYPE_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

enum class air_hit_type {
    /// @brief 命中 | miss
    hit_or_miss = 0,

    /// @brief cLitical
    cLitical = 1,
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_ENUM_AIR_HIT_TYPE_HPP_INCLUDED
