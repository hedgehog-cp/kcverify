#ifndef KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_PER_EQUIPMENT_HPP_INCLUDED
#define KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_PER_EQUIPMENT_HPP_INCLUDED

// std
#include <optional>
#include <vector>

// kcv
#include "models/eoen/serialization/fit_bonus/fit_bonus_data.hpp"
#include "models/kcsapi/types/enum/category.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"

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

#endif  // KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_PER_EQUIPMENT_HPP_INCLUDED
