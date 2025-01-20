#ifndef KCVERIFY_DAMAGE_FORMULA_EQUIPMENT_LEVEL_BONUSES_HPP_INCLUDED
#define KCVERIFY_DAMAGE_FORMULA_EQUIPMENT_LEVEL_BONUSES_HPP_INCLUDED

// std
#include <variant>

// kcv
#include "constants/equipment.hpp"
#include "kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcsapi/types/api_type.hpp"
#include "kcsapi/types/enum/category.hpp"
#include "numeric.hpp"

namespace kcv {
namespace equipment_level_bonuses {

template <typename T>
struct no_bonus final {
    static constexpr auto operator()(int) noexcept -> T {
        return 0;
    }
};

template <typename T>
struct liner_bonus final {
    const T k;

    constexpr auto operator()(int level) const -> T {
        return k * T{level};
    }
};

template <typename T>
struct sqrt_bonus final {
    const T k;

    constexpr auto operator()(int level) const -> T {
        return k * kcv::sqrt(T{level});
    }
};

template <typename T>
using bonus_formula = std::variant<no_bonus<T>, liner_bonus<T>, sqrt_bonus<T>>;

template <typename T>
constexpr auto day_shelling(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept -> bonus_formula<T> {
    using none  = no_bonus<T>;
    using liner = liner_bonus<T>;
    using sqrt  = sqrt_bonus<T>;

    const auto& category = std::get<kcv::kcsapi::idx_type::category>(mst.api_type);
    const auto& id       = mst.api_id;

    switch (category) {
        case kcv::kcsapi::category::main_gun_small:
        case kcv::kcsapi::category::main_gun_medium:
        case kcv::kcsapi::category::aa_shell:
        case kcv::kcsapi::category::ap_shell:
        case kcv::kcsapi::category::aa_gun:
        case kcv::kcsapi::category::landing_craft:
        case kcv::kcsapi::category::searchlight:
        case kcv::kcsapi::category::submarine_torpedo:
        case kcv::kcsapi::category::command_facility:
        case kcv::kcsapi::category::aviation_personnel:
        case kcv::kcsapi::category::aa_director:
        case kcv::kcsapi::category::rocket:
        case kcv::kcsapi::category::surface_ship_personnel:
        case kcv::kcsapi::category::searchlight_large:
        case kcv::kcsapi::category::special_amphibious_tank:
        case kcv::kcsapi::category::army_infantry:
        case kcv::kcsapi::category::surface_ship_equipment:
            return sqrt{1.0};

        case kcv::kcsapi::category::main_gun_large:
            return sqrt{1.5};

        case kcv::kcsapi::category::secondary_gun:
            switch (id) {
                using kcv::literals::equipment_literals::operator""_id;

                case "12.7cm連装高角砲"_id:
                case "8cm高角砲"_id:
                case "10cm連装高角砲(砲架)"_id:
                case "12.7cm高角砲+高射装置"_id:
                case "10.5cm連装砲"_id:
                case "5inch連装砲 Mk.28 mod.2"_id:
                case "8cm高角砲改+増設機銃"_id:
                case "10cm連装高角砲改+増設機銃"_id:
                case "5inch 単装高角砲群"_id:
                case "65mm/64 単装速射砲改"_id:
                case "10cm連装高角砲群 集中配備"_id:
                case "12cm単装高角砲+25mm機銃増備"_id:
                    return liner{0.2};

                case "15.5cm三連装副砲"_id:
                case "15cm連装副砲"_id:
                case "15.5cm三連装副砲改"_id:
                case "15.2cm三連装砲"_id:
                case "5inch連装砲(副砲配置) 集中配備"_id:
                    return liner{0.3};

                case "15.2cm単装砲"_id:
                case "OTO 152mm三連装速射砲"_id:
                case "90mm単装高角砲"_id:
                    return sqrt{1.0};

                case "15.5cm三連装副砲改二"_id:  // 未検証
                default:
                    return none{};
            }

        case kcv::kcsapi::category::sonar:
        case kcv::kcsapi::category::sonar_large:
            return sqrt{0.75};

        case kcv::kcsapi::category::depth_charge:
            switch (id) {
                using kcv::literals::equipment_literals::operator""_id;

                case "九四式爆雷投射機"_id:
                case "三式爆雷投射機"_id:
                case "三式爆雷投射機 集中配備"_id:
                case "試製15cm9連装対潜噴進砲"_id:
                case "二式12cm迫撃砲改"_id:
                case "二式12cm迫撃砲改 集中配備"_id:
                case "RUR-4A Weapon Alpha改"_id:
                case "対潜短魚雷(試作初期型)"_id:
                case "Hedgehog(初期型)"_id:
                    return sqrt{0.75};

                case "Mk.32 対潜魚雷(Mk.2落射機)"_id:  // 未検証
                default:
                    return none{};
            }

        default:
            return none{};
    }
}

template <typename T>
constexpr auto torpedo(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept -> bonus_formula<T> {
    using none  = no_bonus<T>;
    using liner = liner_bonus<T>;
    using sqrt  = sqrt_bonus<T>;

    const auto& category = std::get<kcv::kcsapi::idx_type::category>(mst.api_type);

    switch (category) {
        case kcv::kcsapi::category::torpedo:
        case kcv::kcsapi::category::aa_gun:
            return sqrt{1.2};

        case kcv::kcsapi::category::submarine_torpedo:
            return liner{1.0};

        default:
            return none{};
    }
}

}  // namespace equipment_level_bonuses
}  // namespace kcv

#endif  // KCVERIFY_DAMAGE_FORMULA_EQUIPMENT_LEVEL_BONUSES_HPP_INCLUDED
