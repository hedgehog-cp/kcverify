#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_TORPEDO_ATTACK_POWER_FORMULA_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_TORPEDO_ATTACK_POWER_FORMULA_HPP_INCLUDED

// std
#include <algorithm>
#include <cstdint>
#include <format>
#include <optional>

// kcv
#include "core/attributes/ship.hpp"
#include "core/battlelog/battlelog.hpp"
#include "core/context_data.hpp"
#include "core/damage_formula/functions/composed_function.hpp"
#include "core/damage_formula/functions/modifier_functions.hpp"
#include "core/damage_formula/map_bonus.hpp"
#include "core/entity/ship.hpp"
#include "extensions/interval.hpp"
#include "models/kcsapi/types/enum/engagement.hpp"
#include "models/kcsapi/types/enum/formation.hpp"

namespace kcv {

/// @brief 損傷状態.
/// @todo 定義を移動する.
enum class damage_state {
    /// @brief 小破未満.
    healthy,

    /// @brief 小破.
    light,

    /// @brief 中破.
    medium,

    /// @brief 大破.
    heavy,

    /// @brief 轟沈.
    sunk,
};

/// @todo 定義を移動する.
inline auto get_damage_state(const kcv::ship& ship) -> damage_state {
    const double ratio = static_cast<double>(ship.hp()) / static_cast<double>(ship.maxhp());
    if (ratio > 0.75) {
        return damage_state::healthy;
    } else if (ratio > 0.5) {
        return damage_state::light;
    } else if (ratio > 0.25) {
        return damage_state::medium;
    } else if (ratio > 0) {
        return damage_state::heavy;
    } else {
        return damage_state::sunk;
    }
}

/// @brief 攻撃力式 - 雷撃.
class torpedo_attack_power_formula final {
   public:
    /// @brief 補正関数.
    using modifier_function_t = kcv::functions::composed_function<
        kcv::functions::liner,     // 第0種補正
        kcv::functions::liner,     // 交戦形態補正
        kcv::functions::liner,     // 攻撃側陣形補正
        kcv::functions::liner,     // 損傷状態補正
        kcv::functions::liner,     // 第14種補正
        kcv::functions::softcap,   // ソフトキャップ
                                   // 第5種補正
        kcv::functions::floor,     // 切り捨て
                                   // 第6種補正
                                   // 第7種補正
                                   // 切り捨て
                                   // 昼間特殊攻撃補正
                                   // 徹甲弾補正
                                   // 第11種補正
        kcv::functions::liner,     // 艦種補正
        kcv::functions::liner,     // 海域補正
        kcv::functions::liner,     // 期間限定海域
        kcv::functions::liner,     // 第8種補正
        kcv::functions::pt_imp,    // PT
        kcv::functions::liner,     // PT装備
                                   // PT装備補正は多層の乗算...
        kcv::functions::critical,  // 急所補正
        kcv::functions::floor      // 切り捨て
        >;

   private:
    struct memory final {};

   public:
    torpedo_attack_power_formula(const kcv::context_data& ctx, const kcv::battlelog& data)
        : memory_{}
        , base_value_{}  //
        , formula_{
              f0(ctx, data, this->memory_)                  //
              | engagement(ctx, data, this->memory_)        //
              | formation(ctx, data, this->memory_)         //
              | damage_state(ctx, data, this->memory_)      //
              | f14(ctx, data, this->memory_)               //
              | softcap(ctx, data, this->memory_)           //
              | floor(ctx, data, this->memory_)             //
              | stype(ctx, data, this->memory_)             //
              | map(ctx, data, this->memory_)               //
              | event(ctx, data, this->memory_)             //
              | f8(ctx, data, this->memory_)                //
              | pt_imp(ctx, data, this->memory_)            //
              | pt_imp_equipment(ctx, data, this->memory_)  //
              | critical(ctx, data, this->memory_)          //
              | floor_if_cl2(ctx, data, this->memory_)      //
          } {}

    auto base_value() const -> kcv::number;

    auto formula() const;

    auto evaluate() const -> std::optional<kcv::number> {
        return this->formula_(this->base_value_);
    }

   private:
    /// @brief 基本攻撃力.
    static auto basic_power() -> kcv::number;

    /// @brief 第0種補正.
    static auto f0(const kcv::context_data& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    /// @brief 交戦形態補正.
    static auto engagement(const kcv::context_data& ctx, const kcv::battlelog& data, memory& m)
        -> kcv::functions::liner {
        switch (data.engagement) {
            case kcv::kcsapi::engagement::green_t:
                return kcv::functions::liner{.a = 1.2};

            case kcv::kcsapi::engagement::parallel:
                return kcv::functions::liner{.a = 1.0};

            case kcv::kcsapi::engagement::head_on:
                return kcv::functions::liner{.a = 0.8};

            case kcv::kcsapi::engagement::red_t:
                return kcv::functions::liner{.a = 0.6};
        }
    }

    /// @brief 攻撃側陣形補正.
    static auto formation(const kcv::context_data& ctx, const kcv::battlelog& data, memory& m)
        -> kcv::functions::liner {
        switch (get_attacker_formation(data)) {
            case kcv::kcsapi::formation::line_ahead:
                return kcv::functions::liner{.a = 1.0};

            case kcv::kcsapi::formation::double_line:
                return kcv::functions::liner{.a = 0.8};

            case kcv::kcsapi::formation::diamond:
                return kcv::functions::liner{.a = 0.7};

            case kcv::kcsapi::formation::echelon:
                return kcv::functions::liner{.a = 0.6};

            case kcv::kcsapi::formation::line_abreast:
                return kcv::functions::liner{.a = 0.6};

            case kcv::kcsapi::formation::vanguard:
                return kcv::functions::liner{.a = 1.0};

            case kcv::kcsapi::formation::Cruising1:
                return kcv::functions::liner{.a = 0.7};

            case kcv::kcsapi::formation::Cruising2:
                return kcv::functions::liner{.a = 0.9};

            case kcv::kcsapi::formation::Cruising3:
                return kcv::functions::liner{.a = 0.6};

            case kcv::kcsapi::formation::Cruising4:
                return kcv::functions::liner{.a = 1.0};
        }
    }

    /// @brief 損傷状態補正.
    static auto damage_state(const kcv::context_data& ctx, const kcv::battlelog& data, memory& m)
        -> kcv::functions::liner {
        const auto& attacker    = get_attacker(data);
        const auto damage_state = get_damage_state(attacker);
        switch (damage_state) {
            case kcv::damage_state::healthy:
            case kcv::damage_state::light:
                return kcv::functions::liner{.a = 1.0};

            case kcv::damage_state::medium:
                return kcv::functions::liner{.a = 0.8};

            case kcv::damage_state::heavy:
            case kcv::damage_state::sunk:
                // 大破または轟沈のとき雷撃しないが, 刺し違え雷撃に対応するため例外送出しない.
                // 大破時の補正値は割合判定が先行するため逆算不可能なため`* 0.0`とはいえない.
                // しかし, 刺し違え雷撃を考慮して0.0とすると都合が良い.
                // 逆算時は0除算となるため注意.
                return kcv::functions::liner{.a = 0.0};
        }
    }

    /// @brief 第14種補正.
    static auto f14(const kcv::context_data& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    /// @brief ソフトキャップ.
    static auto softcap(const kcv::context_data& ctx, const kcv::battlelog& data, memory& m)
        -> kcv::functions::softcap {
        return kcv::functions::softcap{.cap = 180};
    }

    /// @brief 切り捨て.
    /// それぞれ別の切り捨てを使う.
    static auto floor(const kcv::context_data& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::floor {
        return kcv::functions::floor{};
    }

    /// @brief 艦種補正.
    static auto stype(const kcv::context_data& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    /// @brief 海域補正.
    static auto map(const kcv::context_data& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
        // #7-4, #7-5のみ対応.
        if (not(data.world == 7 and data.map == 4) and not(data.world == 7 and data.map == 5)) {
            return kcv::functions::liner{};
        }

        auto total = kcv::map_bonus_result{};

        const auto& attacker  = kcv::get_attacker(data);
        const auto& map_bonus = ctx.map_bonuse(data.world, data.map);
        const auto& cells     = ctx.destination().worlds.at(std::format("World {}-{}", data.world, data.map));
        const auto& node      = std::get<1>(cells.at(data.cell));
        for (const auto& [nodes, nodes_exclude, bonuses] : map_bonus.list_bonus) {
            if (nodes.has_value() and not std::ranges::contains(*nodes, node)) {
                continue;
            }

            total *= kcv::total_map_bonus(attacker, bonuses);
        }

        return kcv::functions::liner{.a = total.dmg};
    }

    /// @brief 期間限定海域補正.
    static auto event(const kcv::context_data& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    /// @brief 第8種補正.
    static auto f8(const kcv::context_data& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    /// @brief PT補正.
    static auto pt_imp(const kcv::context_data& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::pt_imp {
        return kcv::functions::pt_imp{.is_enabled = kcv::is_pt_imp(get_defender(data).mst())};
    }

    /// @brief PT装備補正
    static auto pt_imp_equipment(const kcv::context_data& ctx, const kcv::battlelog& data, memory& m)
        -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    /// @brief 急所補正.
    static auto critical(const kcv::context_data& ctx, const kcv::battlelog& data, memory& m)
        -> kcv::functions::critical {
        const bool is_cl2 = std::get<std::int32_t>(data.clitical) == 2;
        return kcv::functions::critical{.is_enabled = is_cl2};
    }

    /// @brief 急所補正切り捨て.
    static auto floor_if_cl2(const kcv::context_data& ctx, const kcv::battlelog& data, memory& m)
        -> kcv::functions::floor {
        const bool is_cl2 = std::get<std::int32_t>(data.clitical) == 2;
        return kcv::functions::floor{.is_enabled = is_cl2};
    }

   private:
    memory memory_;
    kcv::number base_value_;
    modifier_function_t formula_;
};

}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_TORPEDO_ATTACK_POWER_FORMULA_HPP_INCLUDED
