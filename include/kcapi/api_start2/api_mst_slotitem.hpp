#ifndef KCVERIFY_KCAPI_API_START2_API_MST_SLOTITEM_HPP_INCLUDED
#define KCVERIFY_KCAPI_API_START2_API_MST_SLOTITEM_HPP_INCLUDED

#include <optional>
#include <string>
#include <vector>

#include "kcapi/types/enum/equipment_id.hpp"

namespace kcv {
namespace kcapi {

struct api_mst_slotitem_value_type final {
    int api_atap;
    int api_bakk;
    int api_baku;
    std::vector<int> api_broken;
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
    std::vector<int> api_type;
    std::string api_usebull;
    std::optional<int> api_version;
    std::optional<int> api_cost;
    std::optional<int> api_distance;
};

using api_mst_slotitem = std::vector<api_mst_slotitem_value_type>;

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_API_START2_API_MST_SLOTITEM_HPP_INCLUDED
