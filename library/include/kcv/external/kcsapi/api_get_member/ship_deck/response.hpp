#ifndef KCV_EXTERNAL_KCSAPI_API_GET_MEMBER_SHIP_DECK_RESPONSE_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_API_GET_MEMBER_SHIP_DECK_RESPONSE_HPP_INCLUDED

// std
#include <vector>

// kcv
#include "kcv/external/kcsapi/types/api_deck_data.hpp"
#include "kcv/external/kcsapi/types/api_ship_data.hpp"

namespace kcv {
namespace kcsapi {
namespace api_get_member {
namespace ship_deck {

/// @brief api_get_member/ship_deck.json
/// 進撃中.
struct response final {
    /// @brief 艦隊データ.
    std::vector<kcv::kcsapi::api_deck_data_value_t> api_deck_data;

    /// @brief 艦船データ.
    std::vector<kcv::kcsapi::api_ship_data_value_t> api_ship_data;
};

}  // namespace ship_deck
}  // namespace api_get_member
}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_API_GET_MEMBER_SHIP_DECK_RESPONSE_HPP_INCLUDED
