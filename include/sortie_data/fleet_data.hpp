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
    using eoen_type = eoen::database::sortie::sortie_fleet_data;

    static constexpr auto from_eoen(
        const eoen_type& src, const kcapi::api_mst_ship& mst_ship, const kcapi::api_mst_slotitem& mst_slotitem
    ) -> fleet_data {
        return fleet_data{
            src.fleet_id,               //
            src.node_support_fleet_id,  //
            src.boss_support_fleet_id,  //
            src.combined_flag,          //
            src.fleets                  //
                | std::ranges::views::transform([&](const auto& opt) {
                      return opt.transform([&](const auto& e) { return fleet::from_eoen(e, mst_ship, mst_slotitem); });
                  })
                | std::ranges::to<std::vector>(),
            src.air_bases  //
                | std::ranges::views::transform([&](const auto& e) { return air_base::from_eoen(e, mst_slotitem); })
                | std::ranges::to<std::vector>()
        };
    }

    constexpr fleet_data() = default;

    constexpr fleet_data(
        int fleet_id,                              //
        int node_support_fleet_id,                 //
        int boss_support_fleet_id,                 //
        int combined_flag,                         //
        std::vector<std::optional<fleet>> fleets,  //
        std::vector<air_base> air_bases            //
    ) noexcept
        : fleet_id_{fleet_id}
        , node_support_fleet_id_{node_support_fleet_id}
        , boss_support_fleet_id_{boss_support_fleet_id}
        , combined_flag_{combined_flag}
        , fleets_{std::move(fleets)}
        , air_bases_{std::move(air_bases)} {
    }

    constexpr int fleet_id() const noexcept {
        return this->fleet_id_;
    }

    constexpr int node_support_fleet_id() const noexcept {
        return this->node_support_fleet_id_;
    }

    constexpr int boss_support_fleet_id() const noexcept {
        return this->boss_support_fleet_id_;
    }

    constexpr int combined_flag() const noexcept {
        return this->combined_flag_;
    }

    constexpr auto fleets() const noexcept -> const std::vector<std::optional<fleet>>& {
        return this->fleets_;
    }

    constexpr auto air_bases() const noexcept -> const std::vector<air_base>& {
        return this->air_bases_;
    }

   private:
    int fleet_id_;
    int node_support_fleet_id_;
    int boss_support_fleet_id_;
    int combined_flag_;
    std::vector<std::optional<fleet>> fleets_;
    std::vector<air_base> air_bases_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_DATA_FLEET_DATA_HPP_INCLUDED
