#ifndef KCV_DOMAIN_VERIFICATION_ENTITY_EQUIPMENT_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_ENTITY_EQUIPMENT_HPP_INCLUDED

// std
#include <cstdint>

// kcv
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"

namespace kcv {

class equipment final {
   public:
    equipment(
        const kcv::kcsapi::api_mst_slotitem_value_t& mst,
        std::int32_t level,
        std::int32_t aircraft_level
    ) noexcept
        : mst_{mst}
        , level_{level}
        , aircraft_level_{aircraft_level} {}

    auto mst() const noexcept -> const kcv::kcsapi::api_mst_slotitem_value_t& {
        return this->mst_;
    }

    auto level() const noexcept -> std::int32_t {
        return this->level_;
    }

    auto aircraft_level() const noexcept -> std::int32_t {
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

}  // namespace kcv

#endif  // KCV_DOMAIN_VERIFICATION_ENTITY_EQUIPMENT_HPP_INCLUDED
