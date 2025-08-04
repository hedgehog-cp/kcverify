#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_STAGE3JET_COMBINED_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_STAGE3JET_COMBINED_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "models/kcsapi/types/enum/air_hit_type.hpp"

namespace kcv {
namespace kcsapi {

struct api_stage3jet_combined final {
    std::optional<std::vector<std::int32_t>> api_ebak_flag;
    std::optional<std::vector<kcv::kcsapi::air_hit_type>> api_ecl_flag;
    std::optional<std::vector<double>> api_edam;
    std::optional<std::vector<std::int32_t>> api_erai_flag;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_STAGE3JET_COMBINED_HPP_INCLUDED
