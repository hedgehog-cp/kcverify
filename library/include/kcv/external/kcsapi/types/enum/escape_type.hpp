#ifndef KCV_EXTERNAL_KCSAPI_TYPES_ENUM_ESCAPE_TYPE_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_ENUM_ESCAPE_TYPE_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

/// @brief 退避のタイプ.
/// @note 各メンバ名は開発者が任意に定めたもので非公式.
enum class escape_type : int {
    /// @brief 遊撃部隊退避（7隻編成の遊撃部隊でのみ発生）
    single_fleet = 1,

    /// @brief 水雷戦隊退避（通常の2艦隊連合での退避）
    combined_fleet = 2,
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_ENUM_ESCAPE_TYPE_HPP_INCLUDED
