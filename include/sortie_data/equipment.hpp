#ifndef KCVERIFY_SORTIE_DATA_EQUIPMENT_HPP_INCLUDED
#define KCVERIFY_SORTIE_DATA_EQUIPMENT_HPP_INCLUDED

// std
#include <algorithm>
#include <cstdint>

// kcv
#include "common.hpp"
#include "eoen/database/sortie/sortie_equipment.hpp"
#include "kcsapi/api_start2/api_mst_slotitem.hpp"

namespace kcv {

/// @brief 装備.
class equipment final {
   public:
    using eoen_type = eoen::database::sortie::sortie_equipment;

    static constexpr auto from_eoen(const eoen_type& src, const kcv::kcsapi::api_mst_slotitem& mst) -> equipment {
        return equipment{
            kcv::binary_search(mst, src.id),
            src.level,
            src.aircraft_level,
        };
    }

    // clang-format off

    constexpr equipment(
        const kcv::kcsapi::api_mst_slotitem_value_t& mst,
        std::int32_t level,
        std::int32_t aircraft_level
    ) noexcept
        : mst_{mst}
        , level_{std::move(level)}
        , aircraft_level_{std::move(aircraft_level)} {}

    // clang-format on

    constexpr auto mst() const noexcept -> decltype(auto) {
        return (this->mst_);
    }

    constexpr auto level() const noexcept -> decltype(auto) {
        return (this->level_);
    }

    constexpr auto aircraft_level() const noexcept -> decltype(auto) {
        return (this->aircraft_level_);
    }

   private:
    /// @brief 装備マスタ.
    const kcv::kcsapi::api_mst_slotitem_value_t& mst_;

    /// @brief 改修値.
    std::int32_t level_;

    /// @brief 熟練度.
    std::int32_t aircraft_level_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_DATA_EQUIPMENT_HPP_INCLUDED
