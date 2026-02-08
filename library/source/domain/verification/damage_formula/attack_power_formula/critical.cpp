#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"

// -----------------------------------------------------------------------------
// 攻撃力式のうち急所弾補正, 熟練急所弾補正の実装をここに分離する.
// -----------------------------------------------------------------------------

// std
#include <cmath>
#include <cstdint>
#include <ranges>

// kcv
#include "kcv/core/constants/equipment_attributes.hpp"
#include "kcv/core/constants/ship.hpp"
#include "kcv/core/constants/ship_attributes.hpp"
#include "kcv/core/context_data.hpp"
#include "kcv/core/numeric/interval.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"
#include "kcv/domain/verification/entity/equipment.hpp"
#include "kcv/domain/verification/entity/ship.hpp"
#include "kcv/domain/verification/entity/slot.hpp"
#include "kcv/domain/verification/logic/logic.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcv/external/kcsapi/types/enum/category.hpp"

namespace kcv::modifiers {
namespace {
namespace impl {

/// @brief 砲撃戦において熟練急所弾であるかを検証する.
/// 熟練度>0の機体を搭載しているかは検証しない.
/// FIXME: 雑実装.
bool is_critical_air_attack_in_hougeki(const kcv::battlelog& data) {
    // 急所弾でない.
    if (not kcv::is_critical(data)) {
        return false;
    }

    const auto& attacker = kcv::get_attacker(data);
    const auto& defender = kcv::get_defender(data);

    if (kcv::is_submarine(defender.mst())) {
        // 対潜戦闘において加賀改二護による攻撃では熟練度補正が乗らない.
        // 加賀改二護というよりも正規空母だろうか?
        if (attacker.mst().api_id == kcv::ship_id("加賀改二護")) {
            return false;
        }

        // 対潜戦闘における航空攻撃.
        if (constexpr int air_attack = 8; kcv::classify_asw_operation(data) == air_attack) {
            return true;
        }
    }

    // 対陸上施設.
    if (kcv::is_installation(defender.mst())) {
        // 詳細不明.
        // - 艦攻, 艦爆を搭載している.
        // - 機数>0.
        // - 空母または補給艦.
        // - ???
    }

    // 対水上.
    {
        // 詳細不明.
        // - 艦攻, 艦爆を搭載している.
        // - 機数>0.
        // - 空母または補給艦.
        // - ???
    }

    // とりあえず, 空母が艦攻または艦爆を搭載している, とする.
    {
        if (kcv::is_aircraft_carrier(attacker.mst())) {
            static constexpr auto planes = {
                kcv::kcsapi::category::carrier_based_bomber,
                kcv::kcsapi::category::carrier_based_torpedo,
                kcv::kcsapi::category::jet_bomber,
            };
            if (kcv::has_equipment(attacker, planes)) {
                return true;
            }
        }
    }

    return false;
}

/// @brief 夜間攻撃が熟練急所弾であるかを検証する.
bool is_critical_air_attack_in_night(const kcv::battlelog& data) {
    // 急所弾でない.
    if (not kcv::is_critical(data)) {
        return false;
    }

    // 夜間航空攻撃である.
    if (kcv::is_night_air_attack(data)) {
        return true;
    }

    const auto& attacker = kcv::get_attacker(data);

    // 夜間砲撃空母による攻撃である.
    if (kcv::is_night_shellable_aircraft_carrier(attacker.mst())) {
        return false;
    }

    // Ark Royalのswordfish攻撃である.
    if (kcv::is_ark_royal(attacker.mst()) and kcv::has_available_plane(attacker, &kcv::is_cb_swordfish)) {
        return true;
    }

    // その他, 戦艦などによる攻撃である.
    return false;
}

/// @brief 航空攻撃であるかを検証する.
bool is_critical_air_attack(const kcv::battlelog& data) {
    switch (data.phase) {
        case kcv::phase::sp_midnight:
            return impl::is_critical_air_attack_in_night(data);

        case kcv::phase::opening_taisen:
            return false;

        case kcv::phase::opening_atack:
            return false;

        case kcv::phase::hougeki:
            return impl::is_critical_air_attack_in_hougeki(data);

        case kcv::phase::raigeki:
            return false;

        case kcv::phase::friendly:
        case kcv::phase::midnight:
            return impl::is_critical_air_attack_in_night(data);
    }

    return false;
}

/// @brief 攻撃が戦爆連合であるかを検証する.
/// @see damage_formula_vecrification.cpp
bool is_fba_combined_air_attack(const kcv::battlelog& data) {
    return std::visit(
        kcv::overloaded{
            [](kcv::kcsapi::day_attack_kind v) static noexcept -> bool {
                return v == kcv::kcsapi::day_attack_kind::cutin_air_attack;
            },
            [](const auto&) static noexcept -> bool { return false; },
        },
        data.attack_kind
    );
}

/// @brief 攻撃可能な艦載機であるかを検証する.
bool is_attackable_plane(const kcv::kcsapi::api_mst_slotitem_value_t& mst) noexcept {
    switch (std::get<kcv::kcsapi::category>(mst.api_type)) {
        case kcv::kcsapi::category::carrier_based_bomber:
        case kcv::kcsapi::category::carrier_based_torpedo:
        case kcv::kcsapi::category::seaplane_bomber:
        case kcv::kcsapi::category::as_patrol:
        case kcv::kcsapi::category::flying_boat:
        case kcv::kcsapi::category::jet_bomber:
            return true;

        default:
            return false;
    }
}

/// @brief 見かけの艦載機熟練度に対応する内部熟練度の最小値を返す.
/// @param aircraft_level 見かけの艦載機熟練度.
/// @return 内部熟練度の最小値
auto lower_internal_proficiency(std::int32_t aircraft_level) -> std::int32_t {
    switch (aircraft_level) {
        case 0:
            return 0;

        case 1:
            // 全損時に正規帰投した場合, 見かけの熟練度が1のとき, 内部熟練度の最小値は0.
            return 0;

        case 2:
            // 全損時に正規帰投した場合, 見かけの熟練度が2のとき, 内部熟練度の最小値は0.
            return 0;

        case 3:
            return 40;

        case 4:
            return 55;

        case 5:
            return 70;

        case 6:
            return 85;

        case 7:
            return 100;
    }

    return 0;
}

/// @brief 見かけの艦載機熟練度に対応する内部熟練度の最大値を返す.
/// @param aircraft_level 見かけの艦載機熟練度.
/// @return 内部熟練度の最大値.
auto upper_internal_proficiency(std::int32_t aircraft_level) -> std::int32_t {
    switch (aircraft_level) {
        case 0:
            return 9;

        case 1:
            return 24;

        case 2:
            return 39;

        case 3:
            return 54;

        case 4:
            return 69;

        case 5:
            return 84;

        case 6:
            return 99;

        case 7:
            return 120;
    }

    return 0;
}

/// @brief 内部熟練度に対応する定数を返す.
/// @param internal_proficiency 内部熟練度.
auto internal_proficiency_constant(std::int32_t internal_proficiency) -> std::int32_t {
    if (internal_proficiency <= 9) return 0;
    if (internal_proficiency <= 24) return 1;
    if (internal_proficiency <= 39) return 2;
    if (internal_proficiency <= 54) return 3;
    if (internal_proficiency <= 69) return 4;
    if (internal_proficiency <= 79) return 5;
    if (internal_proficiency <= 99) return 7;
    return 10;
}

/// @brief 見かけの艦載機熟練度に対応する内部熟練度補正を返す. スロット位置の重みづけ無し.
/// @param aircraft_level 見かけの艦載機熟練度.
/// @return 内部熟練度補正.
auto internal_proficiency_modifier(std::int32_t aircraft_level) -> kcv::number {
    const auto lower = impl::lower_internal_proficiency(aircraft_level);
    const auto upper = impl::upper_internal_proficiency(aircraft_level);
    return kcv::number{
        std::floor(std::sqrt(lower) + impl::internal_proficiency_constant(lower)),
        std::floor(std::sqrt(upper) + impl::internal_proficiency_constant(upper)),
    };
}

/// @brief 熟練度補正を返す.
/// @todo 対潜哨戒機の定数項補正(?)は未実装.
auto proficiency(const kcv::ship& attacker) -> kcv::functions::proficiency {
    auto total = kcv::number{1};

    // 隊長機から順に蓄積して計算していると考えられる.
    // https://x.com/hedgehog_hasira/status/1630585333279784962
    for (const auto& [index, slot] : attacker.slots() | std::ranges::views::enumerate) {
        // 全損すれば艦載機熟練度が0となるため機数>0の考慮は不要だと思うが, 念のためフィルタリングする.
        if (slot.equipment().has_value() and slot.aircraft_current() > 0) {
            if (impl::is_attackable_plane(slot.equipment()->mst())) {
                if (index == 0) {
                    // 隊長機.
                    total += impl::internal_proficiency_modifier(slot.equipment()->aircraft_level()) / 100;
                } else {
                    // 僚機.
                    total += impl::internal_proficiency_modifier(slot.equipment()->aircraft_level()) / 200;
                }
            }
        }
    }

    return kcv::functions::proficiency{.a = total};
}

}  // namespace impl
}  // namespace
}  // namespace kcv::modifiers

// 長いのでエイリアス.
namespace mod = kcv::modifiers;

auto mod::critical(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::critical {
    // if (ctx.既存補正をoff) { return ctx.置換; }

    return kcv::functions::critical{.is_enabled = kcv::is_critical(data)};
}

auto mod::proficiency(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::proficiency {
    namespace impl = kcv::modifiers::impl;

    // if (ctx.既存補正をoff) { return ctx.置換; }

    // 熟練急所弾.
    if (impl::is_critical_air_attack(data)) {
        // 戦爆連合の熟練度補正は不明.
        if (impl::is_fba_combined_air_attack(data)) {
            return kcv::functions::proficiency{.a = kcv::number::whole()};
        }

        return impl::proficiency(kcv::get_attacker(data));
    }

    return kcv::functions::proficiency::identity();
}

auto mod::floor_if_critical(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::floor_if {
    // if (ctx.既存補正をoff) { return ctx.置換; }

    return kcv::functions::floor_if{.is_enabled = kcv::is_critical(data)};
}