#ifndef KCV_EXTERNAL_KCSAPI_TYPES_ENUM_FORMATION_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_ENUM_FORMATION_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

/// @brief 陣形
enum class formation {
    /// @brief 単縦陣
    line_ahead = 1,

    /// @brief 複縦陣
    double_line = 2,

    /// @brief 輪形陣
    diamond = 3,

    /// @brief 梯形陣
    echelon = 4,

    /// @brief 単横陣
    line_abreast = 5,

    /// @brief 警戒陣
    vanguard = 6,

    /// @brief 第一警戒航行序列
    Cruising1 = 11,

    /// @brief 第二警戒航行序列
    Cruising2 = 12,

    /// @brief 第三警戒航行序列
    Cruising3 = 13,

    /// @brief 第四警戒航行序列
    Cruising4 = 14,
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_ENUM_FORMATION_HPP_INCLUDED
