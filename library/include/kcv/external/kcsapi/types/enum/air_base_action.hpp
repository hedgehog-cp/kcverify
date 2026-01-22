#ifndef KCV_EXTERNAL_KCSAPI_TYPES_ENUM_AIR_BASE_ACTION_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_ENUM_AIR_BASE_ACTION_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

/// @brief 基地航空隊への行動指示.
enum class air_base_action {
    /// @see namespace ElectronicObserverTypes; public enum AirBaseActionKind { ... }
    none = -1,

    /// @brief 待機
    standby = 0,

    /// @brief 出撃
    mission = 1,

    /// @brief 防空
    air_defence = 2,

    /// @brief 退避
    take_cover = 3,

    /// @brief 休息
    rest = 4,
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_ENUM_AIR_BASE_ACTION_HPP_INCLUDED
