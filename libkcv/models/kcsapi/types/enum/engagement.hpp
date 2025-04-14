#ifndef KCVERIFY_KCSAPI_TYPES_ENUM_ENGAGEMENT_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_ENUM_ENGAGEMENT_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

/// @brief 交戦形態
enum class engagement {
    /// @brief 同航戦
    parallel = 1,

    /// @brief 反航戦
    head_on = 2,

    /// @brief T字有利
    green_t = 3,

    /// @brief T字不利
    red_t = 4,
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_ENUM_ENGAGEMENT_HPP_INCLUDED
