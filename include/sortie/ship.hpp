#ifndef KCVERIFY_SORTIE_SHIP_HPP_INCLUDED
#define KCVERIFY_SORTIE_SHIP_HPP_INCLUDED

// std
#include <array>
#include <optional>
#include <ranges>
#include <utility>
#include <vector>

// alt std
#include "optional.hpp"
#include "ranges.hpp"

// kcv
#include "common.hpp"
#include "eoen/database/sortie/sortie_ship.hpp"
#include "kcsapi/api_start2/api_mst_ship.hpp"
#include "kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcsapi/types/enum/nationality.hpp"
#include "kcsapi/types/enum/ship_id.hpp"
#include "kcsapi/types/enum/sp_effect_item.hpp"
#include "sortie/slot.hpp"

namespace kcv {
namespace sortie {

/// @brief 艦船.
class ship final {
   public:
    using eoen_type = kcv::eoen::database::sortie::sortie_ship;

    // clang-format off

    static constexpr auto from_eoen(
        const eoen_type& src,
        const kcv::kcsapi::api_mst_ship& api_mst_ship,
        const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
    ) -> ship {
        const auto& mst = kcv::binary_search_or_exit(api_mst_ship, src.id);
        const auto original_id = kcv::original_id_or_exit(mst, api_mst_ship);
        return ship{
            mst,
            src.drop_id,
            src.level,
            src.condition,
            src.kyouka,
            src.fuel,
            src.ammo,
            src.hp,
            src.armor,
            src.evasion,
            src.aircraft,
            src.range,
            src.speed,
            src.firepower,
            src.torpedo,
            src.aa,
            src.asw,
            src.search,
            src.luck,
            src.equipment_slots
                | std::ranges::views::transform([&](const auto& e) {
                    return kcv::sortie::slot::from_eoen(e, api_mst_slotitem);
                    })
                | std::ranges::to<std::vector>(),
            src.expansion_slot.transform([&](const auto& e) {
                return kcv::sortie::slot::from_eoen(e, api_mst_slotitem);
            }),
            src.special_effect_items,
            original_id,
        };
    }

    // clang-format on

    // clang-format off

     constexpr ship(
        const kcv::kcsapi::api_mst_ship_value_t& mst,
        std::optional<std::int32_t> drop_id,
        std::int32_t level,
        std::int32_t condition,
        std::array<std::int32_t, 7> kyouka,
        std::int32_t fuel,
        std::int32_t ammo,
        std::int32_t hp,
        std::optional<std::int32_t> armor,
        std::optional<std::int32_t> evasion,
        std::optional<std::vector<std::int32_t>> aircraft,
        std::int32_t range,
        std::int32_t speed,
        std::optional<std::int32_t> firepower,
        std::optional<std::int32_t> torpedo,
        std::optional<std::int32_t> aa,
        std::optional<std::int32_t> asw,
        std::optional<std::int32_t> search,
        std::optional<std::int32_t> luck,
        std::vector<kcv::sortie::slot> eqslots,
        std::optional<kcv::sortie::slot> exslot,
        std::optional<std::vector<kcv::kcsapi::sp_effect_item>> special_effect_items,
        kcv::kcsapi::ship_id original_id
    ) noexcept
        : mst_{mst}
        , drop_id_{std::move(drop_id)}
        , level_{std::move(level)}
        , condition_{std::move(condition)}
        , kyouka_{std::move(kyouka)}
        , fuel_{std::move(fuel)}
        , ammo_{std::move(ammo)}
        , hp_{std::move(hp)}
        , armor_{std::move(armor)}
        , evasion_{std::move(evasion)}
        , aircraft_{std::move(aircraft)}
        , range_{std::move(range)}
        , speed_{std::move(speed)}
        , firepower_{std::move(firepower)}
        , torpedo_{std::move(torpedo)}
        , aa_{std::move(aa)}
        , asw_{std::move(asw)}
        , search_{std::move(search)}
        , luck_{std::move(luck)}
        , eqslots_{std::move(eqslots)}
        , exslot_{std::move(exslot)}
        , special_effect_items_{std::move(special_effect_items)} 
        , original_id_{std::move(original_id)}
        , nationality_{kcv::kcsapi::to_nationality(mst.api_sort_id)}{}

    // clang-format on

    constexpr auto mst(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.mst_);
    }

    constexpr auto drop_id(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.drop_id_);
    }

    constexpr auto level(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.level_);
    }

    constexpr auto condition(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.condition_);
    }

    constexpr auto kyouka(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.kyouka_);
    }

    constexpr auto fuel(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.fuel_);
    }

    constexpr auto ammo(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.ammo_);
    }

    constexpr auto hp(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.hp_);
    }

    constexpr auto armor(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.armor_);
    }

    constexpr auto evasion(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.evasion_);
    }

    constexpr auto aircraft(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.aircraft_);
    }

    constexpr auto range(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.range_);
    }

    constexpr auto speed(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.speed_);
    }

    constexpr auto firepower(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.firepower_);
    }

    constexpr auto torpedo(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.torpedo_);
    }

    constexpr auto aa(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.aa_);
    }

    constexpr auto asw(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.asw_);
    }

    constexpr auto search(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.search_);
    }

    constexpr auto luck(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.luck_);
    }

    constexpr auto eqslots(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.eqslots_);
    }

    constexpr auto exslot(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.exslot_);
    }

    constexpr auto special_effect_items(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.special_effect_items_);
    }

    constexpr auto original_id(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.original_id_);
    }

    constexpr auto nationality(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.nationality_);
    }

    /// @brief 装備スロットと補強増設スロット.
    constexpr auto slots() const noexcept -> kcv::ranges::range_of<kcv::sortie::slot> auto {
        return kcv::ranges::views::concat(this->eqslots_, this->exslot_);
    }

   private:
    /// @brief 艦船マスタ.
    const kcv::kcsapi::api_mst_ship_value_t& mst_;

    /// @brief 着任順の固有ID.
    std::optional<std::int32_t> drop_id_;

    /// @brief レベル.
    std::int32_t level_;

    /// @brief 疲労度.
    std::int32_t condition_;

    /// @brief 近代化改修. 0=火力, 1=雷装, 2=対空, 3=装甲, 4=運, 5=耐久, 6=対潜.
    std::array<std::int32_t, 7> kyouka_;

    /// @brief 搭載燃料.
    std::int32_t fuel_;

    /// @brief 搭載弾薬量.
    std::int32_t ammo_;

    /// @brief 耐久.
    std::int32_t hp_;

    /// @brief 装甲.
    std::optional<std::int32_t> armor_;

    /// @brief 回避.
    std::optional<std::int32_t> evasion_;

    /// @brief 搭載数.
    std::optional<std::vector<std::int32_t>> aircraft_;

    /// @brief 射程.
    std::int32_t range_;

    /// @brief 速度.
    std::int32_t speed_;

    /// @brief 火力.
    std::optional<std::int32_t> firepower_;

    /// @brief 雷装.
    std::optional<std::int32_t> torpedo_;

    /// @brief 対空.
    std::optional<std::int32_t> aa_;

    /// @brief 対潜.
    std::optional<std::int32_t> asw_;

    /// @brief 索敵.
    std::optional<std::int32_t> search_;

    /// @brief 運.
    std::optional<std::int32_t> luck_;

    /// @brief 装備スロット. 補強増設スロットを含まない.
    std::vector<kcv::sortie::slot> eqslots_;

    /// @brief 補強増設スロット.
    kcv::optional<kcv::sortie::slot> exslot_;

    /// @brief 特注アイテム.
    std::optional<std::vector<kcv::kcsapi::sp_effect_item>> special_effect_items_;

    /// @brief 未改造艦船ID
    kcv::kcsapi::ship_id original_id_;

    /// @brief 国籍
    kcv::kcsapi::nationality nationality_;
};

}  // namespace sortie
}  // namespace kcv

#endif  // KCVERIFY_SORTIE_SHIP_HPP_INCLUDED
