#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_SQUADRON_PLANE_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_SQUADRON_PLANE_HPP_INCLUDED

// std
#include <cstdint>

// kcv
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"

namespace kcv {
namespace kcsapi {

struct api_squadoron_plane final {
    std::int32_t api_count;
    kcv::kcsapi::equipment_id api_mst_id;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_SQUADRON_PLANE_HPP_INCLUDED
