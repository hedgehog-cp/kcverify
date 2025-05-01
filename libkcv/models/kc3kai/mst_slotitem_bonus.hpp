#ifndef KCVERIFY_MODELS_KC3KAI_MST_SLOTITEM_BONUS_HPP_INCLUDED
#define KCVERIFY_MODELS_KC3KAI_MST_SLOTITEM_BONUS_HPP_INCLUDED

// std
#include <compare>
#include <concepts>
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "models/kcsapi/types/enum/category.hpp"
#include "models/kcsapi/types/enum/ctype.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"
#include "models/kcsapi/types/enum/nationality.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"
#include "models/kcsapi/types/enum/stype.hpp"

namespace kcv {
namespace kc3kai {

/// @brief 装備ボーナスデータ.
/// @see KC3Kai: kancolle-replay/js/data/mst_slotitem_bonus.json
struct bonus_value final {
    /// @brief 火力.
    std::int32_t houg = 0;

    /// @brief 対空.
    std::int32_t tyku = 0;

    /// @brief 回避.
    std::int32_t kaih = 0;

    /// @brief 装甲.
    std::int32_t souk = 0;

    /// @brief 命中.
    std::int32_t houm = 0;

    /// @brief 対潜.
    std::int32_t tais = 0;

    /// @brief 雷撃.
    std::int32_t raig = 0;

    /// @brief 索敵.
    std::int32_t saku = 0;

    /// @brief 射程.
    std::int32_t leng = 0;

    /// @brief 爆装.
    std::int32_t baku = 0;

   private:
    using this_type = bonus_value;

    friend constexpr auto operator<=>(const this_type& lhs, const this_type& rhs) -> std::strong_ordering = default;

    friend constexpr auto operator+=(this_type& lhs, const this_type& rhs) -> this_type& {
        lhs.houg += rhs.houg;
        lhs.tyku += rhs.tyku;
        lhs.kaih += rhs.kaih;
        lhs.souk += rhs.souk;
        lhs.houm += rhs.houm;
        lhs.tais += rhs.tais;
        lhs.raig += rhs.raig;
        lhs.saku += rhs.saku;
        lhs.leng += rhs.leng;
        lhs.baku += rhs.baku;
        return lhs;
    }

    friend constexpr auto operator+(const this_type& lhs, const this_type& rhs) -> this_type {
        auto temp = lhs;
        return temp += rhs;
    }

    friend constexpr auto operator*(const this_type& lhs, std::integral auto rhs) -> this_type {
        return this_type{
            .houg = lhs.houg * rhs,
            .tyku = lhs.tyku * rhs,
            .kaih = lhs.kaih * rhs,
            .souk = lhs.souk * rhs,
            .houm = lhs.houm * rhs,
            .tais = lhs.tais * rhs,
            .raig = lhs.raig * rhs,
            .saku = lhs.saku * rhs,
            .leng = lhs.leng * rhs,
            .baku = lhs.baku * rhs,
        };
    }
};

/// @brief 装備ボーナスデータ.
/// @see KC3Kai: kancolle-replay/js/data/mst_slotitem_bonus.json
struct bonus_data final {
    /// @brief 水上電探. 1または未指定.
    std::optional<std::int32_t> requires_surface_radar;

    /// @brief 対空電探. 1または未指定.
    std::optional<std::int32_t> requires_anti_air_radar;

    /// @brief 命中電探. 1または未指定.
    std::optional<std::int32_t> requires_accuracy_radar;

    /// @brief 艦型.
    std::optional<std::vector<kcv::kcsapi::ctype>> ship_class;

    /// @brief 艦籍.
    std::optional<std::vector<kcv::kcsapi::nationality>> ship_country;

    /// @brief 艦船ID.
    std::optional<std::vector<kcv::kcsapi::ship_id>> ship_id;

    /// @brief 未改造ID.
    std::optional<std::vector<kcv::kcsapi::ship_id>> ship_base;

    /// @brief 艦種.
    std::optional<std::vector<kcv::kcsapi::stype>> ship_type;

    /// @brief 装備ID.
    std::optional<std::vector<kcv::kcsapi::equipment_id>> requires_id;

    /// @brief
    std::optional<std::int32_t> requires_id_num;

    /// @brief
    std::optional<std::int32_t> requires_id_level;

    /// @brief カテゴリID.
    std::optional<std::vector<kcv::kcsapi::category>> requires_type;

    /// @brief 存在しない.
    std::optional<std::int32_t> requires_type_num;

    /// @brief 改修値.
    std::optional<std::int32_t> level;

    /// @brief 搭載数.
    std::optional<std::int32_t> num;

    /// @brief ボーナス.
    kcv::kc3kai::bonus_value bonus;
};

/// @brief 装備ボーナスデータ.
/// @see KC3Kai: kancolle-replay/js/data/mst_slotitem_bonus.json
struct mst_slotitem_bonus final {
    /// @brief カテゴリID条件.
    std::optional<std::vector<kcv::kcsapi::category>> types;

    /// @brief 装備ID条件.
    std::optional<std::vector<kcv::kcsapi::equipment_id>> ids;

    /// @brief ボーナス.
    std::vector<kcv::kc3kai::bonus_data> bonuses;
};

}  // namespace kc3kai
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KC3KAI_MST_SLOTITEM_BONUS_HPP_INCLUDED
