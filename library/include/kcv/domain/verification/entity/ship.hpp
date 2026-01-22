#ifndef KCV_DOMAIN_VERIFICATION_ENTITY_SHIP_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_ENTITY_SHIP_HPP_INCLUDED

// std
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <vector>

// kcv
#include "kcv/domain/verification/entity/slot.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_ship.hpp"
#include "kcv/external/kcsapi/types/api_kyouka.hpp"
#include "kcv/external/kcsapi/types/api_type.hpp"
#include "kcv/external/kcsapi/types/enum/category.hpp"
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"
#include "kcv/external/kcsapi/types/enum/icon.hpp"
#include "kcv/external/kcsapi/types/enum/nationality.hpp"
#include "kcv/external/kcsapi/types/enum/ship_id.hpp"
#include "kcv/external/kcsapi/types/enum/sp_effect_item.hpp"
#include "kcv/std_ext/ranges.hpp"

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
        std::int32_t condition,
        std::int32_t ammo,
        const kcv::kcsapi::api_kyouka& kyouka,
        std::int32_t maxhp,
        std::int32_t hp,
        std::int32_t torpedo,
        std::int32_t armor,
        std::int32_t speed
    )
        : mst_{mst}
        , base_id_{base_id}
        , nationality_{nationality}
        , eqslots_{eqslots}
        , exslot_{exslot}
        , level_{level}
        , condition_{condition}
        , ammo_{ammo}
        , kyouka_{kyouka}
        , maxhp_{maxhp}
        , hp_{hp}
        , torpedo_{torpedo}
        , armor_{armor}
        , speed_{speed} {}

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

    auto slots() noexcept -> kcv::ranges::slots_view<kcv::slot> {
        return kcv::ranges::views::concat(this->eqslots_, this->exslot_);
    }

    auto slots() const noexcept -> kcv::ranges::slots_view<const kcv::slot> {
        return kcv::ranges::views::concat(this->eqslots_, this->exslot_);
    }

    auto level() const noexcept -> std::int32_t {
        return this->level_;
    }

    void level(std::int32_t level) noexcept {
        this->level_ = level;
    }

    auto condition() const noexcept -> std::int32_t {
        return this->condition_;
    }

    auto ammo() const noexcept -> std::int32_t {
        return this->ammo_;
    }

    auto maxhp() const noexcept -> std::int32_t {
        return this->maxhp_;
    }

    auto hp() const noexcept -> std::int32_t {
        return this->hp_;
    }

    void hp(std::int32_t hp) noexcept {
        this->hp_ = hp;
    }

    auto torpedo() const noexcept -> std::int32_t {
        return this->torpedo_;
    }

    auto armor() const noexcept -> std::int32_t {
        return this->armor_;
    }

    auto speed() const noexcept -> std::int32_t {
        return this->speed_;
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

    /// @brief レベル.
    std::int32_t level_;

    /// @brief 疲労度.
    std::int32_t condition_;

    // /// @brief 搭載燃料.
    // std::int32_t fuel_;

    // /// @brief 搭載弾薬量.
    std::int32_t ammo_;

    // /// @brief 搭載数.
    // std::vector<std::int32_t> aircraft_;

    /// @brief 近代化改修. 0=火力, 1=雷装, 2=対空, 3=装甲, 4=運, 5=耐久, 6=対潜.
    kcv::kcsapi::api_kyouka kyouka_;

    // /// @brief 特注アイテム.
    // std::optional<std::vector<kcv::kcsapi::sp_effect_item>> special_effect_items;

    /// @brief 最大耐久.
    std::int32_t maxhp_;

    /// @brief 耐久.
    std::int32_t hp_;

    // /// @brief 火力.
    // std::int32_t firepower_;

    /// @brief 雷装.
    std::int32_t torpedo_;

    // /// @brief 対空.
    // std::int32_t aa_;

    /// @brief 装甲.
    std::int32_t armor_;

    // /// @brief 回避.
    // std::int32_t evasion_;

    // /// @brief 射程.
    // std::int32_t range_;

    /// @brief 速力.
    std::int32_t speed_;

    // /// @brief 対潜.
    // std::int32_t asw_;

    // /// @brief 索敵.
    // std::int32_t search_;

    // /// @brief 運.
    // std::int32_t luck_;
};

/// @brief 条件を満たす装備を搭載しているかを検証する. CPO.
struct has_equipment_fn final {
    /// @brief 条件を満たす装備を搭載しているかを検証する.
    /// @param ship 艦船.
    /// @param pred 装備マスタを引数にとる単項述語関数.
    static bool operator()(
        const kcv::ship& ship,
        const std::predicate<const kcv::kcsapi::api_mst_slotitem_value_t&> auto& pred
    ) noexcept {
        for (const auto& slot : ship.slots()) {
            if (const auto& e = slot.equipment(); e.has_value()) {
                if (std::invoke(pred, e->mst())) {
                    return true;
                }
            }
        }

        return false;
    }

    /// @brief 条件を満たす装備を搭載しているかを検証する.
    /// @param ship 艦船.
    /// @param category 装備カテゴリ.
    static bool operator()(const kcv::ship& ship, kcv::kcsapi::category category) noexcept {
        for (const auto& slot : ship.slots()) {
            if (const auto& e = slot.equipment(); e.has_value()) {
                if (std::get<kcv::kcsapi::idx_type::category>(e->mst().api_type) == category) {
                    return true;
                }
            }
        }

        return false;
    }

    /// @brief 条件を満たす装備を搭載しているかを検証する.
    /// @param ship 艦船.
    /// @param category 装備カテゴリ.
    [[deprecated]]
    static bool operator()(const kcv::ship& ship, std::initializer_list<kcv::kcsapi::category> categories) noexcept {
        for (const auto& slot : ship.slots()) {
            if (const auto& e = slot.equipment(); e.has_value()) {
                if (std::ranges::contains(categories, std::get<kcv::kcsapi::idx_type::category>(e->mst().api_type))) {
                    return true;
                }
            }
        }

        return false;
    }

    /// @brief 条件を満たす装備を搭載しているかを検証する.
    /// @param ship 艦船.
    /// @param category 装備アイコン.
    static bool operator()(const kcv::ship& ship, kcv::kcsapi::icon icon) noexcept {
        for (const auto& slot : ship.slots()) {
            if (const auto& e = slot.equipment(); e.has_value()) {
                if (std::get<kcv::kcsapi::idx_type::icon>(e->mst().api_type) == icon) {
                    return true;
                }
            }
        }

        return false;
    }
};

/// @brief 条件を満たす装備を搭載しているかを検証する.
inline constexpr auto has_equipment = has_equipment_fn{};

/// @brief 条件を満たす装備の搭載数を数え上げる. CPO.
struct count_equipment_fn final {
    /// @brief 条件を満たす装備の搭載数を数え上げる.
    /// @param ship 艦船.
    /// @param pred 装備マスタを引数にとる単項述語関数.
    static int operator()(
        const kcv::ship& ship,
        const std::predicate<const kcv::kcsapi::api_mst_slotitem_value_t&> auto& pred
    ) noexcept {
        int count = 0;
        for (const auto& slot : ship.slots()) {
            if (const auto& e = slot.equipment(); e.has_value()) {
                if (std::invoke(pred, e->mst())) {
                    count++;
                }
            }
        }

        return count;
    }

    /// @brief 条件を満たす装備の搭載数を数え上げる.
    /// @param ship 艦船.
    /// @param category 装備カテゴリ.
    static int operator()(const kcv::ship& ship, kcv::kcsapi::category category) noexcept {
        int count = 0;
        for (const auto& slot : ship.slots()) {
            if (const auto& e = slot.equipment(); e.has_value()) {
                if (std::get<kcv::kcsapi::idx_type::category>(e->mst().api_type) == category) {
                    count++;
                }
            }
        }

        return count;
    }

    /// @brief 条件を満たす装備の搭載数を数え上げる.
    /// @param ship 艦船.
    /// @param id 装備ID.
    static int operator()(const kcv::ship& ship, kcv::kcsapi::equipment_id id) noexcept {
        int count = 0;
        for (const auto& slot : ship.slots()) {
            if (const auto& e = slot.equipment(); e.has_value()) {
                if (e->mst().api_id == id) {
                    count++;
                }
            }
        }

        return count;
    }
};

/// @brief 条件を満たす装備の搭載数を数え上げる.
inline constexpr auto count_equipment = count_equipment_fn{};

}  // namespace kcv

#endif  // KCV_DOMAIN_VERIFICATION_ENTITY_SHIP_HPP_INCLUDED
