#ifndef KCV_DOMAIN_VERIFICATION_BATTLELOG_BATTLELOG_ACCESSOR_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_BATTLELOG_BATTLELOG_ACCESSOR_HPP_INCLUDED

// kcv
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/entity/fleet.hpp"
#include "kcv/domain/verification/entity/fleet_data.hpp"
#include "kcv/external/kcsapi/types/enum/fleet_flag.hpp"
#include "kcv/external/kcsapi/types/enum/formation.hpp"
#include "kcv/std_ext/exception.hpp"
#include "kcv/std_ext/utility.hpp"

namespace kcv {

/// @brief 攻撃艦を取得する.
/// @todo 友軍艦隊での取得を検討する.
inline auto get_attacker(const kcv::battlelog& data) -> const kcv::ship& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.girls_fleet_data.fleets().at(data.attacker_fleet).value().ships().at(data.attacker_ship);

        case kcv::kcsapi::fleet_flag::enemy:
            return data.abyssal_fleet_data.fleets().at(data.attacker_fleet).value().ships().at(data.attacker_ship);
    }

    kcv::throw_unrachable(data.attacker_side);
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

    kcv::throw_unrachable(data.attacker_side);
}

/// @brief 攻撃側陣形を取得する.
inline auto get_attacker_formation(const kcv::battlelog& data) -> kcv::kcsapi::formation {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.girls_formation;

        case kcv::kcsapi::fleet_flag::enemy:
            return data.abyssal_formation;
    }

    kcv::throw_unrachable(data.attacker_side);
}

/// @brief 攻撃側陣形を取得する.
inline auto get_defender_formation(const kcv::battlelog& data) -> kcv::kcsapi::formation {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.abyssal_formation;

        case kcv::kcsapi::fleet_flag::enemy:
            return data.girls_formation;
    }

    kcv::throw_unrachable(data.attacker_side);
}

/// @brief 攻撃側艦隊データを取得する.
inline auto get_attacker_fleet_data(const kcv::battlelog& data) -> const kcv::fleet_data& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.girls_fleet_data;

        case kcv::kcsapi::fleet_flag::enemy:
            return data.abyssal_fleet_data;
    }

    kcv::throw_unrachable(data.attacker_side);
}

/// @brief 防御側艦隊データを取得する.
inline auto get_defender_fleet_data(const kcv::battlelog& data) -> const kcv::fleet_data& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.abyssal_fleet_data;

        case kcv::kcsapi::fleet_flag::enemy:
            return data.girls_fleet_data;
    }

    kcv::throw_unrachable(data.attacker_side);
}

/// @brief 攻撃側艦隊を取得する.
inline auto get_attacker_fleet(const kcv::battlelog& data) -> const kcv::fleet& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.girls_fleet_data.fleets().at(data.attacker_fleet).value();

        case kcv::kcsapi::fleet_flag::enemy:
            return data.abyssal_fleet_data.fleets().at(data.attacker_fleet).value();
    }

    kcv::throw_unrachable(data.attacker_side);
}

/// @brief 防御側艦隊を取得する.
inline auto get_defender_fleet(const kcv::battlelog& data) -> const kcv::fleet& {
    switch (data.attacker_side) {
        case kcv::kcsapi::fleet_flag::player:
            return data.girls_fleet_data.fleets().at(data.attacker_fleet).value();

        case kcv::kcsapi::fleet_flag::enemy:
            return data.abyssal_fleet_data.fleets().at(data.attacker_fleet).value();
    }

    kcv::throw_unrachable(data.attacker_side);
}

/// @brief 急所弾であるかを検証する.
inline bool is_critical(const kcv::battlelog& data) noexcept {
    return std::visit(
        kcv::overloaded{
            [](std::int32_t v) static -> bool { return v == 2; },
            [](kcv::kcsapi::air_hit_type v) static -> bool { return v == kcv::kcsapi::air_hit_type::cLitical; },
        },
        data.clitical
    );
}

}  // namespace kcv

#endif  // KCV_DOMAIN_VERIFICATION_BATTLELOG_BATTLELOG_ACCESSOR_HPP_INCLUDED
