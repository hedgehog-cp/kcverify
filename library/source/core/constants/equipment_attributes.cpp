#include "kcv/core/constants/equipment_attributes.hpp"

// kcv
#include "kcv/core/constants/equipment.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcv/external/kcsapi/types/api_type.hpp"
#include "kcv/external/kcsapi/types/enum/category.hpp"
#include "kcv/external/kcsapi/types/enum/icon.hpp"

bool kcv::is_radar(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    return std::get<kcv::kcsapi::icon>(mst.api_type) == kcsapi::icon::radar;
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

bool kcv::is_sonor(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (std::get<kcv::kcsapi::category>(mst.api_type)) {
        case kcv::kcsapi::category::sonar:
        case kcv::kcsapi::category::sonar_large:
            return true;

        default:
            return false;
    }
}

bool kcv::is_depth_charge(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (std::get<kcv::kcsapi::category>(mst.api_type)) {
        case kcv::kcsapi::category::depth_charge:
            return true;

        default:
            return false;
    }
}

bool kcv::is_depth_charge_projector(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::equipment_literals::operator""_id;
        case "九四式爆雷投射機"_id:
        case "三式爆雷投射機"_id:
        case "三式爆雷投射機 集中配備"_id:
        case "試製15cm9連装対潜噴進砲"_id:
        case "RUR-4A Weapon Alpha改"_id:
        case "Mk.32 対潜魚雷(Mk.2落射機)"_id:
            return true;

        default:
            return false;
    }
}

bool kcv::is_synergistic_depth_charge(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::equipment_literals::operator""_id;
        case "九五式爆雷"_id:
        case "二式爆雷"_id:
        case "対潜短魚雷(試作初期型)"_id:
        case "Hedgehog(初期型)"_id:
        case "二式爆雷改二"_id:
            return true;

        default:
            return false;
    }
}

bool kcv::is_ap_depth_charge(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::equipment_literals::operator""_id;
        case "九五式爆雷"_id:
        case "二式爆雷"_id:
        case "RUR-4A Weapon Alpha改"_id:
        case "対潜短魚雷(試作初期型)"_id:
        case "Hedgehog(初期型)"_id:
        case "Mk.32 対潜魚雷(Mk.2落射機)"_id:
        case "二式爆雷改二"_id:
            return true;

        default:
            return false;
    }
}

bool kcv::is_cl_fit_main_gun(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::equipment_literals::operator""_id;
        case "14cm連装砲"_id:
        case "14cm連装砲改"_id:
        case "15.2cm連装砲"_id:
        case "15.2cm連装砲改"_id:
        case "15.2cm連装砲改二"_id:
        case "6inch 連装速射砲 Mk.XXI"_id:
        case "Bofors 15.2cm連装砲 Model 1930"_id:
        case "Bofors 15cm連装速射砲 Mk.9 Model 1938"_id:
        case "Bofors 15cm連装速射砲 Mk.9改+単装速射砲 Mk.10改 Model 1938"_id:
        case "14cm連装砲改二"_id:
        case "13.8cm連装砲"_id:
        case "13.8cm連装砲改"_id:
            return true;

        default:
            return false;
    }
}

bool kcv::is_cl_fit_secondary_gun(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::equipment_literals::operator""_id;
        case "14cm単装砲"_id:
        case "15.2cm単装砲"_id:
            return true;

        default:
            return false;
    }
}

bool kcv::is_italian_fit_main_gun(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (mst.api_id) {
        using kcv::literals::equipment_literals::operator""_id;
        case "203mm/53 連装砲"_id:
            return true;

        default:
            return false;
    }
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
    if (kcv::is_cb_swordfish(mst)) {
        return true;
    }

    switch (mst.api_id) {
        using kcv::literals::equipment_literals::operator""_id;
        case "零戦62型(爆戦/岩井隊)"_id:
        case "彗星一二型(三一号光電管爆弾搭載機)"_id:
            return true;
    }

    switch (std::get<kcv::kcsapi::icon>(mst.api_type)) {
        case kcv::kcsapi::icon::night_fighter:
        case kcv::kcsapi::icon::night_attacker:
        case kcv::kcsapi::icon::night_bomber:
            return true;

        default:
            return false;
    }
}

bool kcv::is_late_model_bow_torpedo(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (mst.api_id) {
        case "後期型艦首魚雷(6門)"_id:
        case "熟練聴音員+後期型艦首魚雷(6門)"_id:
        case "後期型53cm艦首魚雷(8門)"_id:
        case "21inch艦首魚雷発射管6門(後期型)"_id:
        case "潜水艦後部魚雷発射管4門(後期型)"_id:
        case "後期型艦首魚雷(4門)"_id:
        case "熟練聴音員+後期型艦首魚雷(4門)"_id:
        case "21inch艦首魚雷発射管4門(後期型)"_id:
            return true;

        default:
            return false;
    }
}