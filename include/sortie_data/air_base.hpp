#ifndef KCVERIFY_SORTIE_AIR_BASE_HPP_INCLUDED
#define KCVERIFY_SORTIE_AIR_BASE_HPP_INCLUDED

#include <ranges>
#include <string>
#include <vector>

#include "eoen/database/sortie/sortie_air_base.hpp"
#include "kcsapi/types/enum/air_base_action.hpp"
#include "sortie_data/air_base_squadron.hpp"

namespace kcv {

/// @brief 基地航空隊. 第N航空隊の第1~4中隊. スロット1~4に相当.
class air_base final {
   public:
    using eoen_type = eoen::database::sortie::sortie_air_base;

    static auto from_eoen(const eoen_type& src, const kcsapi::api_mst_slotitem& mst) -> air_base {
        return air_base{
            std::move(src.name),
            src.map_area_id,
            src.air_corps_id,
            src.action_kind,
            src.base_distance,
            src.bonus_distance,
            src.squadrons  //
                | std::ranges::views::transform([&](const auto& e) { return air_base_squadron::from_eoen(e, mst); })
                | std::ranges::to<std::vector>(),
        };
    }

    constexpr air_base() = default;

    constexpr air_base(
        std::string name,                         //
        int map_area_id,                          //
        int air_corps_id,                         //
        kcsapi::air_base_action action_kind,      //
        int base_distance,                        //
        int bonus_distance,                       //
        std::vector<air_base_squadron> squadrons  //
    ) noexcept
        : name_{std::move(name)}
        , map_area_id_{map_area_id}
        , air_corps_id_{air_corps_id}
        , action_kind_{action_kind}
        , base_distance_{base_distance}
        , bonus_distance_{bonus_distance}
        , squadrons_{std::move(squadrons)} {
    }

    constexpr auto name() const noexcept -> const std::string& {
        return this->name_;
    }

    constexpr int map_area_id() const noexcept {
        return this->map_area_id_;
    }

    constexpr int air_corps_id() const noexcept {
        return this->air_corps_id_;
    }

    constexpr auto action_kind() const noexcept -> kcsapi::air_base_action {
        return this->action_kind_;
    }

    constexpr int base_distance() const noexcept {
        return this->base_distance_;
    }

    constexpr int bonus_distance() const noexcept {
        return this->bonus_distance_;
    }

    constexpr auto squadrons() const noexcept -> const std::vector<air_base_squadron>& {
        return this->squadrons_;
    }

   private:
    std::string name_;
    int map_area_id_;
    int air_corps_id_;
    kcsapi::air_base_action action_kind_;
    int base_distance_;
    int bonus_distance_;
    std::vector<air_base_squadron> squadrons_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_AIR_BASE_HPP_INCLUDED
