#ifndef KCVERIFY_SORTIE_DATA_FLEET_HPP_INCLUDED
#define KCVERIFY_SORTIE_DATA_FLEET_HPP_INCLUDED

// std
#include <ranges>
#include <utility>
#include <vector>

// kcv
#include "eoen/database/sortie/sortie_fleet.hpp"
#include "sortie_data/ship.hpp"

namespace kcv {

/// @brief 艦隊.
class fleet final {
   public:
    using eoen_type = kcv::eoen::database::sortie::sortie_fleet;

    // clang-format off

    static constexpr auto from_eoen(
        const eoen_type& src,
        const kcv::kcsapi::api_mst_ship& api_mst_ship,
        const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem
    ) -> fleet {
        return fleet{
            src.name,
            src.ships
                | std::ranges::views::transform([&](const auto& e) {
                      return kcv::ship::from_eoen(e, api_mst_ship, api_mst_slotitem);
                  }) 
                | std::ranges::to<std::vector>(),
        };
    }

    // clang-format on

    constexpr fleet(std::string name, std::vector<kcv::ship> ships)
        : name_{std::move(name)}
        , ships_{std::move(ships)} {}

    constexpr auto name() const noexcept -> decltype(auto) {
        return (this->name_);
    }

    constexpr auto ships() const noexcept -> decltype(auto) {
        return (this->ships_);
    }

   private:
    /// @brief 艦隊名.
    std::string name_;

    /// @brief 艦船.
    std::vector<kcv::ship> ships_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_DATA_FLEET_HPP_INCLUDED
