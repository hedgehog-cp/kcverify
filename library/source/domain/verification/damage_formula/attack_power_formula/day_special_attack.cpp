#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"

// -----------------------------------------------------------------------------
// 攻撃力式のうち昼間特殊攻撃補正の実装をここに分離する.
// -----------------------------------------------------------------------------

// std
#include <algorithm>
#include <array>
#include <concepts>
#include <functional>
#include <initializer_list>
#include <optional>
#include <print>
#include <ranges>
#include <span>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

// kcv
#include "domain/verification/damage_formula/attack_power_formula/fleet_cutin.hpp"
#include "kcv/core/constants/equipment.hpp"
#include "kcv/core/constants/equipment_attributes.hpp"
#include "kcv/core/constants/ship.hpp"
#include "kcv/core/constants/ship_attributes.hpp"
#include "kcv/core/context_data.hpp"
#include "kcv/core/numeric/composed_function.hpp"
#include "kcv/core/numeric/interval.hpp"
#include "kcv/core/numeric/interval/basic_interval.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"
#include "kcv/domain/verification/entity/equipment.hpp"
#include "kcv/domain/verification/entity/ship.hpp"
#include "kcv/domain/verification/entity/slot.hpp"
#include "kcv/domain/verification/logic/logic.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_ship.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcv/external/kcsapi/extensions/damage_state.hpp"
#include "kcv/external/kcsapi/extensions/utility.hpp"
#include "kcv/external/kcsapi/types/enum/category.hpp"
#include "kcv/external/kcsapi/types/enum/day_attack_kind.hpp"
#include "kcv/external/kcsapi/types/enum/engagement.hpp"
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"
#include "kcv/external/kcsapi/types/enum/formation.hpp"
#include "kcv/external/kcsapi/types/enum/icon.hpp"
#include "kcv/external/kcsapi/types/enum/night_attack_kind.hpp"
#include "kcv/external/kcsapi/types/enum/stype.hpp"
#include "kcv/std_ext/exception.hpp"
#include "kcv/std_ext/utility.hpp"

namespace kcv::modifiers {
namespace {
namespace impl {

// night_implに同様の実装がある.
// std::optional<const T&>はC++26を待つため, rwでラップする.
using opt_mst_slotitem_value_t = std::optional<std::reference_wrapper<const kcv::kcsapi::api_mst_slotitem_value_t>>;

// night_implに同様の実装がある.
/// @brief i番目の装備とi番目の述語関数とが全て満たすならばtrueを返す.
template <std::predicate<const kcv::kcsapi::api_mst_slotitem_value_t&>... Preds>
bool matches_equipments(std::span<const opt_mst_slotitem_value_t> equipments, Preds&&... preds) {
    if (std::ranges::size(equipments) != sizeof...(Preds)) {
        return false;
    }

    auto i = 0uz;
    return ((equipments[i].has_value() and std::invoke(preds, equipments[i++]->get())) and ...);
}

bool is_fighter(const kcv::kcsapi::api_mst_slotitem_value_t& mst) {
    return std::get<kcv::kcsapi::category>(mst.api_type) == kcv::kcsapi::category::carrier_based_fighter;
}

bool is_bomber(const kcv::kcsapi::api_mst_slotitem_value_t& mst) {
    return std::get<kcv::kcsapi::category>(mst.api_type) == kcv::kcsapi::category::carrier_based_bomber;
}

bool is_torpedo(const kcv::kcsapi::api_mst_slotitem_value_t& mst) {
    return std::get<kcv::kcsapi::category>(mst.api_type) == kcv::kcsapi::category::carrier_based_torpedo;
}

auto cutin_air_attack(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::number {
    // night_implに同様の実装がある.
    // 表示装備がある場合は, 表示装備の個数==data.display_equipments.size();
    // -1でパディングされることはないはず.
    const auto display_equipments = data.display_equipments  //
                                  | std::ranges::views::transform([&ctx](auto id) -> opt_mst_slotitem_value_t {
                                        if (id == kcv::kcsapi::invalid_equipment_id) {
                                            return std::nullopt;
                                        }
                                        return std::make_optional(std::cref(kcv::find_mst(ctx.api_mst_slotitem(), id)));
                                    })
                                  | std::ranges::to<std::vector>();

    // [艦戦, 艦爆, 艦攻].
    if (matches_equipments(display_equipments, &is_fighter, &is_bomber, &is_torpedo)) {
        return 1.25;
    }

    // [艦爆, 艦爆, 艦攻].
    if (matches_equipments(display_equipments, &is_bomber, &is_bomber, &is_torpedo)) {
        return 1.2;
    }

    // [艦爆, 艦攻].
    if (matches_equipments(display_equipments, &is_bomber, &is_torpedo)) {
        return 1.15;
    }

    return 1;
}

}  // namespace impl
}  // namespace
}  // namespace kcv::modifiers

namespace mod = kcv::modifiers;

auto mod::day(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::day {
    namespace impl = kcv::modifiers::impl;

    // if (ctx.既存補正をoff) { return ctx.置換; }

    return std::visit(
        kcv::overloaded{
            [](const auto&) static noexcept -> kcv::functions::day { return kcv::functions::day::identity(); },
            [&ctx, &data](kcv::kcsapi::day_attack_kind v) -> kcv::functions::day {
                switch (v) {
                    case kcv::kcsapi::day_attack_kind::unknown:
                    case kcv::kcsapi::day_attack_kind::normal_attack:
                    case kcv::kcsapi::day_attack_kind::laser:
                        return kcv::functions::day{.a = 1.0};

                    case kcv::kcsapi::day_attack_kind::double_shelling:
                        return kcv::functions::day{.a = 1.2};

                    case kcv::kcsapi::day_attack_kind::cutin_main_sub:
                        return kcv::functions::day{.a = 1.1};

                    case kcv::kcsapi::day_attack_kind::cutin_main_radar:
                        return kcv::functions::day{.a = 1.2};

                    case kcv::kcsapi::day_attack_kind::cutin_main_ap:
                        return kcv::functions::day{.a = 1.3};

                    case kcv::kcsapi::day_attack_kind::cutin_main_main:
                        return kcv::functions::day{.a = 1.5};

                    case kcv::kcsapi::day_attack_kind::cutin_air_attack:
                        return kcv::functions::day{.a = impl::cutin_air_attack(ctx, data)};

                    case kcv::kcsapi::day_attack_kind::special_nelson:
                        return kcv::functions::day{.a = mod::special_nelson(ctx, data)};

                    case kcv::kcsapi::day_attack_kind::special_nagato:
                        return kcv::functions::day{.a = mod::special_nagato(ctx, data)};

                    case kcv::kcsapi::day_attack_kind::special_mutsu:
                        return kcv::functions::day{.a = mod::special_mutsu(ctx, data)};

                    case kcv::kcsapi::day_attack_kind::special_colorado:
                        return kcv::functions::day{.a = mod::special_colorado(ctx, data)};

                    case kcv::kcsapi::day_attack_kind::special_kongou:
                        return kcv::functions::day{.a = mod::special_kongou(ctx, data)};

                    case kcv::kcsapi::day_attack_kind::special_richelieu:
                        return kcv::functions::day{.a = mod::special_richelieu(ctx, data)};

                    case kcv::kcsapi::day_attack_kind::special_queen_elizabeth_class:
                        return kcv::functions::day{.a = mod::special_queen_elizabeth_class(ctx, data)};

                    case kcv::kcsapi::day_attack_kind::zuiun_multi_angle:
                        return kcv::functions::day{.a = 1.35};

                    case kcv::kcsapi::day_attack_kind::sea_air_multi_angle:
                        return kcv::functions::day{.a = 1.3};

                    case kcv::kcsapi::day_attack_kind::special_submarine_tender_23:
                        return kcv::functions::day{.a = mod::special_submarine_tender_23(ctx, data)};

                    case kcv::kcsapi::day_attack_kind::special_submarine_tender_34:
                        return kcv::functions::day{.a = mod::special_submarine_tender_34(ctx, data)};

                    case kcv::kcsapi::day_attack_kind::special_submarine_tender_24:
                        return kcv::functions::day{.a = mod::special_submarine_tender_24(ctx, data)};

                    case kcv::kcsapi::day_attack_kind::special_yamato_3_ships:
                        return kcv::functions::day{.a = mod::special_yamato_3_ships(ctx, data)};

                    case kcv::kcsapi::day_attack_kind::special_yamato_2_ships:
                        return kcv::functions::day{.a = mod::special_yamato_2_ships(ctx, data)};

                    case kcv::kcsapi::day_attack_kind::shelling:
                    case kcv::kcsapi::day_attack_kind::air_attack:
                    case kcv::kcsapi::day_attack_kind::depth_charge:
                    case kcv::kcsapi::day_attack_kind::torpedo:
                    case kcv::kcsapi::day_attack_kind::rocket:
                    case kcv::kcsapi::day_attack_kind::landing_daihatsu:
                    case kcv::kcsapi::day_attack_kind::landing_toku_daihatsu:
                    case kcv::kcsapi::day_attack_kind::landing_daihatsu_tank:
                    case kcv::kcsapi::day_attack_kind::landing_amphibious:
                    case kcv::kcsapi::day_attack_kind::landing_toku_daihatsu_tank:
                        return kcv::functions::day{.a = 1.0};
                }

                return kcv::functions::day::identity();
            }
        },
        data.attack_kind
    );
}