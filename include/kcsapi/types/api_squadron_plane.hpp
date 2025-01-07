#ifndef KCVERIFY_KCSAPI_TYPES_API_SQUADRON_PLANE_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_API_SQUADRON_PLANE_HPP_INCLUDED

#include "kcsapi/types/enum/equipment_id.hpp"

namespace kcv {
namespace kcsapi {

struct api_squadoron_plane final {
    int api_count;
    equipment_id api_mst_id;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_API_SQUADRON_PLANE_HPP_INCLUDED
