#ifndef KCVERIFY_CORE_SORTIE_ENTITIES_EQUIPMENT_HPP_INCLUDED
#define KCVERIFY_CORE_SORTIE_ENTITIES_EQUIPMENT_HPP_INCLUDED

// std
#include <cstdint>

// kcv
#include "core/common/kcsapi.hpp"
#include "models/eoen/database/sortie/sortie_equipment.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"

namespace kcv {
namespace sortie {

/// @brief 装備.
class equipment final {
   public:
    using eoen_type = kcv::eoen::database::sortie::sortie_equipment;

    static auto from_eoen(const eoen_type& src, const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem) -> equipment {
        return equipment{
            kcv::binary_search(api_mst_slotitem, src.id),
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
        , level_{level}
        , aircraft_level_{aircraft_level} {}

    // clang-format on

    constexpr auto mst() const noexcept -> const kcv::kcsapi::api_mst_slotitem_value_t& {
        return this->mst_;
    }

    constexpr auto level() const noexcept -> std::int32_t {
        return this->level_;
    }

    constexpr auto aircraft_level() const noexcept -> std::int32_t {
        return this->aircraft_level_;
    }

   private:
    /// @brief 装備マスタ.
    const kcv::kcsapi::api_mst_slotitem_value_t& mst_;

    /// @brief 改修値.
    std::int32_t level_;

    /// @brief 熟練度.
    std::int32_t aircraft_level_;
};

}  // namespace sortie
}  // namespace kcv

#endif  // KCVERIFY_CORE_SORTIE_ENTITIES_EQUIPMENT_HPP_INCLUDED
