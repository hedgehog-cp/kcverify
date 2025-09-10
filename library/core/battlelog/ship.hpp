#ifndef KCVERIFY_CORE_BATTLELOG_SHIP_HPP_INCLUDED
#define KCVERIFY_CORE_BATTLELOG_SHIP_HPP_INCLUDED

// std
#include <concepts>
#include <ranges>
#include <vector>

// kcv
#include "core/battlelog/slot.hpp"
#include "extensions/ranges.hpp"
#include "models/eoen/database/sortie/sortie_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/enum/nationality.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"

namespace kcv {

/// @brief 艦船.
class ship final {
   public:
    using eoen_type = kcv::eoen::database::sortie::sortie_ship;

    static auto from_eoen(
        const eoen_type& src,
        const kcv::kcsapi::api_mst_ship& api_mst_ship,
        const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
    ) -> ship {
        const auto& mst = kcv::find_mst(api_mst_ship, src.id);
        return ship{
            mst,
            kcv::base_id(api_mst_ship, mst),
            kcv::nationality(mst),
            src.equipment_slots  //
                | std::ranges::views::transform([&api_mst_slotitem](const auto& e) {
                      return kcv::slot::from_eoen(e, api_mst_slotitem);
                  })
                | std::ranges::to<std::vector>(),
            src.expansion_slot.transform([&api_mst_slotitem](const auto& e) {
                return kcv::slot::from_eoen(e, api_mst_slotitem);
            }),
        };
    }

    ship(
        const kcv::kcsapi::api_mst_ship_value_t& mst,
        kcv::kcsapi::ship_id base_id,
        kcv::kcsapi::nationality nationality,
        std::vector<kcv::slot> eqslots,
        std::optional<kcv::slot> exslot
    )
        : mst_{mst}
        , base_id_{base_id}
        , nationality_{nationality}
        , eqslots_{eqslots}
        , exslot_{exslot}
        , slots_{kcv::ranges::views::concat(this->eqslots_, this->exslot_)} {}

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
};

bool has_equipment_if(
    const auto& slots,
    const std::predicate<const kcv::kcsapi::api_mst_slotitem_value_t&> auto& pred
) {
    for (const auto& slot : slots) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            if (pred(e->mst())) {
                return true;
            }
        }
    }
    return false;
}

}  // namespace kcv

#endif  // KCVERIFY_CORE_BATTLELOG_SHIP_HPP_INCLUDED
