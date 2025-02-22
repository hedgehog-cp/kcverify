#ifndef KCVERIFY_SORTIE_DATA_FLEET_DATA_HPP_INCLUDED
#define KCVERIFY_SORTIE_DATA_FLEET_DATA_HPP_INCLUDED

// std
#include <optional>
#include <ranges>
#include <vector>

// kcv
#include "eoen/database/sortie/sortie_fleet_data.hpp"
#include "sortie_data/air_base.hpp"
#include "sortie_data/fleet.hpp"

namespace kcv {

/// @brief 第1~4艦隊と基地航空隊.
class fleet_data final {
   public:
    using eoen_type = kcv::eoen::database::sortie::sortie_fleet_data;

    // clang-format off

    static constexpr auto from_eoen(
        const eoen_type& src,
        const kcv::kcsapi::api_mst_ship& api_mst_ship,
        const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
    ) -> fleet_data {
        return fleet_data{
            src.fleet_id,
            src.node_support_fleet_id,
            src.boss_support_fleet_id,
            src.combined_flag,
            src.fleets
                | std::ranges::views::transform([&](const auto& opt) {
                      return opt.transform([&](const auto& e) {
                          return fleet::from_eoen(e, api_mst_ship, api_mst_slotitem);
                      });
                  })
                | std::ranges::to<std::vector>(),
            src.air_bases
                | std::ranges::views::transform([&](const auto& e) { return air_base::from_eoen(e, api_mst_slotitem); })
                | std::ranges::to<std::vector>()
        };
    }

    // clang-format on

    // clang-format off

    constexpr fleet_data(
        std::int32_t fleet_id,
        std::int32_t node_support_fleet_id,
        std::int32_t boss_support_fleet_id,
        std::int32_t combined_flag,
        std::vector<std::optional<kcv::fleet>> fleets,
        std::vector<kcv::air_base> air_bases
    ) noexcept
        : fleet_id_{std::move(fleet_id)}
        , node_support_fleet_id_{std::move(node_support_fleet_id)}
        , boss_support_fleet_id_{std::move(boss_support_fleet_id)}
        , combined_flag_{std::move(combined_flag)}
        , fleets_{std::move(fleets)}
        , air_bases_{std::move(air_bases)} {}

    // clang-format on

    constexpr auto fleet_id() const noexcept -> decltype(auto) {
        return (this->fleet_id_);
    }

    constexpr auto node_support_fleet_id() const noexcept -> decltype(auto) {
        return (this->node_support_fleet_id_);
    }

    constexpr auto boss_support_fleet_id() const noexcept -> decltype(auto) {
        return (this->boss_support_fleet_id_);
    }

    constexpr auto combined_flag() const noexcept -> decltype(auto) {
        return (this->combined_flag_);
    }

    constexpr auto fleets() const noexcept -> decltype(auto) {
        return (this->fleets_);
    }

    constexpr auto air_bases() const noexcept -> decltype(auto) {
        return (this->air_bases_);
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

#endif  // KCVERIFY_SORTIE_DATA_FLEET_DATA_HPP_INCLUDED
