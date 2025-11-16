#ifndef KCVERIFY_CORE_JSON_GLZ_META_KC3KAI_KANCOLLE_REPLAY_JS_DATA_BONUS_BONUS_HPP_INCLUDED
#define KCVERIFY_CORE_JSON_GLZ_META_KC3KAI_KANCOLLE_REPLAY_JS_DATA_BONUS_BONUS_HPP_INCLUDED

// glz
#include <glaze/json.hpp>

// kcv
#include "models/kc3kai/bonus/bonus.hpp"

template <>
struct glz::meta<kcv::kc3kai::bonus_bonus_t> final {
    using T = kcv::kc3kai::bonus_bonus_t;

   public:
    static constexpr auto value = glz::object(
        // clang-format off

        "dmg",                &T::dmg,
        "acc",                &T::acc,
        "eva",                &T::eva,
        "shipBase",           &T::ship_base,
        "shipType",           &T::ship_type,
        "shipClass",          &T::ship_class,
        "shipId",             &T::ship_id,
        "isPlane",            &T::is_plane,
        "notAirOnly",         &T::not_air_only,
        "basewide",           &T::basewide,
        "requireEquipId",     &T::require_equip_id,
        "requireEquipType",   &T::require_equip_type,
        "perEquip",           &T::per_equip,
        "requireEquipIdNumX", &T::require_equip_id_num_x,
        "requireEquipIdNum",  &T::require_equip_id_num,
        "requireEquipLevel",  &T::require_equip_level,
        "requireEquipIdNot",  &T::require_equip_id_not,
        "unconfirmed",        &T::unconfirmed

        // clang-format on
    );
};

template <>
struct glz::meta<kcv::kc3kai::bonus_bonus_group_t> final {
    using T = kcv::kc3kai::bonus_bonus_group_t;

   public:
    static constexpr auto value = glz::object(
        // clang-format off

        "nodes",       &T::nodes,
        "nodesExclude",&T::nodes_exclude,
        "bonuses",     &T::bonuses

        // clang-format on
    );
};

template <>
struct glz::meta<kcv::kc3kai::bonus_debuff_t> final {
    using T = kcv::kc3kai::bonus_debuff_t;

   public:
    static constexpr auto value = glz::object(
        // clang-format off

        "shipId", &T::ship_id,
        "amount",  &T::amount

        // clang-format on
    );
};

template <>
struct glz::meta<kcv::kc3kai::bonus_debuff_group_t> final {
    using T = kcv::kc3kai::bonus_debuff_group_t;

   public:
    static constexpr auto value = glz::object(
        // clang-format off

        "nodes",   &T::nodes,
        "debuffs", &T::debuffs

        // clang-format on
    );
};

template <>
struct glz::meta<kcv::kc3kai::bonus_map_t> final {
    using T = kcv::kc3kai::bonus_map_t;

   public:
    static constexpr auto value = glz::object(
        // clang-format off

        "world",          &T::world,
        "mapnum",         &T::mapnum,
        "date",           &T::date,
        "note",           &T::note,
        "listBonus",      &T::list_bonus,
        "listBonusLBAS",  &T::list_bonus_lbas,
        "listDebuff",     &T::list_debuff

        // clang-format on
    );
};

#endif  // KCVERIFY_CORE_JSON_GLZ_META_KC3KAI_KANCOLLE_REPLAY_JS_DATA_BONUS_BONUS_HPP_INCLUDED
