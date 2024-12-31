#ifndef KCVERIFY_SORTIE_DATA_SHIP_HPP_INCLUDED
#define KCVERIFY_SORTIE_DATA_SHIP_HPP_INCLUDED

// std
#include <optional>
#include <ranges>
#include <vector>

// ranges: C++26から不要
#include <range/v3/view/concat.hpp>

// kcv
#include "eoen/database/sortie/sortie_ship.hpp"
#include "kcsapi/api_start2/api_mst_ship.hpp"
#include "kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcsapi/types/enum/nationality.hpp"
#include "kcsapi/types/enum/ship_id.hpp"
#include "optional/optional.hpp"
#include "sortie_data/slot.hpp"

namespace kcv {

/// @brief 艦船.
class ship final {
   public:
    using eoen_type = eoen::database::sortie::sortie_ship;

    static auto from_eoen(
        const eoen_type& src, const kcsapi::api_mst_ship& mst_ship, const kcsapi::api_mst_slotitem& mst_slotitem
    ) -> ship {
        const auto itr = std::ranges::lower_bound(mst_ship, src.id, {}, &kcsapi::api_mst_ship_value_type::api_id);
        if (itr == std::ranges::end(mst_ship) or itr->api_id != src.id) [[unlikely]] {
            std::println(stderr, "{} not found in api_mst_ship.", std::to_underlying(src.id));
            std::exit(EXIT_FAILURE);
        }

        constexpr auto null_id = kcv::kcsapi::ship_id{-1};
        const auto original_id = std::ranges::fold_left(
            mst_ship  //
                | std::ranges::views::filter([&itr](const auto& e) -> bool {
                      return e.api_yomi == itr->api_yomi and e.api_sort_id % 10 == 1;
                  })
                | std::ranges::views::take(1),
            null_id, [](auto, const auto& e) -> kcv::kcsapi::ship_id { return e.api_id; }
        );
        if (original_id != null_id) [[likely]] {
            return ship{
                *itr, original_id,
                src.equipment_slots  //
                    | std::ranges::views::transform([&](const auto& e) { return slot::from_eoen(e, mst_slotitem); })
                    | std::ranges::to<std::vector>(),
                src.expansion_slot.transform([&](const auto& e) { return slot::from_eoen(e, mst_slotitem); })
            };
        } else {
            std::println(stderr, "{}'s original_id not found in api_mst_ship.", std::to_underlying(src.id));
            std::exit(EXIT_FAILURE);
        }
    }

    constexpr ship(
        const kcsapi::api_mst_ship_value_type& mst, kcv::kcsapi::ship_id original_id, std::vector<slot> slots,
        std::optional<slot> ex
    ) noexcept
        : mst_{mst}
        , original_id_{original_id}
        , nationality_{kcv::kcsapi::to_nationality(mst.api_sort_id)}
        , eqslots_{std::move(slots)}
        , exslot_{std::move(ex)} {
    }

    constexpr auto mst() const noexcept -> const kcsapi::api_mst_ship_value_type& {
        return this->mst_;
    }

    constexpr auto original_id() const noexcept -> kcv::kcsapi::ship_id {
        return this->original_id_;
    }

    constexpr auto nationality() const noexcept -> kcv::kcsapi::nationality {
        return this->nationality_;
    }

    /// @note `eq` はkcsapi::api_mst_ship_value_type::api_maxeqから.
    constexpr auto eqslots() const noexcept -> const std::vector<slot>& {
        return this->eqslots_;
    }

    constexpr auto exslot() const noexcept -> const std::optional<slot>& {
        return this->exslot_;
    }

    /// @brief 装備スロットと補強増設スロット.
    /// @note C++26のstd::ranges::views::concatの代替として, range-v3を使って実装.
    constexpr std::ranges::range auto slots() const noexcept {
        return ::ranges::views::concat(this->eqslots_, this->exslot_);
    }

   private:
    /// @brief 艦船マスタ.
    const kcsapi::api_mst_ship_value_type& mst_;

    /// @brief 未改造艦船ID
    kcv::kcsapi::ship_id original_id_;

    /// @brief 国籍
    kcv::kcsapi::nationality nationality_;

    // status_;

    /// @brief 装備スロット. 補強増設スロットを含まない.
    std::vector<slot> eqslots_;

    /// @brief 補強増設スロット.
    kcv::optional<slot> exslot_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_DATA_SHIP_HPP_INCLUDED
