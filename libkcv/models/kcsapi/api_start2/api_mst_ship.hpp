#ifndef KCVERIFY_MODELS_KCSAPI_API_START2_API_MST_SHIP_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_API_START2_API_MST_SHIP_HPP_INCLUDED

// std
#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

// kcv
#include "models/kcsapi/types/api_minmax.hpp"
#include "models/kcsapi/types/api_resource.hpp"
#include "models/kcsapi/types/enum/ctype.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"
#include "models/kcsapi/types/enum/stype.hpp"

namespace kcv {
namespace kcsapi {

/// @brief `api_start2/getData` の `api_mst_ship` の要素型.
struct api_mst_ship_value_t final {
    std::optional<std::int32_t> api_afterbull;
    std::optional<std::int32_t> api_afterfuel;
    std::optional<std::int32_t> api_afterlv;
    std::optional<std::string> api_aftershipid;
    std::optional<std::int32_t> api_backs;
    std::optional<api_resource> api_broken;
    std::optional<std::int32_t> api_buildtime;
    std::optional<std::int32_t> api_bull_max;
    kcv::kcsapi::ctype api_ctype;
    std::optional<std::int32_t> api_fuel_max;
    std::optional<std::string> api_getmes;
    std::optional<kcv::kcsapi::api_minmax> api_houg;
    kcv::kcsapi::ship_id api_id;
    std::optional<std::int32_t> api_leng;
    std::optional<kcv::kcsapi::api_minmax> api_luck;
    std::optional<std::array<std::int32_t, 5>> api_maxeq;
    std::string api_name;
    std::optional<std::array<std::int32_t, 4>> api_powup;
    std::optional<kcv::kcsapi::api_minmax> api_raig;
    std::int32_t api_slot_num;
    std::int32_t api_soku;
    std::int32_t api_sort_id;
    std::optional<std::int32_t> api_sortno;
    std::optional<kcv::kcsapi::api_minmax> api_souk;
    kcv::kcsapi::stype api_stype;
    std::optional<kcv::kcsapi::api_minmax> api_taik;
    std::optional<kcv::kcsapi::api_minmax> api_tyku;
    std::optional<std::int32_t> api_voicef;
    std::string api_yomi;
    std::optional<kcv::kcsapi::api_minmax> api_tais;
};

/// @note コンテナを `std::vector` から `std::flat_map` への破壊的変更を検討.
using api_mst_ship = std::vector<api_mst_ship_value_t>;

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_API_START2_API_MST_SHIP_HPP_INCLUDED
