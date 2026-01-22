#ifndef KCV_EXTERNAL_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_PER_EQUIPMENT_HPP_INCLUDED
#define KCV_EXTERNAL_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_PER_EQUIPMENT_HPP_INCLUDED

// std
#include <optional>
#include <vector>

// kcv
#include "kcv/external/eoen/serialization/fit_bonus/fit_bonus_data.hpp"
#include "kcv/external/kcsapi/types/enum/category.hpp"
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"

namespace kcv {
namespace eoen {
namespace serialization {
namespace fit_bonus {

struct fit_bonus_per_equipment final {
    /// @brief カテゴリID条件.
    std::optional<std::vector<kcv::kcsapi::category>> types;

    /// @brief 装備ID条件.
    std::optional<std::vector<kcv::kcsapi::equipment_id>> ids;

    /// @brief ボーナス.
    std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_data> bonuses;
};

}  // namespace fit_bonus
}  // namespace serialization
}  // namespace eoen
}  // namespace kcv

#endif  // KCV_EXTERNAL_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_PER_EQUIPMENT_HPP_INCLUDED
