#ifndef KCVERIFY_CORE_ENTITY_AIR_BASE_HPP_INCLUDED
#define KCVERIFY_CORE_ENTITY_AIR_BASE_HPP_INCLUDED

// std
#include <cstdint>
#include <string>
#include <vector>

// kcv
#include "core/entity/air_base_squadron.hpp"
#include "models/kcsapi/types/enum/air_base_action.hpp"

namespace kcv {

class air_base final {
   public:
    air_base(
        std::string name,
        std::int32_t map_area_id,
        std::int32_t air_corps_id,
        kcv::kcsapi::air_base_action action_kind,
        std::int32_t base_distance,
        std::int32_t bonus_distance,
        std::vector<kcv::air_base_squadron> squadrons
    ) noexcept
        : name_{name}
        , map_area_id_{map_area_id}
        , air_corps_id_{air_corps_id}
        , action_kind_{action_kind}
        , base_distance_{base_distance}
        , bonus_distance_{bonus_distance}
        , squadrons_{squadrons} {}

    auto name() const noexcept -> const std::string& {
        return this->name_;
    }

    auto map_area_id() const noexcept -> std::int32_t {
        return this->map_area_id_;
    }

    auto air_corps_id() const noexcept -> std::int32_t {
        return this->air_corps_id_;
    }

    auto action_kind() const noexcept -> kcv::kcsapi::air_base_action {
        return this->action_kind_;
    }

    auto base_distance() const noexcept -> std::int32_t {
        return this->base_distance_;
    }

    auto bonus_distance() const noexcept -> std::int32_t {
        return this->bonus_distance_;
    }

    auto squadrons() const noexcept -> const std::vector<kcv::air_base_squadron>& {
        return this->squadrons_;
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
    std::vector<kcv::air_base_squadron> squadrons_;
};

}  // namespace kcv

#endif  // KCVERIFY_CORE_ENTITY_AIR_BASE_HPP_INCLUDED
