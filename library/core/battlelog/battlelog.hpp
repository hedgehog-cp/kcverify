#ifndef KCVERIFY_CORE_BATTLELOG_BATTLELOG_HPP_INCLUDED
#define KCVERIFY_CORE_BATTLELOG_BATTLELOG_HPP_INCLUDED

// std
#include <cstddef>
#include <cstdint>
#include <tuple>
#include <variant>
#include <vector>

// kcv
#include "core/entity/fleet_data.hpp"
#include "models/kcsapi/types/enum/air_hit_type.hpp"
#include "models/kcsapi/types/enum/day_attack_kind.hpp"
#include "models/kcsapi/types/enum/engagement.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"
#include "models/kcsapi/types/enum/fleet_flag.hpp"
#include "models/kcsapi/types/enum/formation.hpp"
#include "models/kcsapi/types/enum/night_attack_kind.hpp"

namespace kcv {

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

    /// @brief cLiticalフラグ. 0=miss, 1=命中, 2=cLitical.
    std::variant<std::int32_t, kcv::kcsapi::air_hit_type> clitical;

    /// @brief かばい.
    bool is_protected;

    /// @brief ダメージ.
    std::int32_t damage;
};

/// @brief 攻撃艦を取得する.
/// @todo 友軍艦隊での取得を検討する.
inline auto get_attacker(const kcv::battlelog& data) -> const kcv::ship& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.girls_fleet_data.fleets().at(data.attacker_fleet).value().ships().at(data.attacker_ship);

        case kcv::kcsapi::fleet_flag::enemy:
            return data.abyssal_fleet_data.fleets().at(data.attacker_fleet).value().ships().at(data.attacker_ship);
    }
}

/// @brief 防御艦を取得する.
/// @todo 友軍艦隊での取得を検討する.
inline auto get_defender(const kcv::battlelog& data) -> const kcv::ship& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.abyssal_fleet_data.fleets().at(data.defender_fleet).value().ships().at(data.defender_ship);

        case kcv::kcsapi::fleet_flag::enemy:
            return data.girls_fleet_data.fleets().at(data.defender_fleet).value().ships().at(data.defender_ship);
    }
}

/// @brief 攻撃側陣形を取得する.
inline auto get_attacker_formation(const kcv::battlelog& data) -> kcv::kcsapi::formation {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.girls_formation;

        case kcv::kcsapi::fleet_flag::enemy:
            return data.abyssal_formation;
    }
}

/// @brief 攻撃側艦隊データを取得する.
inline auto get_attacker_fleet_data(const kcv::battlelog& data) -> const kcv::fleet_data& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.girls_fleet_data;

        case kcv::kcsapi::fleet_flag::enemy:
            return data.abyssal_fleet_data;
    }
}

/// @brief 防御側艦隊データを取得する.
inline auto get_defender_fleet_data(const kcv::battlelog& data) -> const kcv::fleet_data& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.abyssal_fleet_data;

        case kcv::kcsapi::fleet_flag::enemy:
            return data.girls_fleet_data;
    }
}

/// @brief 攻撃側艦隊を取得する.
inline auto get_attacker_fleet(const kcv::battlelog& data) -> const kcv::fleet& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.abyssal_fleet_data.fleets().at(data.attacker_fleet).value();

        case kcv::kcsapi::fleet_flag::enemy:
            return data.girls_fleet_data.fleets().at(data.attacker_fleet).value();
    }
}

/// @brief 防御側艦隊を取得する.
inline auto get_defender_fleet(const kcv::battlelog& data) -> const kcv::fleet& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.girls_fleet_data.fleets().at(data.attacker_fleet).value();

        case kcv::kcsapi::fleet_flag::enemy:
            return data.abyssal_fleet_data.fleets().at(data.attacker_fleet).value();
    }
}

}  // namespace kcv

#endif  // KCVERIFY_CORE_BATTLELOG_BATTLELOG_HPP_INCLUDED
