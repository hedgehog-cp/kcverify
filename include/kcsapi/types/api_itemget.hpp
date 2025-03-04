#ifndef KCVERIFY_KCSAPI_TYPES_API_ITEMGET_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_API_ITEMGET_HPP_INCLUDED

#include <string>

namespace kcv {
namespace kcsapi {

struct api_itemget final {
    int api_getcount;
    int api_icon_id;
    int api_id;
    std::string api_name;
    int api_usemst;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_API_ITEMGET_HPP_INCLUDED
