#ifndef KCVERIFY_SORTIE_SORTIE_DATA_HPP_INCLUDED
#define KCVERIFY_SORTIE_SORTIE_DATA_HPP_INCLUDED

// std
#include <cstdlib>
#include <utility>
#include <vector>

// kcv
#include "eoen/database/sortie/sortie_record.hpp"
#include "kcsapi/api_start2/api_mst_ship.hpp"
#include "kcsapi/api_start2/api_mst_slotitem.hpp"
#include "sortie/fleet_data.hpp"
#include "sortie/map_data.hpp"
#include "sortie/sortie_api.hpp"

namespace kcv {
namespace sortie {

class sortie_data final {
   public:
    using eoen_type = kcv::eoen::database::sortie::sortie_record;

    static auto from_eoen(
        const eoen_type &src, const kcv::kcsapi::api_mst_ship &api_mst_ship,
        const kcv::kcsapi::api_mst_slotitem &api_mst_slotitem
    ) -> sortie_data {
        auto api_files = std::vector<kcv::sortie::sortie_api>{};
        kcv::sortie::read_json(api_files, src.api_files);
        return sortie_data{
            src.world,
            src.map,
            std::move(api_files),
            kcv::sortie::fleet_data::from_eoen(src.fleet_data, api_mst_ship, api_mst_slotitem),
            src.fleet_after_sortie_data.transform([&](const auto &e) {
                return kcv::sortie::fleet_data::from_eoen(e, api_mst_ship, api_mst_slotitem);
            }),
            kcv::sortie::map_data::from_eoen(src.map_data),
        };
    }

    // clang-format off

    constexpr sortie_data(
        std::int32_t world,
        std::int32_t map,
        std::vector<kcv::sortie::sortie_api> sortie_api,
        kcv::sortie::fleet_data fleet_data,
        std::optional<kcv::sortie::fleet_data> fleet_after_sortie_data,
        kcv::sortie::map_data map_data
    )
        : world_{std::move(world)}
        , map_{std::move(map)}
        , sortie_api_{std::move(sortie_api)}
        , fleet_data_{std::move(fleet_data)}
        , fleet_after_sortie_data_{std::move(fleet_after_sortie_data)}
        , map_data_{std::move(map_data)} {}

    // clang-format on

    constexpr auto world(this auto &&self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.world_);
    }

    constexpr auto map(this auto &&self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.map_);
    }

    constexpr auto sortie_api(this auto &&self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.sortie_api_);
    }

    constexpr auto fleet_data(this auto &&self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.fleet_data_);
    }

    constexpr auto fleet_after_sortie_data(this auto &&self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.fleet_after_sortie_data_);
    }

    constexpr auto map_data(this auto &&self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.map_data_);
    }

   private:
    /// @brief 74式ENの何某かの管理用ID.
    // std::int32_t id_;

    /// @brief 74式ENの何某かの管理用Version.
    // std::int32_t version_;

    /// @brief 海域. #5-3-Pに対する5.
    std::int32_t world_;

    /// @brief 海域. #5-3-Pに対する3.
    std::int32_t map_;

    /// @brief この出撃中に送受信したAPI
    std::vector<kcv::sortie::sortie_api> sortie_api_;

    /// @brief 出撃前艦隊データ.
    kcv::sortie::fleet_data fleet_data_;

    /// @brief 出撃後艦隊データ.
    std::optional<kcv::sortie::fleet_data> fleet_after_sortie_data_;

    /// @brief 海域攻略進捗データ.
    kcv::sortie::map_data map_data_;
};

}  // namespace sortie
}  // namespace kcv

#endif  // KCVERIFY_SORTIE_SORTIE_DATA_HPP_INCLUDED
