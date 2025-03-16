#ifndef KCVERIFY_SORTIE_SLOT_HPP_INCLUDED
#define KCVERIFY_SORTIE_SLOT_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <utility>

// kcv
#include "eoen/database/sortie/sortie_equipment_slot.hpp"
#include "sortie/equipment.hpp"

namespace kcv {
namespace sortie {

/// @brief スロット.
class slot final {
   public:
    using eoen_type = kcv::eoen::database::sortie::sortie_equipment_slot;

    static constexpr auto from_eoen(const eoen_type& src, const kcv::kcsapi::api_mst_slotitem& mst) -> slot {
        return slot{
            src.aircraft_current,
            src.aircraft_max,
            src.equipment.transform([&](const auto& e) { return kcv::sortie::equipment::from_eoen(e, mst); }),
        };
    }

    constexpr slot(std::int32_t current, std::int32_t max, std::optional<kcv::sortie::equipment> equipment) noexcept
        : aircraft_current_{std::move(current)}
        , aircraft_max_{std::move(max)}
        , equipment_{std::move(equipment)} {}

    constexpr auto aircraft_current(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.aircraft_current_);
    }

    constexpr auto aircraft_max(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.aircraft_max_);
    }

    constexpr auto equipment(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.equipment_);
    }

   private:
    /// @brief 現在搭載数.
    std::int32_t aircraft_current_;

    /// @brief 最大搭載数.
    std::int32_t aircraft_max_;

    /// @brief 装備.
    std::optional<kcv::sortie::equipment> equipment_;
};

}  // namespace sortie
}  // namespace kcv

#endif  // KCVERIFY_SORTIE_SLOT_HPP_INCLUDED
