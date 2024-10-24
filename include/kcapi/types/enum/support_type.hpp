#ifndef KCVERIFY_KCAPI_TYPES_ENUM_SUPPORT_TYPE_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_ENUM_SUPPORT_TYPE_HPP_INCLUDED

namespace kcv {
namespace kcapi {

/// @brief 支援艦隊
enum class support_type {
    /// @brief なし
    none = 0,

    /// @brief 空撃
    aerial = 1,

    /// @brief 砲撃
    shelling = 2,

    /// @brief 雷撃
    torpedo = 3,

    /// @brief 対潜
    anti_submarine = 4,
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_ENUM_SUPPORT_TYPE_HPP_INCLUDED
