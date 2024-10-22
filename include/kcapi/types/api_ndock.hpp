#ifndef KCVERIFY_KCAPI_TYPES_API_NDOCK_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_NDOCK_HPP_INCLUDED

#include <cstdint>
#include <string>

namespace kcv {
namespace kcapi {

/// @brief 入渠ドック.
struct api_ndock final {
    /// @brief 入渠完了時間.
    std::int64_t api_complete_time;

    /// @brief 入渠完了日時.
    std::string api_complete_time_str;

    /// @brief ドック番号.
    int api_id;

    /// @brief 消費燃料.
    int api_item1;

    /// @brief 消費弾薬.
    int api_item2;

    /// @brief 消費鋼材.
    int api_item3;

    /// @brief 消費ボーキサイト.
    int api_item4;

    /// @brief 提督ID
    int api_member_id;

    /// @brief 入渠中艦船ID. 空きは0.
    int api_ship_id;

    /// @brief 状態. -1=ロック, 0=空き, 1=入渠中.
    int api_state;
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_NDOCK_HPP_INCLUDED
