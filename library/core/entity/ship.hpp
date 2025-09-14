#ifndef KCVERIFY_CORE_ENTITY_SHIP_HPP_INCLUDED
#define KCVERIFY_CORE_ENTITY_SHIP_HPP_INCLUDED

// std
#include <vector>

// kcv
#include "core/entity/slot.hpp"
#include "extensions/ranges.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/types/enum/nationality.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"

namespace kcv {

/// @brief 艦船.
class ship final {
   public:
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

}  // namespace kcv

#endif  // KCVERIFY_CORE_ENTITY_SHIP_HPP_INCLUDED
