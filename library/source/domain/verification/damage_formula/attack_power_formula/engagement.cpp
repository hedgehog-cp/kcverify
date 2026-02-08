#include "kcv/domain/verification/damage_formula/attack_power_formula.hpp"

// -----------------------------------------------------------------------------
// 攻撃力式のうち交戦形態補正の実装をここに分離する.
// -----------------------------------------------------------------------------

// kcv
#include "kcv/core/context_data.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/damage_formula/modifier_functions.hpp"

namespace kcv::modifiers {
namespace {
namespace impl {

/// @brief 僚艦夜戦突撃の交戦形態補正を返す.
auto special_kongou(const kcv::battlelog& data) noexcept -> kcv::functions::engagement {
    switch (data.engagement) {
        case kcv::kcsapi::engagement::green_t:
            return kcv::functions::engagement{.a = 1.25};

        case kcv::kcsapi::engagement::parallel:
        case kcv::kcsapi::engagement::head_on:
            return kcv::functions::engagement{.a = 1.0};

        case kcv::kcsapi::engagement::red_t:
            return kcv::functions::engagement{.a = 0.8};
    }

    return kcv::functions::engagement::identity();
}

/// @brief ネルソンタッチの交戦形態補正を返す.
auto special_nelson(const kcv::battlelog& data) noexcept -> kcv::functions::engagement {
    switch (data.engagement) {
        case kcv::kcsapi::engagement::green_t:
        case kcv::kcsapi::engagement::parallel:
        case kcv::kcsapi::engagement::head_on:
            return kcv::functions::engagement{.a = 1.0};

        case kcv::kcsapi::engagement::red_t:
            return kcv::functions::engagement{.a = 1.25};
    }

    return kcv::functions::engagement::identity();
}

/// @brief 夜間攻撃の交戦形態補正を返す.
auto night_modifier(const kcv::battlelog& data) noexcept -> kcv::functions::engagement {
    switch (std::get<kcv::kcsapi::night_attack_kind>(data.attack_kind)) {
        case kcv::kcsapi::night_attack_kind::special_nelson:
            // 僚艦夜戦突撃を交戦形態補正とするならばネルソンタッチもここだろう.
            // ソース無し.
            return special_nelson(data);

        case kcv::kcsapi::night_attack_kind::special_kongou:
            // 僚艦夜戦突撃のT字有利およびT字不利の補正は, 本体の補正より前に位置するため交戦形態補正の一種とする.
            // https://x.com/hedgehog_hasira/status/1654086587649753088
            return special_kongou(data);

        default:
            return kcv::functions::engagement{.a = 1.0};
    }
}

/// @brief 主要な交戦形態補正を返す.
auto primary_modifier(const kcv::battlelog& data) noexcept -> kcv::functions::engagement {
    switch (data.engagement) {
        case kcv::kcsapi::engagement::green_t:
            return kcv::functions::engagement{.a = 1.2};

        case kcv::kcsapi::engagement::parallel:
            return kcv::functions::engagement{.a = 1.0};

        case kcv::kcsapi::engagement::head_on:
            return kcv::functions::engagement{.a = 0.8};

        case kcv::kcsapi::engagement::red_t:
            return kcv::functions::engagement{.a = 0.6};
    }

    return kcv::functions::engagement::identity();
}

}  // namespace impl
}  // namespace
}  // namespace kcv::modifiers

// 長いのでエイリアス.
namespace mod = kcv::modifiers;

auto mod::engagement(const kcv::context_data& ctx, const kcv::battlelog& data) -> kcv::functions::engagement {
    namespace impl = kcv::modifiers::impl;

    // if (ctx.既存補正をoff) { return ctx.置換; }

    switch (data.phase) {
        case kcv::phase::sp_midnight:
            return impl::night_modifier(data);

        case kcv::phase::opening_taisen:
        case kcv::phase::opening_atack:
        case kcv::phase::hougeki:
        case kcv::phase::raigeki:
            return impl::primary_modifier(data);

        case kcv::phase::friendly:
        case kcv::phase::midnight:
            return impl::night_modifier(data);
    }

    return kcv::functions::engagement::identity();
}