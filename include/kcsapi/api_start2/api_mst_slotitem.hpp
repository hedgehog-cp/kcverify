#ifndef KCVERIFY_kcsapi_API_START2_API_MST_SLOTITEM_HPP_INCLUDED
#define KCVERIFY_kcsapi_API_START2_API_MST_SLOTITEM_HPP_INCLUDED

// std
#include <optional>
#include <string>
#include <vector>

// kcv
#include "kcsapi/types/api_resource.hpp"
#include "kcsapi/types/api_type.hpp"
#include "kcsapi/types/enum/equipment_id.hpp"

namespace kcv {
namespace kcsapi {

/// @brief `api_start2/getData` の `api_mst_slotitem` の要素型.
struct api_mst_slotitem_value_t final {
    int api_atap;
    int api_bakk;
    int api_baku;
    api_resource api_broken;
    int api_houg;
    int api_houk;
    int api_houm;
    equipment_id api_id;
    int api_leng;
    int api_luck;
    std::string api_name;
    int api_raig;
    int api_raik;
    int api_raim;
    int api_rare;
    int api_sakb;
    int api_saku;
    int api_soku;
    int api_sortno;
    int api_souk;
    int api_taik;
    int api_tais;
    int api_tyku;
    kcsapi::api_type api_type;
    std::string api_usebull;
    std::optional<int> api_version;
    std::optional<int> api_cost;
    std::optional<int> api_distance;
};

using api_mst_slotitem = std::vector<api_mst_slotitem_value_t>;

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_kcsapi_API_START2_API_MST_SLOTITEM_HPP_INCLUDED
