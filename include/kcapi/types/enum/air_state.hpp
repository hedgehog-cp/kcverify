#ifndef KCVERIFY_KCAPI_TYPES_ENUM_AIR_STATE_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_ENUM_AIR_STATE_HPP_INCLUDED

namespace kcv {
namespace kcapi {

/// @brief 制空状態
enum class air_state {
    unknown = -1,

    /// @brief 航空均衡 | 航空拮抗
    parity = 0,

    /// @brief 制空権確保
    supremacy = 1,

    /// @brief 航空優勢
    superiority = 2,

    /// @brief 航空劣勢
    denial = 3,

    /// @brief 制空権喪失
    incapability = 4,
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_ENUM_AIR_STATE_HPP_INCLUDED
