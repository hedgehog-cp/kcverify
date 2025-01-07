#ifndef KCVERIFY_KCSAPI_TYPES_API_SHIP_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_API_SHIP_HPP_INCLUDED

// std
#include <optional>
#include <vector>

// kcv
#include "kcsapi/types/api_kyouka.hpp"
#include "kcsapi/types/api_sp_effectitems.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 所属艦船情報.
struct api_ship final {
    int api_back;
    int api_bull;
    int api_cond;
    std::vector<int> api_exp;
    int api_fuel;
    int api_id;
    std::vector<int> api_kaihi;
    std::vector<int> api_karyoku;
    kcsapi::api_kyouka api_kyouka;
    int api_leng;
    int api_locked;
    int api_locked_equip;
    std::vector<int> api_lucky;
    int api_lv;
    int api_maxhp;
    std::vector<int> api_ndock_item;
    int api_ndock_time;
    int api_nowhp;
    std::vector<int> api_onslot;
    std::vector<int> api_raisou;
    std::vector<int> api_sakuteki;
    std::optional<int> api_sally_area;
    int api_ship_id;
    std::vector<int> api_slot;
    int api_slot_ex;
    int api_slotnum;
    int api_soku;
    int api_sortno;
    std::vector<int> api_soukou;
    int api_srate;
    std::vector<int> api_taiku;
    std::vector<int> api_taisen;
    std::optional<api_sp_effect_items> api_sp_effect_items;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_API_SHIP_HPP_INCLUDED
