#ifndef KCVERIFY_SORTIE_SHIP_HPP_INCLUDED
#define KCVERIFY_SORTIE_SHIP_HPP_INCLUDED

// std
#include <optional>
#include <ranges>
#include <vector>

// ranges
#include <range/v3/view/concat.hpp>

// kcv
#include "eoen/database/sortie/sortie_ship.hpp"
#include "kcapi/api_start2/api_mst_ship.hpp"
#include "kcapi/api_start2/api_mst_slotitem.hpp"
#include "optional/optional.hpp"
#include "sortie_data/slot.hpp"

namespace kcv {

/// @brief 艦船.
class ship final {
   public:
    using eoen_type = eoen::database::sortie::sortie_ship;

    static auto from_eoen(
        const eoen_type& src, const kcapi::api_mst_ship& mst_ship, const kcapi::api_mst_slotitem& mst_slotitem
    ) -> ship {
        const auto itr = std::ranges::lower_bound(mst_ship, src.id, {}, &kcapi::api_mst_ship_value_type::api_id);
        if (itr != std::ranges::end(mst_ship) and itr->api_id == src.id) [[likely]] {
            return ship{
                *itr,
                src.equipment_slots  //
                    | std::ranges::views::transform([&](const auto& e) { return slot::from_eoen(e, mst_slotitem); })
                    | std::ranges::to<std::vector>(),
                src.expansion_slot.transform([&](const auto& e) { return slot::from_eoen(e, mst_slotitem); })
            };
        } else {
            std::println(stderr, "{} not found in api_mst_slotitem.", std::to_underlying(src.id));
            std::exit(EXIT_FAILURE);
        }
    }

    constexpr ship(const kcapi::api_mst_ship_value_type& mst, std::vector<slot> slots, std::optional<slot> ex) noexcept
        : mst_{mst}
        , slots_{std::move(slots)}
        , expansion_slot_{std::move(ex)} {
    }

    constexpr auto mst() const noexcept -> const kcapi::api_mst_ship_value_type& {
        return this->mst_;
    }

    /// @note `eq` はkcapi::api_mst_ship_value_type::api_maxeqから.
    constexpr auto eqslots() const noexcept -> const std::vector<slot>& {
        return this->slots_;
    }

    constexpr auto expansion_slot() const noexcept -> const std::optional<slot>& {
        return this->expansion_slot_;
    }

    /// @brief 装備スロットと補強増設スロット.
    /// @note C++26のstd::ranges::views::concatの代替として, range-v3を使って実装.
    constexpr std::ranges::range auto slots() const noexcept {
        return ::ranges::views::concat(this->slots_, this->expansion_slot_);
    }

   private:
    /// @brief 艦船マスタ.
    const kcapi::api_mst_ship_value_type& mst_;
    // status_;

    /// @brief 装備スロット. 補強増設スロットはを含まない.
    std::vector<slot> slots_;

    /// @brief 補強増設スロット.
    kcv::optional<slot> expansion_slot_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_SHIP_HPP_INCLUDED
