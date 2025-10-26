#ifndef KCVERIFY_CORE_ENTITY_SHIP_HPP_INCLUDED
#define KCVERIFY_CORE_ENTITY_SHIP_HPP_INCLUDED

// std
#include <vector>

// kcv
#include "core/entity/slot.hpp"
#include "extensions/ranges.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/types/api_kyouka.hpp"
#include "models/kcsapi/types/enum/nationality.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"
#include "models/kcsapi/types/enum/sp_effect_item.hpp"

namespace kcv {

/// @brief 艦船.
class ship final {
   public:
    ship(
        const kcv::kcsapi::api_mst_ship_value_t& mst,
        kcv::kcsapi::ship_id base_id,
        kcv::kcsapi::nationality nationality,
        std::vector<kcv::slot> eqslots,
        std::optional<kcv::slot> exslot,
        std::int32_t level,
        std::int32_t hp
    )
        : mst_{mst}
        , base_id_{base_id}
        , nationality_{nationality}
        , eqslots_{eqslots}
        , exslot_{exslot}
        , slots_{kcv::ranges::views::concat(this->eqslots_, this->exslot_)}
        , level_{level}
        , hp_{hp} {}

    auto mst() const noexcept -> const kcv::kcsapi::api_mst_ship_value_t& {
        return this->mst_;
    }

    auto base_id() const noexcept -> kcv::kcsapi::ship_id {
        return this->base_id_;
    }

    auto nationality() const noexcept -> kcv::kcsapi::nationality {
        return this->nationality_;
    }

    auto eqslots() const noexcept -> const std::vector<kcv::slot>& {
        return this->eqslots_;
    }

    auto exslot() const noexcept -> const std::optional<kcv::slot>& {
        return this->exslot_;
    }

    auto slots() const noexcept -> const kcv::ranges::slots_view<kcv::slot>& {
        return this->slots_;
    }

    auto hp() const noexcept -> std::int32_t {
        return this->hp_;
    }

    void hp(std::int32_t v) noexcept {
        this->hp_ = v;
    }

    auto level() const noexcept -> std::int32_t {
        return this->level_;
    }

    void level(std::int32_t v) noexcept {
        this->level_ = v;
    }

   private:
    /// @brief 艦船マスタ.
    const kcv::kcsapi::api_mst_ship_value_t& mst_;

    /// @brief 未改造艦船ID
    kcv::kcsapi::ship_id base_id_;

    /// @brief 国籍
    kcv::kcsapi::nationality nationality_;

    /// @brief 装備スロット.
    std::vector<kcv::slot> eqslots_;

    /// @brief 増設スロット.
    std::optional<kcv::slot> exslot_;

    /// @brief 装備スロット.
    kcv::ranges::slots_view<kcv::slot> slots_;

    /// @brief レベル.
    std::int32_t level_;

    // /// @brief 疲労度.
    // std::int32_t condition_;

    // /// @brief 搭載燃料.
    // std::int32_t fuel_;

    // /// @brief 搭載弾薬量.
    // std::int32_t ammo_;

    // /// @brief 搭載数.
    // std::vector<std::int32_t> aircraft_;

    // /// @brief 近代化改修. 0=火力, 1=雷装, 2=対空, 3=装甲, 4=運, 5=耐久, 6=対潜.
    // kcv::kcsapi::api_kyouka kyouka_;

    // /// @brief 特注アイテム.
    // std::optional<std::vector<kcv::kcsapi::sp_effect_item>> special_effect_items;

    // /// @brief 耐久.
    std::int32_t hp_;

    // /// @brief 火力.
    // std::int32_t firepower_;

    // /// @brief 雷装.
    // std::int32_t torpedo_;

    // /// @brief 対空.
    // std::int32_t aa_;

    // /// @brief 装甲.
    // std::int32_t armor_;

    // /// @brief 回避.
    // std::int32_t evasion_;

    // /// @brief 射程.
    // std::int32_t range_;

    // /// @brief 速度.
    // std::int32_t speed_;

    // /// @brief 対潜.
    // std::int32_t asw_;

    // /// @brief 索敵.
    // std::int32_t search_;

    // /// @brief 運.
    // std::int32_t luck_;
};

}  // namespace kcv

#endif  // KCVERIFY_CORE_ENTITY_SHIP_HPP_INCLUDED
