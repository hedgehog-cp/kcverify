#ifndef KCV_DOMAIN_VERIFICATION_ENTITY_AIR_BASE_SQUADRON_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_ENTITY_AIR_BASE_SQUADRON_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <utility>

// kcv
#include "kcv/domain/verification/entity/slot.hpp"

namespace kcv {

class air_base_squadron final {
   public:
    air_base_squadron(
        std::optional<std::int32_t> aircraft_current,
        std::int32_t state,
        std::int32_t condition,
        kcv::slot slot
    ) noexcept
        : aircraft_current_{std::move(aircraft_current)}
        , state_{state}
        , condition_{condition}
        , slot_{std::move(slot)} {}

    auto aircraft_current() const noexcept -> const std::optional<std::int32_t>& {
        return this->aircraft_current_;
    }

    auto state() const noexcept -> std::int32_t {
        return this->state_;
    }

    auto condition() const noexcept -> std::int32_t {
        return this->condition_;
    }

    auto slot() const noexcept -> const kcv::slot& {
        return this->slot_;
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

#endif  // KCV_DOMAIN_VERIFICATION_ENTITY_AIR_BASE_SQUADRON_HPP_INCLUDED
