#ifndef KCVERIFY_CORE_ENTITY_FLEET_DATA_HPP_INCLUDED
#define KCVERIFY_CORE_ENTITY_FLEET_DATA_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "core/entity/air_base.hpp"
#include "core/entity/fleet.hpp"

namespace kcv {

class fleet_data final {
   public:
    fleet_data(
        std::int32_t fleet_id,
        std::int32_t node_support_fleet_id,
        std::int32_t boss_support_fleet_id,
        std::int32_t combined_flag,
        std::vector<std::optional<kcv::fleet>> fleets,
        std::vector<kcv::air_base> air_bases
    ) noexcept
        : fleet_id_{fleet_id}
        , node_support_fleet_id_{node_support_fleet_id}
        , boss_support_fleet_id_{boss_support_fleet_id}
        , combined_flag_{combined_flag}
        , fleets_{fleets}
        , air_bases_{air_bases} {}

    auto fleet_id() const noexcept -> std::int32_t {
        return this->fleet_id_;
    }

    auto node_support_fleet_id() const noexcept -> std::int32_t {
        return this->node_support_fleet_id_;
    }

    auto boss_support_fleet_id() const noexcept -> std::int32_t {
        return this->boss_support_fleet_id_;
    }

    auto combined_flag() const noexcept -> std::int32_t {
        return this->combined_flag_;
    }

    auto fleets() const noexcept -> const std::vector<std::optional<kcv::fleet>>& {
        return this->fleets_;
    }

    auto air_bases() const noexcept -> const std::vector<kcv::air_base>& {
        return this->air_bases_;
    }

   private:
    /// @brief 1 or 2 or 3 or 4.
    std::int32_t fleet_id_;

    /// @brief 前衛支援. 0 = none, 1~4 = fleets
    std::int32_t node_support_fleet_id_;

    /// @brief 艦隊決戦支援.
    std::int32_t boss_support_fleet_id_;

    /// @see https://github.com/ElectronicObserverEN/ElectronicObserver/blob/main/ElectronicObserverTypes/FleetType.cs
    std::int32_t combined_flag_;

    /// @brief 第1艦隊~第4艦隊.
    std::vector<std::optional<kcv::fleet>> fleets_;

    /// @brief 第1基地航空隊~第3基地航空隊.
    std::vector<kcv::air_base> air_bases_;
};

}  // namespace kcv

#endif  // KCVERIFY_CORE_ENTITY_FLEET_DATA_HPP_INCLUDED
