#ifndef KCVERIFY_KCAPI_TYPES_API_SQUADRON_PLANE_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_SQUADRON_PLANE_HPP_INCLUDED

#include "kcapi/types/enum/equipment_id.hpp"

namespace kcv {
namespace kcapi {

struct api_squadoron_plane final {
    int api_count;
    equipment_id api_mst_id;
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_SQUADRON_PLANE_HPP_INCLUDED
