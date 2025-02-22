#ifndef KCVERIFY_SORTIE_AIR_BASE_SQUADRON_HPP_INCLUDED
#define KCVERIFY_SORTIE_AIR_BASE_SQUADRON_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>

// kcv
#include "eoen/database/sortie/sortie_air_base_squadron.hpp"
#include "kcsapi/api_start2/api_mst_slotitem.hpp"
#include "sortie_data/slot.hpp"

namespace kcv {

/// @brief 基地航空隊. 第N航空隊の中隊. スロット1つに相当.
class air_base_squadron final {
   public:
    using eoen_type = kcv::eoen::database::sortie::sortie_air_base_squadron;

    static auto from_eoen(const eoen_type& src, const kcv::kcsapi::api_mst_slotitem& mst) -> air_base_squadron {
        return air_base_squadron{
            src.aircraft_current,
            src.state,
            src.condition,
            slot::from_eoen(src.equipment_slot, mst),
        };
    }

    // clang-format off

    constexpr air_base_squadron(
        std::optional<std::int32_t> aircraft_current,
        std::int32_t state,
        std::int32_t condition,
        kcv::slot slot
    ) noexcept
        : aircraft_current_{std::move(aircraft_current)}
        , state_{std::move(state)}
        , condition_{std::move(condition)}
        , slot_{std::move(slot)} {}

    // clang-format on

    constexpr auto aircraft_current() const noexcept -> decltype(auto) {
        return (this->aircraft_current_);
    }

    constexpr auto state() const noexcept -> decltype(auto) {
        return (this->state_);
    }

    constexpr auto condition() const noexcept -> decltype(auto) {
        return (this->condition_);
    }

    constexpr auto slot() const noexcept -> decltype(auto) {
        return (this->slot_);
    }

   private:
    /// @brief 現在搭載数.
    std::optional<std::int32_t> aircraft_current_;

    /// @brief 0=未配属, 1=配属済み, 2=配置転換中.
    std::int32_t state_;

    /// @brief 疲労度. 1=通常, 2=黄疲労, 3=赤疲労. 未配属なら存在しない.
    std::int32_t condition_;

    /// @brief 装備スロット.
    kcv::slot slot_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_AIR_BASE_SQUADRON_HPP_INCLUDED
