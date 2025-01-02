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
    using eoen_type = eoen::database::sortie::sortie_fleet;

    static auto from_eoen(
        const eoen_type& src, const kcsapi::api_mst_ship& mst_ship, const kcsapi::api_mst_slotitem& mst_slotitem
    ) -> fleet {
        return fleet{
            std::move(src.name),  //
            src.ships             //
                | std::ranges::views::transform([&](const auto& e) {
                      return ship::from_eoen(e, mst_ship, mst_slotitem);
                  })
                | std::ranges::to<std::vector>()
        };
    }

    constexpr fleet(std::string name, std::vector<ship> ships)
        : name_{std::move(name)}
        , ships_{std::move(ships)} {
    }

    constexpr fleet(std::vector<ship>&& ships)
        : ships_{std::move(ships)} {
    }

    constexpr auto name() const noexcept -> const std::string& {
        return this->name_;
    }

    constexpr auto ships() const noexcept -> const std::vector<ship>& {
        return this->ships_;
    }

   private:
    std::string name_;
    std::vector<ship> ships_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_DATA_FLEET_HPP_INCLUDED
