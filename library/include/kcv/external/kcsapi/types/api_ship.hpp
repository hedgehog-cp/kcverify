#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_SHIP_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_SHIP_HPP_INCLUDED

// std
#include <optional>
#include <vector>

// kcv
#include "kcv/external/kcsapi/types/api_kyouka.hpp"
#include "kcv/external/kcsapi/types/api_sp_effectitems.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 所属艦船情報.
struct api_ship final {
    std::int32_t api_back;
    std::int32_t api_bull;
    std::int32_t api_cond;
    std::vector<std::int32_t> api_exp;
    std::int32_t api_fuel;
    std::int32_t api_id;
    std::vector<std::int32_t> api_kaihi;
    std::vector<std::int32_t> api_karyoku;
    kcv::kcsapi::api_kyouka api_kyouka;
    std::int32_t api_leng;
    std::int32_t api_locked;
    std::int32_t api_locked_equip;
    std::vector<std::int32_t> api_lucky;
    std::int32_t api_lv;
    std::int32_t api_maxhp;
    std::vector<std::int32_t> api_ndock_item;
    std::int32_t api_ndock_time;
    std::int32_t api_nowhp;
    std::vector<std::int32_t> api_onslot;
    std::vector<std::int32_t> api_raisou;
    std::vector<std::int32_t> api_sakuteki;
    std::optional<std::int32_t> api_sally_area;
    std::int32_t api_ship_id;
    std::vector<std::int32_t> api_slot;
    std::int32_t api_slot_ex;
    std::int32_t api_slotnum;
    std::int32_t api_soku;
    std::int32_t api_sortno;
    std::vector<std::int32_t> api_soukou;
    std::int32_t api_srate;
    std::vector<std::int32_t> api_taiku;
    std::vector<std::int32_t> api_taisen;
    std::optional<kcv::kcsapi::api_sp_effect_items> api_sp_effect_items;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_SHIP_HPP_INCLUDED
