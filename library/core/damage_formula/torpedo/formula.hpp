#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_TORPEDO_FORMULA_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_TORPEDO_FORMULA_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "core/attributes/ship.hpp"
#include "core/battlelog/battlelog.hpp"
#include "core/damage_formula/functions/function_composition.hpp"
#include "core/damage_formula/functions/modifier_functions.hpp"
#include "core/entity/fleet.hpp"
#include "core/entity/fleet_data.hpp"
#include "core/entity/ship.hpp"
#include "extensions/interval.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/enum/engagement.hpp"
#include "models/kcsapi/types/enum/fleet_flag.hpp"
#include "models/kcsapi/types/enum/formation.hpp"

namespace kcv {
namespace damage_formlulas {

// class fleet_data_view final {
//     const kcv::fleet_data& fleet_data_;

//    public:
//     fleet_data_view(const kcv::fleet_data& fleet_data) noexcept
//         : fleet_data_{fleet_data} {}

//     auto get() const noexcept -> const kcv::fleet_data& {
//         return this->fleet_data_;
//     }
// };

// class battlelog_view final {
//     const kcv::battlelog& battlelog_;

//    public:
//     battlelog_view(const kcv::battlelog& battlelog) noexcept
//         : battlelog_{battlelog} {}

//     auto get() const noexcept -> const kcv::battlelog& {
//         return this->battlelog_;
//     }

//     auto get_attacker() const noexcept -> const kcv::ship& {
//         switch (this->battlelog_.attacker_side) {
//             case kcv::kcsapi::fleet_flag::player:
//                 return this->battlelog_.girls_fleet_data.fleets()
//                     .at(this->battlelog_.attacker_fleet)
//                     .value()
//                     .ships()
//                     .at(this->battlelog_.attacker_ship);

//             case kcv::kcsapi::fleet_flag::enemy:
//                 return this->battlelog_.abyssal_fleet_data.fleets()
//                     .at(this->battlelog_.attacker_fleet)
//                     .value()
//                     .ships()
//                     .at(this->battlelog_.attacker_ship);
//         }
//     }

//     auto get_defender() noexcept -> const kcv::ship& {
//         switch (this->battlelog_.attacker_side) {
//             case kcv::kcsapi::fleet_flag::player:
//                 return this->battlelog_.abyssal_fleet_data.fleets()
//                     .at(this->battlelog_.defender_fleet)
//                     .value()
//                     .ships()
//                     .at(this->battlelog_.defender_ship);

//             case kcv::kcsapi::fleet_flag::enemy:
//                 return this->battlelog_.girls_fleet_data.fleets()
//                     .at(this->battlelog_.defender_fleet)
//                     .value()
//                     .ships()
//                     .at(this->battlelog_.defender_ship);
//         }
//     }

//     auto get_attacker_fleet_data() const noexcept -> fleet_data_view {
//         switch (this->battlelog_.attacker_side) {
//             case kcv::kcsapi::fleet_flag::player:
//                 return this->battlelog_.girls_fleet_data;

//             case kcv::kcsapi::fleet_flag::enemy:
//                 return this->battlelog_.abyssal_fleet_data;
//         }
//     }
// };

/// @brief 攻撃艦を取得する.
/// @todo 友軍艦隊での取得を検討する.
auto get_attacker(const kcv::battlelog& data) -> const kcv::ship& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.girls_fleet_data.fleets().at(data.attacker_fleet).value().ships().at(data.attacker_ship);

        case kcv::kcsapi::fleet_flag::enemy:
            return data.abyssal_fleet_data.fleets().at(data.attacker_fleet).value().ships().at(data.attacker_ship);
    }
}

/// @brief 防御艦を取得する.
/// @todo 友軍艦隊での取得を検討する.
auto get_defender(const kcv::battlelog& data) -> const kcv::ship& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.abyssal_fleet_data.fleets().at(data.defender_fleet).value().ships().at(data.defender_ship);

        case kcv::kcsapi::fleet_flag::enemy:
            return data.girls_fleet_data.fleets().at(data.defender_fleet).value().ships().at(data.defender_ship);
    }
}

/// @brief 損傷状態.
enum class damage_state {
    /// @brief 小破未満.
    normal,

    /// @brief 小破.
    shouha,

    /// @brief 中破.
    chuuha,

    /// @brief 大破.
    taiha,

    /// @brief 轟沈.
    sunk,
};

auto get_damage_state(const kcv::ship& ship) -> damage_state {
    const double ratio = static_cast<double>(ship.hp()) / static_cast<double>(ship.maxhp());
    if (ratio > 0.75) {
        return damage_state::normal;
    } else if (ratio > 0.5) {
        return damage_state::shouha;
    } else if (ratio > 0.25) {
        return damage_state::chuuha;
    } else if (ratio > 0) {
        return damage_state::taiha;
    } else {
        return damage_state::sunk;
    }
}

auto get_attacker_formation(const kcv::battlelog& data) -> kcv::kcsapi::formation {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.girls_formation;

        case kcv::kcsapi::fleet_flag::enemy:
            return data.abyssal_formation;
    }
}

auto get_attacker_fleet_data(const kcv::battlelog& data) -> const kcv::fleet_data& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.girls_fleet_data;

        case kcv::kcsapi::fleet_flag::enemy:
            return data.abyssal_fleet_data;
    }
}

auto get_defender_fleet_data(const kcv::battlelog& data) -> const kcv::fleet_data& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.abyssal_fleet_data;

        case kcv::kcsapi::fleet_flag::enemy:
            return data.girls_fleet_data;
    }
}

auto get_attacker_fleet(const kcv::battlelog& data) -> const kcv::fleet& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.abyssal_fleet_data.fleets().at(data.attacker_fleet).value();

        case kcv::kcsapi::fleet_flag::enemy:
            return data.girls_fleet_data.fleets().at(data.attacker_fleet).value();
    }
}

auto get_defender_fleet(const kcv::battlelog& data) -> const kcv::fleet& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.girls_fleet_data.fleets().at(data.attacker_fleet).value();

        case kcv::kcsapi::fleet_flag::enemy:
            return data.abyssal_fleet_data.fleets().at(data.attacker_fleet).value();
    }
}

// struct map_bonus_map final {
//     /// @brief 大域の海域ID. #5-3-Pに対する5.
//     std::int32_t world;

//     /// @brief 海域ID. #5-3-Pに対する3.
//     std::int32_t map;

//     /// @brief セルID. #5-3-PのPに対する16.
//     std::vector<std::int32_t> cells;
// };

// /// @brief 海域補正.
// struct map_bonus final {
//     /// @brief 艦種.
//     kcv::kcsapi::stype stype = {};

//     /// @brief よみ.
//     /// @todo 実行時コストが大きいため最適化する.
//     std::vector<std::string> yomi = {};

//     /// @brief 海域補正.
//     kcv::functions::liner bonus;
// };

// struct map_bonuses final {
//     map_bonus_map map;
//     std::vector<map_bonus> bonuses;
// };

// inline const auto map_bonuses_obj = std::to_array<map_bonuses>({
//     // #7-4-J,L
//     {
//         .map{.world = 7, .map = 4, .cells = {10, 18, 12, 20}},
//         .bonuses{
//             {.stype = kcv::kcsapi::stype::de, .bonus = {.a = 1.25}},
//             {.stype = kcv::kcsapi::stype::clt, .bonus = {.a = 1.15}},
//         },
//     },
//     // #7-4-P
//     {
//         .map{.world = 7, .map = 4, .cells = {16, 21, 22, 23}},
//         .bonuses{
//             {.stype = kcv::kcsapi::stype::de, .bonus = {.a = 1.33}},
//             {.stype = kcv::kcsapi::stype::clt, .bonus = {.a = 1.23}},
//         },
//     },
//     // #7-5-A,B,C,D,E,F,J
//     {
//         .map{.world = 7, .map = 5, .cells = {1, 2, 3, 4, 12, 5, 6, 13, 10}},
//         .bonuses{
//             {
//                 .yomi  = {"りゅうじょう", "みょうこう", "なち",     "あしがら", "はぐろ",       "じんつう",
//                           "なか",         "デロイテル", "まつかぜ", "あけぼの", "さざなみ",     "うしお",
//                           "いかずち",     "いなずま",   "むらさめ", "ゆうだち", "はるさめ",     "さみだれ",
//                           "やまかぜ",     "かわかぜ",   "あさぐも", "みねぐも", "はつかぜ",     "ゆきかぜ",
//                           "あまつかぜ",   "ときつかぜ", "ちとせ",   "みずほ",   "ヒューストン", "パース"},
//                 .bonus = {.a = 1.08},
//             },
//         },
//     },
// });

/// @brief 海域補正.
// auto total_map_bonuses() -> kcv::functions::liner;

struct context final {
    const kcv::kcsapi::api_mst_ship& api_mst_ship;
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem;
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses;

    // 既存補正のON/OFF
};

namespace torpedo {

/// @brief 攻撃力計算機.
class attack_power_calculator final {
   public:
    /// @brief 攻撃力式.
    // 阻塞気球どこ?
    using formula = kcv::functions::function_composition<
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
    attack_power_calculator(const kcv::battlelog& data, const context& ctx)
        : memory_{}
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

    auto evaluate() const -> std::optional<kcv::number> {
        return this->formula_(0);
    }

   private:
    /// @brief 基本攻撃力.
    static auto basic_power() -> kcv::number;

    /// @brief 第0種補正.
    static auto f0(const context& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    /// @brief 交戦形態補正.
    static auto engagement(const context& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
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
    static auto formation(const context& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
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
    static auto damage_state(const context& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
        const auto& attacker    = get_attacker(data);
        const auto damage_state = get_damage_state(attacker);
        switch (damage_state) {
            case kcv::damage_formlulas::damage_state::normal:
            case kcv::damage_formlulas::damage_state::shouha:
                return kcv::functions::liner{.a = 1.0};

            case kcv::damage_formlulas::damage_state::chuuha:
                return kcv::functions::liner{.a = 0.8};

            case kcv::damage_formlulas::damage_state::taiha:
            case kcv::damage_formlulas::damage_state::sunk:
                // 大破または轟沈のとき雷撃しないが, 刺し違え雷撃に対応するため例外送出しない.
                // 大破時の補正値は割合判定が先行するため逆算不可能なため`* 0.0`とはいえない.
                // しかし, 刺し違え雷撃を考慮して0.0とすると都合が良い.
                // 逆算時は0除算となるため注意.
                return kcv::functions::liner{.a = 0.0};
        }
    }

    /// @brief 第14種補正.
    static auto f14(const context& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    /// @brief ソフトキャップ.
    static auto softcap(const context& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::softcap {
        return kcv::functions::softcap{.cap = 180};
    }

    /// @brief 切り捨て.
    /// それぞれ別の切り捨てを使う.
    static auto floor(const context& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::floor {
        return kcv::functions::floor{};
    }

    /// @brief 艦種補正.
    static auto stype(const context& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    /// @brief 海域補正.
    static auto map(const context& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
        // return total_map_bonuses();
        return kcv::functions::liner{};
    }

    /// @brief 期間限定海域補正.
    static auto event(const context& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    /// @brief 第8種補正.
    static auto f8(const context& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    /// @brief PT補正.
    static auto pt_imp(const context& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::pt_imp {
        return kcv::functions::pt_imp{.is_enabled = kcv::is_pt_imp(get_defender(data).mst())};
    }

    /// @brief PT装備補正
    static auto pt_imp_equipment(const context& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::liner {
        return kcv::functions::liner{};
    }

    /// @brief 急所補正.
    static auto critical(const context& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::critical {
        const bool is_cl2 = std::get<std::int32_t>(data.clitical) == 2;
        return kcv::functions::critical{.is_enabled = is_cl2};
    }

    /// @brief 急所補正切り捨て.
    static auto floor_if_cl2(const context& ctx, const kcv::battlelog& data, memory& m) -> kcv::functions::floor {
        const bool is_cl2 = std::get<std::int32_t>(data.clitical) == 2;
        return kcv::functions::floor{.is_enabled = is_cl2};
    }

   private:
    memory memory_;
    formula formula_;
};

}  // namespace torpedo
}  // namespace damage_formlulas
}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_TORPEDO_FORMULA_HPP_INCLUDED
