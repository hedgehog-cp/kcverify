#ifndef KCVERIFY_kcsapi_API_START2_API_MST_SHIP_HPP_INCLUDED
#define KCVERIFY_kcsapi_API_START2_API_MST_SHIP_HPP_INCLUDED

// std
#include <array>
#include <optional>
#include <string>
#include <vector>

// kcv
#include "kcsapi/types/api_minmax.hpp"
#include "kcsapi/types/api_resource.hpp"
#include "kcsapi/types/enum/ctype.hpp"
#include "kcsapi/types/enum/ship_id.hpp"
#include "kcsapi/types/enum/stype.hpp"

namespace kcv {
namespace kcsapi {

/// @brief `api_start2/getData` の `api_mst_ship` の要素型.
struct api_mst_ship_value_type final {
    std::optional<int> api_afterbull;
    std::optional<int> api_afterfuel;
    std::optional<int> api_afterlv;
    std::optional<std::string> api_aftershipid;
    std::optional<int> api_backs;
    std::optional<api_resource> api_broken;
    std::optional<int> api_buildtime;
    std::optional<int> api_bull_max;
    ctype api_ctype;
    std::optional<int> api_fuel_max;
    std::optional<std::string> api_getmes;
    std::optional<api_minmax> api_houg;
    ship_id api_id;
    std::optional<int> api_leng;
    std::optional<api_minmax> api_luck;
    std::optional<std::array<int, 5>> api_maxeq;
    std::string api_name;
    std::optional<std::array<int, 4>> api_powup;
    std::optional<api_minmax> api_raig;
    int api_slot_num;
    int api_soku;
    int api_sort_id;
    std::optional<int> api_sortno;
    std::optional<api_minmax> api_souk;
    stype api_stype;
    std::optional<api_minmax> api_taik;
    std::optional<api_minmax> api_tyku;
    std::optional<int> api_voicef;
    std::string api_yomi;
    std::optional<api_minmax> api_tais;
};

/// @note コンテナを `std::vector` から `std::flat_map` への破壊的変更を検討.
using api_mst_ship = std::vector<api_mst_ship_value_type>;

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_kcsapi_API_START2_API_MST_SHIP_HPP_INCLUDED
