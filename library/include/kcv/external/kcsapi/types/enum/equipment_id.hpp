#ifndef KCV_EXTERNAL_KCSAPI_TYPES_ENUM_EQUIPMENT_ID_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_ENUM_EQUIPMENT_ID_HPP_INCLUDED

#include <cstdint>

namespace kcv {
namespace kcsapi {

/// @brief 装備ID.
enum class equipment_id : std::int32_t {};

/// @brief 無効な装備ID. 空きスロットなどの表現に用いられる. 装備マスタに含まないため検索しないこと.
/// @note enumのメンバとして定義するとswitch文で期待されない警告が発されるため外部に定義する:
/// warning: case value not in enumerated type 'kcv::kcsapi::equipment_id' [-Wswitch]
inline constexpr auto invalid_equipment_id = equipment_id{-1};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_ENUM_EQUIPMENT_ID_HPP_INCLUDED
