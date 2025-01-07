#ifndef KCVERIFY_KCSAPI_API_GET_MEMBER_SHIP_DECK_RESPONSE_HPP_INCLUDED
#define KCVERIFY_KCSAPI_API_GET_MEMBER_SHIP_DECK_RESPONSE_HPP_INCLUDED

// std
#include <vector>

// kcv
#include "kcsapi/types/api_deck_data.hpp"
#include "kcsapi/types/api_ship_data.hpp"

namespace kcv {
namespace kcsapi {
namespace api_get_member {
namespace ship_deck {

/// @brief api_get_member/ship_deck.json
struct response final {
    std::vector<api_deck_data_value_t> api_deck_data;
    std::vector<api_ship_data_value_t> api_ship_data;
};

}  // namespace ship_deck
}  // namespace api_get_member
}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_API_GET_MEMBER_SHIP_DECK_RESPONSE_HPP_INCLUDED
