#ifndef KCVERIFY_KCAPI_API_START2_API_MST_SHIP_HPP_INCLUDED
#define KCVERIFY_KCAPI_API_START2_API_MST_SHIP_HPP_INCLUDED

// std
#include <optional>
#include <string>
#include <vector>

// kcv
#include "kcapi/types/enum/ctype.hpp"
#include "kcapi/types/enum/ship_id.hpp"
#include "kcapi/types/enum/stype.hpp"

namespace kcv {
namespace kcapi {

struct api_mst_ship_value_type final {
    std::optional<int> api_afterbull;
    std::optional<int> api_afterfuel;
    std::optional<int> api_afterlv;
    std::optional<std::string> api_aftershipid;
    std::optional<int> api_backs;
    std::optional<std::vector<int>> api_broken;
    std::optional<int> api_buildtime;
    std::optional<int> api_bull_max;
    ctype api_ctype;
    std::optional<int> api_fuel_max;
    std::optional<std::string> api_getmes;
    std::optional<std::vector<int>> api_houg;
    ship_id api_id;
    std::optional<int> api_leng;
    std::optional<std::vector<int>> api_luck;
    std::optional<std::vector<int>> api_maxeq;
    std::string api_name;
    std::optional<std::vector<int>> api_powup;
    std::optional<std::vector<int>> api_raig;
    int api_slot_num;
    int api_soku;
    int api_sort_id;
    std::optional<int> api_sortno;
    std::optional<std::vector<int>> api_souk;
    stype api_stype;
    std::optional<std::vector<int>> api_taik;
    std::optional<std::vector<int>> api_tyku;
    std::optional<int> api_voicef;
    std::string api_yomi;
    std::optional<std::vector<int>> api_tais;
};

/// @note コンテナを `std::vector` から `std::flat_map` への破壊的変更を検討.
using api_mst_ship = std::vector<api_mst_ship_value_type>;

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_API_START2_API_MST_SHIP_HPP_INCLUDED
