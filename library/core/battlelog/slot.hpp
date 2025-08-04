#ifndef KCVERIFY_CORE_BATTLELOG_SLOT_HPP_INCLUDED
#define KCVERIFY_CORE_BATTLELOG_SLOT_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>

// kcv
#include "core/battlelog/equipment.hpp"
#include "models/eoen/database/sortie/sortie_equipment_slot.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"

namespace kcv {

/// @brief スロット.
class slot final {
   public:
    using eoen_type = kcv::eoen::database::sortie::sortie_equipment_slot;

    static auto from_eoen(const eoen_type& src, const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem) -> slot {
        return slot{
            src.aircraft_current,
            src.aircraft_max,
            src.equipment.transform([&api_mst_slotitem](const auto& e) {
                return kcv::equipment::from_eoen(e, api_mst_slotitem);
            }),
        };
    }

    slot(std::int32_t current, std::int32_t max, std::optional<kcv::equipment> equipment)
        : aircraft_current_{current}
        , aircraft_max_{max}
        , equipment_{std::move(equipment)} {}

    auto aircraft_current() const noexcept -> std::int32_t {
        return this->aircraft_current_;
    }

    auto aircraft_max() const noexcept -> std::int32_t {
        return this->aircraft_max_;
    }

    auto equipment() const noexcept -> const std::optional<kcv::equipment>& {
        return this->equipment_;
    }

   private:
    /// @brief 現在搭載数.
    std::int32_t aircraft_current_;

    /// @brief 最大搭載数.
    std::int32_t aircraft_max_;

    /// @brief 装備.
    std::optional<kcv::equipment> equipment_;
};

}  // namespace kcv

#endif  // KCVERIFY_CORE_BATTLELOG_SLOT_HPP_INCLUDED
