#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_ITEMGET_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_ITEMGET_HPP_INCLUDED

#include <cstdint>
#include <string>

namespace kcv {
namespace kcsapi {

struct api_itemget final {
    std::int32_t api_getcount;
    std::int32_t api_icon_id;
    std::int32_t api_id;
    std::string api_name;
    std::int32_t api_usemst;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_ITEMGET_HPP_INCLUDED
