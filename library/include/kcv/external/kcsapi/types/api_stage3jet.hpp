#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_STAGE3JET_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_STAGE3JET_HPP_INCLUDED

// std
#include <cstdint>
#include <vector>

// kcv
#include "kcv/external/kcsapi/types/enum/air_hit_type.hpp"

namespace kcv {
namespace kcsapi {

struct api_stage3jet final {
    std::vector<std::int32_t> api_ebak_flag;
    std::vector<kcv::kcsapi::air_hit_type> api_ecl_flag;
    std::vector<double> api_edam;
    std::vector<std::int32_t> api_erai_flag;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_STAGE3JET_HPP_INCLUDED
