#ifndef KCVERIFY_KCAPI_TYPES_ENUM_AIR_HIT_TYPE_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_ENUM_AIR_HIT_TYPE_HPP_INCLUDED

namespace kcv {
namespace kcapi {

enum class air_hit_type {
    /// @brief 命中 | miss
    hit_or_miss = 0,

    /// @brief cLitical
    cLitical = 1,
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_ENUM_AIR_HIT_TYPE_HPP_INCLUDED
