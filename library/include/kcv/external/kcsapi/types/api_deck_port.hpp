#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_DECK_PORT_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_DECK_PORT_HPP_INCLUDED

#include <cstdint>
#include <string>
#include <vector>

namespace kcv {
namespace kcsapi {

/// @brief
/// api_get_member/deck
/// api_get_member/ship2
/// api_req_hensei/preset_select
struct api_deck_port_value_t final {
    /// @brief
    std::string api_flagship;

    /// @brief 艦隊番号
    std::int32_t api_id;

    /// @brief 提督ID
    std::int32_t api_member_id;

    /// @brief 遠征状況	[0]={0=未出撃, 1=遠征中, 2=遠征帰投, 3=強制帰投中}, [1]=遠征先ID, [2]=帰投時間, [3]=0
    std::vector<std::int64_t> api_mission;

    /// @brief 艦隊名
    std::string api_name;

    /// @brief
    std::string api_name_id;

    /// @brief 所属艦船ID. 基本的には[6] ('17 秋イベントでは第三艦隊のみ[7]) 空きは-1
    std::vector<std::int32_t> api_ship;
};

using api_deck_port = std::vector<api_deck_port_value_t>;

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_DECK_PORT_HPP_INCLUDED
