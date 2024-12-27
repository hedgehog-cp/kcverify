#ifndef KCVERIFY_SORTIE_AIR_BASE_SQUADRON_HPP_INCLUDED
#define KCVERIFY_SORTIE_AIR_BASE_SQUADRON_HPP_INCLUDED

// std
#include <optional>

// kcv
#include "eoen/database/sortie/sorite_air_base_squadron.hpp"
#include "kcapi/api_start2/api_mst_slotitem.hpp"
#include "sortie_data/slot.hpp"

namespace kcv {

/// @brief 基地航空隊. 第N航空隊の中隊. スロット1つに相当.
class air_base_squadron final {
   public:
    using eoen_type = eoen::database::sortie::sorite_air_base_squadron;

    static auto from_eoen(const eoen_type& src, const kcapi::api_mst_slotitem& mst) -> air_base_squadron {
        return air_base_squadron{
            src.aircraft_current,
            src.state,
            src.condition,
            slot::from_eoen(src.equipment_slot, mst),
        };
    }

    constexpr air_base_squadron() = default;

    constexpr air_base_squadron(std::optional<int> aircraft_current, int state, int condition, kcv::slot slot) noexcept
        : aircraft_current_{aircraft_current}
        , state_{state}
        , condition_{condition}
        , slot_{slot} {
    }

    constexpr auto aircraft_current() const noexcept -> const std::optional<int>& {
        return this->aircraft_current_;
    }

    constexpr int state() const noexcept {
        return this->state_;
    }

    constexpr int condition() const noexcept {
        return this->condition_;
    }

    constexpr auto slot() const noexcept -> const slot& {
        return this->slot_;
    }

   private:
    std::optional<int> aircraft_current_;
    int state_;
    int condition_;
    kcv::slot slot_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_AIR_BASE_SQUADRON_HPP_INCLUDED
