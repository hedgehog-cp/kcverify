#ifndef KCVERIFY_SORTIE_SLOT_HPP_INCLUDED
#define KCVERIFY_SORTIE_SLOT_HPP_INCLUDED

// std
#include <optional>

// kcv
#include "eoen/database/sortie/sortie_equipment_slot.hpp"
#include "sortie_data/equipment.hpp"

namespace kcv {

/// @brief スロットいっこ.
class slot final {
   public:
    using eoen_type = eoen::database::sortie::sortie_equipment_slot;

    static auto from_eoen(const eoen_type& src, const kcapi::api_mst_slotitem& mst) -> slot {
        return slot{
            src.aircraft_current,                                                                 //
            src.aircraft_max,                                                                     //
            src.equipment.transform([&](const auto& e) { return equipment::from_eoen(e, mst); })  //
        };
    }

    constexpr slot() = default;

    constexpr slot(int current, int max, const std::optional<equipment>& equipment = std::nullopt) noexcept
        : aircraft_current_{current}
        , aircraft_max_{max}
        , equipment_{equipment} {
    }

    constexpr int aircraft_current() const noexcept {
        return this->aircraft_current_;
    }

    constexpr int aircraft_max() const noexcept {
        return this->aircraft_max_;
    }

    constexpr auto equipment() const noexcept -> const std::optional<equipment>& {
        return this->equipment_;
    }

   private:
    /// @brief 現在搭載数.
    int aircraft_current_;

    /// @brief 最大搭載数.
    int aircraft_max_;

    /// @brief 装備.
    std::optional<kcv::equipment> equipment_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_SLOT_HPP_INCLUDED
