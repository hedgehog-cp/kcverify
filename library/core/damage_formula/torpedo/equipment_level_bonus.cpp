#include "core/damage_formula/torpedo/equipment_level_bonus.hpp"

// std
#include <cmath>
#include <cstdint>

// kcv
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "stdfloat.hpp"

namespace {

namespace impl = kcv::damage_formulae::torpedo;

}  // namespace

// clang-format off

auto impl::equipment_level_bonus(const kcv::kcsapi::api_mst_slotitem_value_t& mst, std::int32_t level) -> kcv::float64_t {
    const auto& category = std::get<kcv::kcsapi::idx_type::category>(mst.api_type);

    switch (category) {
        case kcv::kcsapi::category::torpedo:
        case kcv::kcsapi::category::aa_gun:
            return 1.2 * std::sqrt(level);

        case kcv::kcsapi::category::submarine_torpedo:
            return 1.0 * level;

        default:
            return 0.0;
    }
}

// clang-format on