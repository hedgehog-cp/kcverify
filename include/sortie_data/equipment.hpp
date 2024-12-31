#ifndef KCVERIFY_SORTIE_EQUIPMENT_HPP_INCLUDED
#define KCVERIFY_SORTIE_EQUIPMENT_HPP_INCLUDED

// std
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <print>
#include <utility>

// kcv
#include "eoen/database/sortie/sortie_equipment.hpp"
#include "kcsapi/api_start2/api_mst_slotitem.hpp"

namespace kcv {

/// @brief 装備.
class equipment final {
   public:
    using eoen_type = eoen::database::sortie::sortie_equipment;

    static auto from_eoen(const eoen_type& src, const kcsapi::api_mst_slotitem& mst) -> equipment {
        const auto itr = std::ranges::lower_bound(mst, src.id, {}, &kcsapi::api_mst_slotitem_value_type::api_id);
        if (itr != std::ranges::end(mst) and itr->api_id == src.id) [[likely]] {
            return equipment{*itr, src.level, src.aircraft_level};
        } else {
            std::println(stderr, "{} not found in api_mst_slotitem.", std::to_underlying(src.id));
            std::exit(EXIT_FAILURE);
        }
    }

    constexpr equipment(const kcsapi::api_mst_slotitem_value_type& mst, int level, int aircraft_level) noexcept
        : mst_{mst}
        , level_{level}
        , aircraft_level_{aircraft_level} {
    }

    constexpr auto mst() const noexcept -> const kcsapi::api_mst_slotitem_value_type& {
        return this->mst_;
    }

    constexpr int level() const noexcept {
        return this->level_;
    }

    constexpr int aircraft_level() const noexcept {
        return this->aircraft_level_;
    }

   private:
    /// @brief 装備マスタ.
    const kcsapi::api_mst_slotitem_value_type& mst_;

    /// @brief 改修値.
    int level_;

    /// @brief 熟練度.
    int aircraft_level_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_EQUIPMENT_HPP_INCLUDED
