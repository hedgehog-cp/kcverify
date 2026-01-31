#ifndef KCV_DOMAIN_VERIFICATION_BATTLELOG_BATTLELOG_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_BATTLELOG_BATTLELOG_HPP_INCLUDED

// std
#include <cstddef>
#include <cstdint>
#include <optional>
#include <tuple>
#include <variant>
#include <vector>

// kcv
#include "kcv/domain/verification/entity/fleet_data.hpp"
#include "kcv/external/kcsapi/types/enum/air_hit_type.hpp"
#include "kcv/external/kcsapi/types/enum/day_attack_kind.hpp"
#include "kcv/external/kcsapi/types/enum/engagement.hpp"
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"
#include "kcv/external/kcsapi/types/enum/fleet_flag.hpp"
#include "kcv/external/kcsapi/types/enum/formation.hpp"
#include "kcv/external/kcsapi/types/enum/night_attack_kind.hpp"

namespace kcv {

enum class phase {
    /// @brief 基地航空隊噴式強襲.

    /// @brief 噴式強襲.

    /// @brief 基地航空隊航空戦.

    /// @brief 開幕夜戦.
    sp_midnight,

    /// @brief 機動部隊航空友軍.

    /// @brief 航空戦.

    /// @brief 支援艦隊攻撃.

    /// @brief 対潜先制爆雷攻撃.
    opening_taisen,

    /// @brief 開幕雷撃.
    opening_atack,

    /// @brief 砲撃戦.
    hougeki,

    /// @brief 雷撃戦.
    raigeki,

    /// @brief 夜戦友軍艦隊攻撃.
    friendly,

    /// @brief 夜戦.
    midnight,
};

/// @brief ダメージごとの戦闘ログ.
/// @todo 砲撃戦, 雷撃戦, 夜戦, etc...に分けて, using battlelog = std::variant< ... >する.
/// @todo メンバの並び順を検討する.
/// @todo attacker, defenderクラスを検討する.
struct battlelog final {
    /// @brief 大域の海域ID. #5-3-Pに対する5.
    std::int32_t world;

    /// @brief 海域ID. #5-3-Pに対する3.
    std::int32_t map;

    /// @brief セルID. #5-3-PのPに対する16.
    std::int32_t cell;

    /// @brief 装甲破砕フラグ.
    std::optional<std::int32_t> x_al01;

    /// @brief 阻塞気球マスフラグ.
    std::int32_t balloon_cell;

    /// @brief 環礁マスフラグ.
    std::optional<std::int32_t> atoll_cell;

    /// @brief 自軍.
    kcv::fleet_data girls_fleet_data;

    /// @brief 敵軍.
    /// XXX: 演習を考慮すると, 敵軍は必ずしも深海棲艦ではないためabyssalの名付けは不適となる.
    kcv::fleet_data abyssal_fleet_data;

    /// @brief 自陣形.
    kcv::kcsapi::formation girls_formation;

    /// @brief 敵陣形.
    kcv::kcsapi::formation abyssal_formation;

    /// @brief 交戦形態.
    kcv::kcsapi::engagement engagement;

    /// @brief 砲撃戦 | 雷撃戦 | 夜戦.
    kcv::phase phase;

    /// @brief 触接機ID. [2]. [0]=自軍, [1]=敵軍. 触接しなければ-1.
    std::tuple<kcv::kcsapi::equipment_id, kcv::kcsapi::equipment_id> touch_plane;

    /// @brief 攻撃艦隊.
    kcv::kcsapi::fleet_flag attacker_side;

    /// @brief 攻撃艦のindex.
    std::size_t attacker_fleet;

    /// @brief 攻撃艦のindex.
    std::size_t attacker_ship;

    /// @brief 防御艦のindex.
    std::size_t defender_fleet;

    /// @brief 防御艦のindex.
    std::size_t defender_ship;

    /// @brief 攻撃種別.
    std::variant<std::monostate, kcv::kcsapi::day_attack_kind, kcv::kcsapi::night_attack_kind> attack_kind;

    /// @brief 表示装備.
    std::vector<kcv::kcsapi::equipment_id> display_equipments;

    /// @brief 砲撃回数.
    std::size_t attack_order;

    /// @brief cLiticalフラグ. 0=miss, 1=命中, 2=cLitical.
    std::variant<std::int32_t, kcv::kcsapi::air_hit_type> clitical;

    /// @brief かばい.
    bool is_protected;

    /// @brief ダメージ.
    std::int32_t damage;
};

/// @brief battlelogを複数保持するコンテナ型.
/// 再配置コストが大きいと推測できるため, コンテナ型の詳細はstd::vectorに限らずその他の型も考慮する.
using battlelogs_t = std::vector<battlelog>;

}  // namespace kcv

#endif  // KCV_DOMAIN_VERIFICATION_BATTLELOG_BATTLELOG_HPP_INCLUDED
