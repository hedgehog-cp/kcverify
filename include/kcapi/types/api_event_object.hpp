#ifndef KCVERIFY_KCAPI_TYPES_API_EVENT_OBJECT_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_EVENT_OBJECT_HPP_INCLUDED

#include <optional>

namespace kcv {
namespace kcapi {

struct api_event_object final {
    int api_m_flag;
    std::optional<int> api_m_flag2;
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_EVENT_OBJECT_HPP_INCLUDED
