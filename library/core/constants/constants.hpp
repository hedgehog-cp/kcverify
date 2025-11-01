#ifndef KCVERIFY_CORE_CONSTANTS_CONSTANTS_HPP_INCLUDED
#define KCVERIFY_CORE_CONSTANTS_CONSTANTS_HPP_INCLUDED

namespace kcv {

/// @brief 艦船マスタのサイズヒント.
inline constexpr auto api_mst_ship_size_hint = 1700uz;

/// @brief 装備マスタのサイズヒント.
inline constexpr auto api_mst_slotitem_size_hint = 800uz;

/// @brief 最大スロットサイズ = 装備スロット|5 + 増設スロット|1.
inline constexpr auto max_slot_size = 5uz + 1uz;

}  // namespace kcv

#endif  // KCVERIFY_CORE_CONSTANTS_CONSTANTS_HPP_INCLUDED
