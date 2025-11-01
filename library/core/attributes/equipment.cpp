#include "core/attributes/equipment.hpp"

// kcv
#include "core/constants/equipment.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/api_type.hpp"
#include "models/kcsapi/types/enum/icon.hpp"

bool kcv::is_radar(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    return std::get<kcv::kcsapi::idx_type::icon>(mst.api_type) == kcsapi::icon::radar;
}

bool kcv::is_anti_air_radar(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    return kcv::is_radar(mst) and mst.api_tyku >= 2;
}

bool kcv::is_surface_radar(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    return kcv::is_radar(mst) and mst.api_saku >= 5;
}

bool kcv::is_accuracy_radar(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    return kcv::is_radar(mst) and mst.api_houm >= 8;
}

bool kcv::is_night_operation_aviation_personnel(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::equipment_literals::operator""_id;
        case "夜間作戦航空要員"_id:
        case "夜間作戦航空要員+熟練甲板員"_id:
            return true;

        default:
            return false;
    }
}

bool kcv::is_cb_swordfish(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::equipment_literals::operator""_id;
        case "Swordfish"_id:
        case "Swordfish Mk.II(熟練)"_id:
        case "Swordfish Mk.III(熟練)"_id:
            return true;

        default:
            return false;
    }
}

bool kcv::is_night_plane(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (std::get<kcv::kcsapi::idx_type::icon>(mst.api_type)) {
        case kcv::kcsapi::icon::night_fighter:
        case kcv::kcsapi::icon::night_attacker:
            return true;

        default:
            return false;
    }
}

bool kcv::is_semi_night_plane(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::equipment_literals::operator""_id;
        case "零戦62型(爆戦/岩井隊)"_id:
        case "彗星一二型(三一号光電管爆弾搭載機)"_id:
            return true;

        default:
            return false;
    }
}
