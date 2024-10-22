#ifndef KCVERIFY_KCAPI_TYPES_API_GET_SHIP_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_GET_SHIP_HPP_INCLUDED

// std
#include <string>

// kcv
#include "kcapi/types/enum/ship_id.hpp"

namespace kcv {
namespace kcapi {

struct api_get_ship final {
    std::string api_ship_getmes;
    ship_id api_ship_id;
    std::string api_ship_name;
    std::string api_ship_type;
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_GET_SHIP_HPP_INCLUDED
