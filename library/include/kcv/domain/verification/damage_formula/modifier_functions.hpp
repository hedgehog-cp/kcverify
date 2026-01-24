#ifndef KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_MODIFIER_FUNCTIONS_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_MODIFIER_FUNCTIONS_HPP_INCLUDED

// std
#include <cmath>
#include <concepts>
#include <limits>
#include <optional>

// kcv
#include "kcv/core/numeric/composed_function.hpp"
#include "kcv/core/numeric/interval.hpp"

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

    /// @brief 恒等変換の関数を返す.
    static auto identity() noexcept -> liner {
        return liner{};
    }

    /// @brief 線形補正関数を適用する.
    auto operator()(const kcv::number& x) const noexcept -> kcv::number {
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

/// @brief 線形補正逆関数.
template <typename Tag>
struct basic_liner_inverse final : public kcv::functions::composable<basic_liner_inverse<Tag>> {
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
template <typename Tag>
struct basic_liner final : public kcv::functions::composable<basic_liner<Tag>> {
    /// @brief 乗算補正値.
    kcv::number a = 1.0;

    /// @brief 加算補正値.
    kcv::number b = 0.0;

    /// @brief 恒等変換の関数を返す.
    static auto identity() noexcept -> basic_liner {
        return basic_liner{};
    }

    /// @brief 線形補正関数を適用する.
    auto operator()(const kcv::number& x) const noexcept -> kcv::number {
        return x * a + b;
    }

    /// @brief 逆関数を返す.
    auto operator^(int) const noexcept -> kcv::functions::basic_liner_inverse<Tag> {
        return basic_liner_inverse<Tag>{
            .a = kcv::make_interval(a),
            .b = kcv::make_interval(b),
        };
    }
};

/// @brief 型がbasic_linerであるかを検証する.
template <typename T>
inline constexpr bool is_basic_liner_v = false;

/// @brief 型がbasic_linerであるかを検証する.
template <typename T>
inline constexpr bool is_basic_liner_v<kcv::functions::basic_liner<T>> = true;

// よくある一次補正をlinerのまま使うと, 補正順序の記述ミスや,
// 逆算結果の集計時にどの補正か分からないといった不都合がある.
// そこで, linerをstrong typeとすることで不都合の解決を図る.
// struct *_tagはこの場限りであり, 定義はない.

/// @brief 未知の第0種補正.
using f0 = kcv::functions::basic_liner<struct f0_tag>;

/// @brief 交戦形態補正.
using engagement = kcv::functions::basic_liner<struct engagement_tag>;

/// @brief 攻撃側陣形補正.
using formation = kcv::functions::basic_liner<struct formation_tag>;

/// @brief 損傷状態補正.
using damage_state = kcv::functions::basic_liner<struct damage_state_tag>;

/// @brief 前対潜シナジー補正.
using pre_asw = kcv::functions::basic_liner<struct pre_asw_tag>;

/// @brief 後対潜シナジー補正.
using post_asw = kcv::functions::basic_liner<struct post_asw_tag>;

/// @brief 未知の第14種補正.
using f14 = kcv::functions::basic_liner<struct f14_tag>;

/// @brief フィット砲補正.
using fit_gun = kcv::functions::basic_liner<struct fit_gun_tag>;

/// @brief 未知の第5種補正.
using f5 = kcv::functions::basic_liner<struct f5_tag>;

/// @brief 未知の第6種補正.
using f6 = kcv::functions::basic_liner<struct f6_tag>;

/// @brief 未知の第7種補正.
using f7 = kcv::functions::basic_liner<struct f7_tag>;

/// @brief 海域補正.
using map = kcv::functions::basic_liner<struct map_tag>;

/// @brief 期間限定海域.
using event = kcv::functions::basic_liner<struct event_tag>;

/// @brief 未知の第7種補正.
using f7 = kcv::functions::basic_liner<struct f7_tag>;

/// @brief 未知の第8種補正.
using f8 = kcv::functions::basic_liner<struct f8_tag>;

/// @brief 未知の第3種補正.
using f3 = kcv::functions::basic_liner<struct f3_tag>;

/// @brief 未知の第2種補正.
using f2 = kcv::functions::basic_liner<struct f2_tag>;

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

    /// @brief 恒等変換の関数を返す.
    static auto identity() noexcept -> air_attack {
        return air_attack{.is_enabled = false};
    }

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
struct floor_if_inverse final : public kcv::functions::composable<floor_if_inverse> {
    /// @brief 無効なとき, 補正を適用せず恒等変換となる.
    bool is_enabled = true;

    /// @brief 床逆関数を適当する.
    /// @details 半開区間 [lower, upper)に対する定義: [ceil(lower), ceil(upper)).
    auto operator()(const kcv::interval& x) const noexcept -> kcv::interval {
        if (not is_enabled) {
            return x;
        }

        return kcv::interval{
            std::ceil(x.lower()),
            std::ceil(x.upper()),
        };
    }

    /// @brief 床逆関数を適当する.
    /// @details 単一区間(整数)に対する定義: [x, x+1).
    /// この定義が使われるのは, 観測ダメージ=floor(攻撃力-防御力)を解くときのみ...たぶん.
    /// その他の場合は常に半開区間を対象にするときなので, intervalを引数による定義を使う...たぶん.
    /// @todo 単一区間(小数)について検討する.
    auto operator()(std::integral auto x) const noexcept -> kcv::interval {
        if (not is_enabled) {
            return x;
        }

        return kcv::interval{
            static_cast<kcv::interval::base_type>(x),
            static_cast<kcv::interval::base_type>(x) + 1,
        };
    }
};

/// @brief 床関数.
struct floor_if final : public kcv::functions::composable<floor_if> {
    /// @brief 無効なとき, 補正を適用せず恒等変換となる.
    bool is_enabled = true;

    /// @brief 恒等変換の関数を返す.
    static auto identity() noexcept -> floor_if {
        return floor_if{.is_enabled = false};
    }

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
    auto operator^(int) const noexcept -> floor_if_inverse {
        return floor_if_inverse{.is_enabled = is_enabled};
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

    /// @brief 恒等変換の関数を返す.
    static auto identity() noexcept -> softcap {
        return softcap{.cap = std::numeric_limits<kcv::number::base_type>::infinity()};
    }

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

    /// @brief 恒等変換の関数を返す.
    static auto identity() noexcept -> pt_imp {
        return pt_imp{.is_enabled = false};
    }

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

    /// @brief 恒等変換の関数を返す.
    static auto identity() noexcept -> critical {
        return critical{.is_enabled = false};
    }

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

    /// @brief 恒等変換の関数を返す.
    static auto identity() noexcept -> depth_armor_break_cap {
        return depth_armor_break_cap{.is_enable = false};
    }

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

/// @brief 装甲乱数補正逆関数.
struct aromor_rand_inverse final : public kcv::functions::composable<aromor_rand_inverse> {
    /// @brief 装甲乱数補正逆関数を適用する.
    auto operator()(const kcv::interval& x) const noexcept -> kcv::interval {
        const auto upper_by_lower = x.lower() / 0.7;
        const auto lower_by_upper = (x.upper() + 0.6) / 1.3;

        return kcv::interval{
            std::max(0.0, lower_by_upper),
            upper_by_lower,
        };
    }
};

/// @brief 装甲乱数補正関数.
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

    auto operator^(int) const noexcept -> aromor_rand_inverse {
        return aromor_rand_inverse{};
    }
};

}  // namespace functions
}  // namespace kcv

#endif  // KCV_DOMAIN_VERIFICATION_DAMAGE_FORMULA_MODIFIER_FUNCTIONS_HPP_INCLUDED
