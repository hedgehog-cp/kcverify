#ifndef KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_DATA_HPP_INCLUDED
#define KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_DATA_HPP_INCLUDED

// std
#include <optional>
#include <vector>

// kcv
#include "eoen/serialization/fit_bonus/fit_bonus_value.hpp"
#include "kcsapi/types/enum/category.hpp"
#include "kcsapi/types/enum/ctype.hpp"
#include "kcsapi/types/enum/equipment_id.hpp"
#include "kcsapi/types/enum/nationality.hpp"
#include "kcsapi/types/enum/ship_id.hpp"
#include "kcsapi/types/enum/stype.hpp"

namespace kcv {
namespace eoen {
namespace serialization {
namespace fit_bonus {

struct fit_bonus_data final {
    std::optional<std::vector<kcv::kcsapi::stype>> ship_type;
    std::optional<int> level;
    std::optional<int> num;
    std::optional<fit_bonus_value> bonus;
    std::optional<std::vector<kcv::kcsapi::ship_id>> ship_id;
    std::optional<fit_bonus_value> air_radar;
    std::optional<std::vector<kcv::kcsapi::ship_id>> original_id;
    std::optional<std::vector<kcv::kcsapi::equipment_id>> requires_id;
    std::optional<int> requires_level;
    std::optional<int> requires_num;
    std::optional<std::vector<kcv::kcsapi::category>> requires_type;
    std::optional<int> requires_num_type;
    std::optional<std::vector<kcv::kcsapi::ctype>> ship_class;
    std::optional<fit_bonus_value> surface_radar;
    std::optional<std::vector<kcv::kcsapi::nationality>> nationality;
    std::optional<fit_bonus_value> accuracy_radar;
};

}  // namespace fit_bonus
}  // namespace serialization
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_DATA_HPP_INCLUDED
