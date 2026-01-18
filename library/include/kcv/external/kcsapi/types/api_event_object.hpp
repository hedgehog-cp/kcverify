#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_EVENT_OBJECT_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_EVENT_OBJECT_HPP_INCLUDED

#include <cstdint>
#include <optional>

namespace kcv {
namespace kcsapi {

struct api_event_object final {
    std::int32_t api_m_flag;
    std::optional<std::int32_t> api_m_flag2;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_EVENT_OBJECT_HPP_INCLUDED
