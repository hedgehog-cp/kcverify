#include "kcv/core/constants/ship_attributes.hpp"
#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"

// -----------------------------------------------------------------------------
// 攻撃力式のうち砲撃戦.航空攻撃補正の実装をここに分離する.
// -----------------------------------------------------------------------------

// kcv
#include "kcv/core/context_data.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"
#include "kcv/domain/verification/logic/logic.hpp"

namespace kcv::modifiers {
namespace {
namespace impl {

/// @brief 通常艦隊または遊撃部隊において, 攻撃艦が警戒陣主力であるかを検証する.
bool is_vanguard_main_in_single_fleet(const kcv::battlelog& data) {
    const auto& attacker_fleet = kcv::get_attacker_fleet(data);
    return static_cast<double>(data.attacker_ship + 1) / attacker_fleet.ships().size() > 0.5;
}

/// @brief 連合艦隊において, 攻撃艦が警戒陣主力であるかを検証する.
bool is_vanguard_main_in_combined_fleet(const kcv::battlelog& data) {
    constexpr auto escort_flagship_index = 6uz;
    switch (data.attacker_ship) {
        case escort_flagship_index:
        case escort_flagship_index + 1:
        case escort_flagship_index + 2:
            return true;

        default:
            return false;
    }
}

/// @brief 攻撃艦が警戒陣主力であるかを検証する.
bool is_vanguard_main(const kcv::battlelog& data) {
    const auto& attacker_fleet_data = kcv::get_attacker_fleet_data(data);
    const bool is_single_fleet      = attacker_fleet_data.combined_flag() == 0;
    if (is_single_fleet) {
        return is_vanguard_main_in_single_fleet(data);
    }

    return is_vanguard_main_in_combined_fleet(data);
}

/// @brief 対潜戦闘における警戒陣の陣形補正を返す.
auto asw_modifier_in_vanguard(const kcv::battlelog& data) -> kcv::functions::formation {
    if (is_vanguard_main(data)) {
        return kcv::functions::formation{.a = 1.0};
    }

    return kcv::functions::formation{.a = 0.6};
}

/// @brief 対潜戦闘における陣形補正を返す.
auto asw_modifier(const kcv::battlelog& data) -> kcv::functions::formation {
    switch (kcv::get_attacker_formation(data)) {
        case kcv::kcsapi::formation::line_ahead:
            return kcv::functions::formation{.a = 0.6};

        case kcv::kcsapi::formation::double_line:
            return kcv::functions::formation{.a = 0.8};

        case kcv::kcsapi::formation::diamond:
            return kcv::functions::formation{.a = 1.2};

        case kcv::kcsapi::formation::echelon:
            return kcv::functions::formation{.a = 1.1};

        case kcv::kcsapi::formation::line_abreast:
            return kcv::functions::formation{.a = 1.3};

        case kcv::kcsapi::formation::vanguard:
            return asw_modifier_in_vanguard(data);

        case kcv::kcsapi::formation::Cruising1:
            return kcv::functions::formation{.a = 1.3};

        case kcv::kcsapi::formation::Cruising2:
            return kcv::functions::formation{.a = 1.1};

        case kcv::kcsapi::formation::Cruising3:
            return kcv::functions::formation{.a = 1.0};

        case kcv::kcsapi::formation::Cruising4:
            return kcv::functions::formation{.a = 0.7};
    }

    return kcv::functions::formation::identity();
}

/// @brief 対潜戦闘でない砲撃戦における警戒陣の攻撃側陣形補正を返す.
auto shelling_modifier_in_vanguard(const kcv::battlelog& data) -> kcv::functions::formation {
    if (is_vanguard_main(data)) {
        return kcv::functions::formation{.a = 0.5};
    }

    return kcv::functions::formation{.a = 1.0};
}

/// @brief 対潜戦闘でない砲撃戦における攻撃側陣形補正を返す.
auto shelling_modifier(const kcv::battlelog& data) -> kcv::functions::formation {
    switch (kcv::get_attacker_formation(data)) {
        case kcv::kcsapi::formation::line_ahead:
            return kcv::functions::formation{.a = 1.0};

        case kcv::kcsapi::formation::double_line:
            return kcv::functions::formation{.a = 0.8};

        case kcv::kcsapi::formation::diamond:
            return kcv::functions::formation{.a = 0.7};

        case kcv::kcsapi::formation::echelon:
            return kcv::functions::formation{.a = 0.75};

        case kcv::kcsapi::formation::line_abreast:
            return kcv::functions::formation{.a = 0.6};

        case kcv::kcsapi::formation::vanguard:
            return shelling_modifier_in_vanguard(data);

        case kcv::kcsapi::formation::Cruising1:
            return kcv::functions::formation{.a = 0.8};

        case kcv::kcsapi::formation::Cruising2:
            return kcv::functions::formation{.a = 1.0};

        case kcv::kcsapi::formation::Cruising3:
            return kcv::functions::formation{.a = 0.7};

        case kcv::kcsapi::formation::Cruising4:
            return kcv::functions::formation{.a = 1.1};
    }

    return kcv::functions::formation::identity();
}

/// @brief 砲撃戦における攻撃側陣形補正を返す.
auto hougeki_modifier(const kcv::battlelog& data) -> kcv::functions::formation {
    if (kcv::is_submarine(kcv::get_defender(data).mst())) {
        return asw_modifier(data);
    }

    return shelling_modifier(data);
}

/// @brief 夜間攻撃における攻撃側陣形補正を返す.
auto torpedo_modifier(const kcv::battlelog& data) -> kcv::functions::formation {
    switch (kcv::get_attacker_formation(data)) {
        case kcv::kcsapi::formation::line_ahead:
            return kcv::functions::formation{.a = 1.0};

        case kcv::kcsapi::formation::double_line:
            return kcv::functions::formation{.a = 0.8};

        case kcv::kcsapi::formation::diamond:
            return kcv::functions::formation{.a = 0.7};

        case kcv::kcsapi::formation::echelon:
            return kcv::functions::formation{.a = 0.6};

        case kcv::kcsapi::formation::line_abreast:
            return kcv::functions::formation{.a = 0.6};

        case kcv::kcsapi::formation::vanguard:
            return kcv::functions::formation{.a = 1.0};

        case kcv::kcsapi::formation::Cruising1:
            return kcv::functions::formation{.a = 0.7};

        case kcv::kcsapi::formation::Cruising2:
            return kcv::functions::formation{.a = 0.9};

        case kcv::kcsapi::formation::Cruising3:
            return kcv::functions::formation{.a = 0.6};

        case kcv::kcsapi::formation::Cruising4:
            return kcv::functions::formation{.a = 1.0};
    }

    return kcv::functions::formation::identity();
}

/// @brief 夜間攻撃における警戒陣の攻撃側陣形補正を返す.
auto night_modifier_in_vanguard(const kcv::battlelog& data) -> kcv::functions::formation {
    if (is_vanguard_main(data)) {
        return kcv::functions::formation{.a = 0.5};
    }

    return kcv::functions::formation{.a = 1.0};
}

/// @brief 夜間攻撃における攻撃側陣形補正を返す.
auto night_modifier(const kcv::battlelog& data) -> kcv::functions::formation {
    switch (kcv::get_attacker_formation(data)) {
        case kcv::kcsapi::formation::vanguard:
            return night_modifier_in_vanguard(data);

        default:
            return kcv::functions::formation{.a = 1.0};
    }
}

}  // namespace impl
}  // namespace
}  // namespace kcv::modifiers

// 長いのでエイリアス.
namespace mod = kcv::modifiers;

auto mod::formation(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::formation {
    namespace impl = kcv::modifiers::impl;

    // if (ctx.既存補正をoff) { return ctx.置換; }

    switch (data.phase) {
        case kcv::phase::sp_midnight:
            return impl::night_modifier(data);

        case kcv::phase::opening_taisen:
            return impl::asw_modifier(data);

        case kcv::phase::opening_atack:
            return impl::torpedo_modifier(data);

        case kcv::phase::hougeki:
            return impl::hougeki_modifier(data);

        case kcv::phase::raigeki:
            return impl::torpedo_modifier(data);

        case kcv::phase::friendly:
        case kcv::phase::midnight:
            return impl::night_modifier(data);
    }

    return kcv::functions::formation::identity();
}