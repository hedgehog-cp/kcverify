#ifndef KCV_EXTERNAL_KCSAPI_TYPES_ENUM_DETECTION_TYPE_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_ENUM_DETECTION_TYPE_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

enum class detection_type {
    unknown = 0,

    /// @brief 成功
    success = 1,

    /// @brief 成功(未帰還機あり)
    success_no_return = 2,

    /// @brief 未帰還
    no_return = 3,

    /// @brief 失敗
    failure = 4,

    /// @brief 発見
    success_no_plane = 5,

    /// @brief 発見できず
    failure_no_plane = 6,
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_ENUM_DETECTION_TYPE_HPP_INCLUDED
