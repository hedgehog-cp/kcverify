#ifndef KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_PER_EQUIPMENT_HPP_INCLUDED
#define KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_PER_EQUIPMENT_HPP_INCLUDED

// std
#include <optional>
#include <vector>

// kcv
#include "eoen/serialization/fit_bonus/fit_bonus_data.hpp"

namespace kcv {
namespace eoen {
namespace serialization {
namespace fit_bonus {

struct fit_bonus_per_equipment final {
    std::optional<std::vector<int>> equipment_types;
    std::optional<std::vector<int>> equipment_ids;
    std::vector<fit_bonus_data> bonuses;
};

}  // namespace fit_bonus
}  // namespace serialization
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_PER_EQUIPMENT_HPP_INCLUDED
