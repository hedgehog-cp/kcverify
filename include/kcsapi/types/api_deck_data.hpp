#ifndef KCVERIFY_KCSAPI_TYPES_API_DECK_DATA_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_API_DECK_DATA_HPP_INCLUDED

#include <cstdint>
#include <string>
#include <vector>

namespace kcv {
namespace kcsapi {

struct api_deck_data_value_t final {
    std::string api_flagship;

    /// @brief 艦隊番号.
    int api_id;

    /// @brief 提督ID.
    std::int_least32_t api_member_id;

    /// @brief 遠征状況. [0]={0=未出撃, 1=遠征中, 2=遠征帰投, 3=強制帰投中}, [1]=遠征先ID, [2]=帰投時間, [3]=0.
    std::vector<int> api_mission;

    /// @brief 艦隊名.
    std::string api_name;

    std::string api_name_id;

    // 所属艦船ID. 基本的には[6] ('17 秋イベントでは第三艦隊のみ[7]). 空きは-1.
    std::vector<std::int_least32_t> api_ship;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_API_DECK_DATA_HPP_INCLUDED
