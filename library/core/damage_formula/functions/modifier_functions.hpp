#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_MODIFIER_FUNCTIONS_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_MODIFIER_FUNCTIONS_HPP_INCLUDED

// std
#include <cmath>
#include <limits>
#include <optional>

// kcv
#include "core/damage_formula/functions/composable.hpp"
#include "extensions/interval.hpp"
#include "extensions/interval/basic_interval.hpp"

namespace kcv {
namespace functions {

/// @brief 線形補正逆関数.
struct liner_inverse final : public kcv::functions::composable<liner_inverse> {
    /// @brief 乗算補正値.
    kcv::interval a = 1.0;

    /// @brief 加算補正値.
    kcv::interval b = 0.0;

    /// @brief 線形補正逆関数を適用する.
    auto operator()(const auto& x) const noexcept -> std::optional<kcv::interval> {
        if (kcv::is_zero(a)) {
            return std::nullopt;
        }

        if (kcv::is_negative(a)) {
            return std::nullopt;
        }

        return (x - b) / a;
    }
};

/// @brief 線形補正関数.
struct liner final : public kcv::functions::composable<liner> {
    /// @brief 乗算補正値.
    kcv::number a = 1.0;

    /// @brief 加算補正値.
    kcv::number b = 0.0;

    /// @brief 線形補正関数を適用する.
    auto operator()(const auto& x) const noexcept -> kcv::number {
        return x * a + b;
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> kcv::functions::liner_inverse {
        return liner_inverse{
            .a = kcv::make_interval(a),
            .b = kcv::make_interval(b),
        };
    }
};

/// @brief 砲撃戦.航空攻撃補正逆関数.
struct air_attack_inverse final : public kcv::functions::composable<air_attack_inverse> {
    /// @brief 無効なとき, 補正を適用せず恒等変換となる.
    bool is_enabled = true;

    /// @brief 砲撃戦.航空攻撃補正逆関数を適用する.
    auto operator()(const kcv::interval& x) const noexcept -> kcv::interval {
        if (not is_enabled) {
            return x;
        }

        return (x - 25.0) / 1.5 - 15.0;
    }
};

/// @brief 砲撃戦.航空攻撃補正関数.
struct air_attack final : public kcv::functions::composable<air_attack> {
    /// @brief 無効なとき, 補正を適用せず恒等変換となる.
    bool is_enabled = true;

    /// @brief 砲撃戦.航空攻撃補正関数を適用する.
    auto operator()(const kcv::number& x) const noexcept -> kcv::number {
        if (not is_enabled) {
            return x;
        }

        return (x + 15.0) * 1.5 + 25.0;
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> air_attack_inverse {
        return air_attack_inverse{.is_enabled = is_enabled};
    }
};

/// @brief 床逆関数.
struct floor_inverse final : public kcv::functions::composable<floor_inverse> {
    /// @brief 無効なとき, 補正を適用せず恒等変換となる.
    bool is_enabled = true;

    /// @brief 床逆関数を適当する.
    auto operator()(const kcv::interval& x) const noexcept -> kcv::interval {
        if (not is_enabled) {
            return x;
        }

        return kcv::interval{
            std::ceil(x.lower()),
            std::ceil(x.upper()) + 1,
        };
    }
};

/// @brief 床関数.
struct floor final : public kcv::functions::composable<floor> {
    /// @brief 無効なとき, 補正を適用せず恒等変換となる.
    bool is_enabled = true;

    /// @brief 床関数を適用する.
    auto operator()(const kcv::number& x) const noexcept -> kcv::number {
        if (not is_enabled) {
            return x;
        }

        return kcv::number{
            std::floor(x.lower()),
            std::floor(x.upper()),
        };
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> floor_inverse {
        return floor_inverse{.is_enabled = is_enabled};
    }
};

/// @brief ソフトキャップ補正逆関数.
struct softcap_inverse final : public kcv::functions::composable<softcap_inverse> {
    /// @brief キャップ値.
    kcv::interval cap;

    /// @brief ソフトキャップ補正逆関数を適用する.
    auto operator()(const kcv::interval& x) const noexcept -> std::optional<kcv::interval> {
        if (kcv::is_negative(x)) {
            return std::nullopt;
        }

        return x < cap ? x : kcv::square(x - cap) + cap;
    }
};

/// @brief ソフトキャップ補正関数.
struct softcap final : public kcv::functions::composable<softcap> {
    /// @brief キャップ値.
    kcv::number cap;

    /// @brief ソフトキャップ補正関数を適用する.
    auto operator()(const kcv::number& precap) const noexcept -> kcv::number {
        return kcv::min(precap, cap) + kcv::sqrt(kcv::max(precap - cap, kcv::number{0.0}));
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> softcap_inverse {
        return softcap_inverse{
            .cap = kcv::make_interval(cap),
        };
    }
};

/// @brief PT小鬼群補正逆関数.
struct pt_imp_inverse final : public kcv::functions::composable<pt_imp_inverse> {
    /// @brief 無効なとき, 補正を適用せず恒等変換となる.
    bool is_enabled = true;

    /// @brief PT補正逆関数を適用する.
    auto operator()(const kcv::interval& x) const noexcept -> std::optional<kcv::interval> {
        if (not is_enabled) {
            return x;
        }

        const auto a = 6.0 * x - 55.0;
        if (kcv::is_negative(a)) {
            return std::nullopt;
        }

        const auto b = -3.0 * x + kcv::sqrt(kcv::interval{5.0}) * kcv::sqrt(a) + 25.0;
        if (kcv::is_zero(b)) {
            return std::nullopt;
        }

        return -10.0 / 9.0 * b;
    }
};

/// @brief PT小鬼群補正関数.
struct pt_imp final : public kcv::functions::composable<pt_imp> {
    /// @brief 無効なとき, 補正を適用せず恒等変換となる.
    bool is_enabled = true;

    /// @brief PT小鬼群補正関数を適用する.
    auto operator()(const kcv::number& x) const noexcept -> std::optional<kcv::number> {
        if (not is_enabled) {
            return x;
        }

        if (kcv::is_negative(x)) {
            return std::nullopt;
        }

        return 0.3 * x + kcv::sqrt(x) + 10.0;
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> pt_imp_inverse {
        return pt_imp_inverse{.is_enabled = is_enabled};
    }
};

/// @brief 急所補正逆関数.
struct critical_inverse final : public kcv::functions::composable<critical_inverse> {
    /// @brief 急所攻撃であるか.
    bool is_enabled = true;

    /// @brief 急所補正逆関数を適用する.
    auto operator()(const kcv::interval& x) const noexcept -> kcv::interval {
        if (not is_enabled) {
            return x;
        }

        return x / 1.5;
    }
};

/// @brief 急所補正関数.
struct critical final : public kcv::functions::composable<critical> {
    /// @brief 急所攻撃であるか.
    bool is_enabled = true;

    /// @brief 急所補正関数を適用する.
    auto operator()(const kcv::number& x) const noexcept -> kcv::number {
        if (not is_enabled) {
            return x;
        }

        return x * 1.5;
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> critical_inverse {
        return critical_inverse{.is_enabled = is_enabled};
    }
};

/// @brief 爆雷装甲減少補正キャップ逆関数.
struct break_armor_cap_inverse final : public kcv::functions::composable<break_armor_cap_inverse> {
    /// @brief 爆雷装甲減少補正が有効.
    bool is_enable = true;

    /// @brief 爆雷装甲減少補正キャップ逆関数を適用する.
    auto operator()(const kcv::interval& x) const noexcept -> kcv::interval {
        if (not is_enable) {
            return x;
        }

        return kcv::interval{
            -std::numeric_limits<kcv::interval::base_type>::infinity(),
            x.upper(),
        };
    }
};

/// @brief 爆雷装甲減少補正キャップ関数.
struct depth_armor_break_cap final : public kcv::functions::composable<depth_armor_break_cap> {
    /// @brief 爆雷装甲減少補正が有効.
    bool is_enable = true;

    /// @brief 爆雷装甲減少補正キャップ関数を適用する.
    auto operator()(const kcv::number& x) const noexcept -> kcv::number {
        if (not is_enable) {
            return x;
        }

        return kcv::number{
            std::max(x.lower(), 1.0),
            std::max(x.upper(), 1.0),
        };
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> break_armor_cap_inverse {
        return break_armor_cap_inverse{};
    }
};

struct aromor_rand final : public kcv::functions::composable<aromor_rand> {
    static auto operator()(const kcv::number& x) noexcept -> kcv::number {
        // [0, 1)の乱数を扱う.
        // 下側は0に固定できる.
        // const auto min_rand = 0.0;
        // 上側は直後に切り捨てがあるため, 1より少しだけ小さい数を乗算する.
        // 装甲は大きくても十進3桁なので, 小数点以下4桁もあれば十分. より安全側に+1桁.
        const auto sup_rand = std::floor(0.99999 * std::floor(x.upper()));

        return kcv::number{x.lower() * 0.7, x.upper() * 0.7 + sup_rand * 0.6};
    }
};

}  // namespace functions
}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_MODIFIER_FUNCTIONS_HPP_INCLUDED
