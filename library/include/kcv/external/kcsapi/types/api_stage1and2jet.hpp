#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_STAGE1AND2JET_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_STAGE1AND2JET_HPP_INCLUDED

#include <cstdint>

namespace kcv {
namespace kcsapi {

/// @brief stage1 and stage2
struct api_stage1and2jet final {
    std::int32_t api_e_count;
    std::int32_t api_e_lostcount;
    std::int32_t api_f_count;
    std::int32_t api_f_lostcount;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_STAGE1AND2JET_HPP_INCLUDED
