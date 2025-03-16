#ifndef KCVERIFY_SORTIE_AIR_BASE_HPP_INCLUDED
#define KCVERIFY_SORTIE_AIR_BASE_HPP_INCLUDED

// std
#include <cstdint>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

// kcv
#include "eoen/database/sortie/sortie_air_base.hpp"
#include "kcsapi/types/enum/air_base_action.hpp"
#include "sortie/air_base_squadron.hpp"

namespace kcv {
namespace sortie {

/// @brief 基地航空隊. 第N航空隊の第1~4中隊. スロット1~4に相当.
class air_base final {
   public:
    using eoen_type = kcv::eoen::database::sortie::sortie_air_base;

    // clang-format off

    static auto from_eoen(const eoen_type& src, const kcv::kcsapi::api_mst_slotitem& mst) -> air_base {
        return air_base{
            std::move(src.name),
            src.map_area_id,
            src.air_corps_id,
            src.action_kind,
            src.base_distance,
            src.bonus_distance,
            src.squadrons
                | std::ranges::views::transform([&](const auto& e) {
                      return kcv::sortie::air_base_squadron::from_eoen(e, mst);
                  })
                | std::ranges::to<std::vector>(),
        };
    }

    // clang-format on

    // clang-format off

    constexpr air_base(
        std::string name,
        std::int32_t map_area_id,
        std::int32_t air_corps_id,
        kcsapi::air_base_action action_kind,
        std::int32_t base_distance,
        std::int32_t bonus_distance,
        std::vector<kcv::sortie::air_base_squadron> squadrons
    ) noexcept
        : name_{std::move(name)}
        , map_area_id_{std::move(map_area_id)}
        , air_corps_id_{std::move(air_corps_id)}
        , action_kind_{std::move(action_kind)}
        , base_distance_{std::move(base_distance)}
        , bonus_distance_{std::move(bonus_distance)}
        , squadrons_{std::move(squadrons)} {}

    // clang-format on

    constexpr auto name(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.name_);
    }

    constexpr auto map_area_id(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.map_area_id_);
    }

    constexpr auto air_corps_id(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.air_corps_id_);
    }

    constexpr auto action_kind(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.action_kind_);
    }

    constexpr auto base_distance(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.base_distance_);
    }

    constexpr auto bonus_distance(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.bonus_distance_);
    }

    constexpr auto squadrons(this auto&& self) noexcept -> decltype(auto) {
        return std::forward_like<decltype(self)>(self.squadrons_);
    }

   private:
    /// @brief 航空隊名.
    std::string name_;

    /// @brief 所属海域ID.
    std::int32_t map_area_id_;

    std::int32_t air_corps_id_;

    /// @brief 行動指示.
    kcv::kcsapi::air_base_action action_kind_;

    /// @brief 戦闘行動半径.
    std::int32_t base_distance_;

    /// @brief 偵察機などによる戦闘行動半径のボーナス.
    std::int32_t bonus_distance_;

    /// @brief 第N中隊.
    std::vector<kcv::sortie::air_base_squadron> squadrons_;
};

}  // namespace sortie
}  // namespace kcv

#endif  // KCVERIFY_SORTIE_AIR_BASE_HPP_INCLUDED
