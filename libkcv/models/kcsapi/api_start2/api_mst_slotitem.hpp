#ifndef KCVERIFY_KCSAPI_API_START2_API_MST_SLOTITEM_HPP_INCLUDED
#define KCVERIFY_KCSAPI_API_START2_API_MST_SLOTITEM_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

// kcv
#include "models/kcsapi/types/api_resource.hpp"
#include "models/kcsapi/types/api_type.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"

namespace kcv {
namespace kcsapi {

/// @brief `api_start2/getData` の `api_mst_slotitem` の要素型.
struct api_mst_slotitem_value_t final {
    std::int32_t api_atap;
    std::int32_t api_bakk;
    std::int32_t api_baku;
    kcv::kcsapi::api_resource api_broken;
    std::int32_t api_houg;
    std::int32_t api_houk;
    std::int32_t api_houm;
    kcv::kcsapi::equipment_id api_id;
    std::int32_t api_leng;
    std::int32_t api_luck;
    std::string api_name;
    std::int32_t api_raig;
    std::int32_t api_raik;
    std::int32_t api_raim;
    std::int32_t api_rare;
    std::int32_t api_sakb;
    std::int32_t api_saku;
    std::int32_t api_soku;
    std::int32_t api_sortno;
    std::int32_t api_souk;
    std::int32_t api_taik;
    std::int32_t api_tais;
    std::int32_t api_tyku;
    kcv::kcsapi::api_type api_type;
    std::string api_usebull;
    std::optional<std::int32_t> api_version;
    std::optional<std::int32_t> api_cost;
    std::optional<std::int32_t> api_distance;
};

using api_mst_slotitem = std::vector<api_mst_slotitem_value_t>;

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_API_START2_API_MST_SLOTITEM_HPP_INCLUDED
