#ifndef KCVERIFY_KCSAPI_TYPES_API_EVENT_OBJECT_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_API_EVENT_OBJECT_HPP_INCLUDED

#include <optional>

namespace kcv {
namespace kcsapi {

struct api_event_object final {
    int api_m_flag;
    std::optional<int> api_m_flag2;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_API_EVENT_OBJECT_HPP_INCLUDED
