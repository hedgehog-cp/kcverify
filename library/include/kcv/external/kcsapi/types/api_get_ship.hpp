#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_GET_SHIP_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_GET_SHIP_HPP_INCLUDED

// std
#include <string>

// kcv
#include "kcv/external/kcsapi/types/enum/ship_id.hpp"

namespace kcv {
namespace kcsapi {

struct api_get_ship final {
    std::string api_ship_getmes;
    kcv::kcsapi::ship_id api_ship_id;
    std::string api_ship_name;
    std::string api_ship_type;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_GET_SHIP_HPP_INCLUDED
