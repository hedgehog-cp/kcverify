#ifndef KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_DATA_HPP_INCLUDED
#define KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_DATA_HPP_INCLUDED

// std
#include <optional>
#include <vector>

// kcv
#include "eoen/serialization/fit_bonus/fit_bonus_value.hpp"
#include "kcapi/types/enum/category.hpp"
#include "kcapi/types/enum/ctype.hpp"
#include "kcapi/types/enum/equipment_id.hpp"
#include "kcapi/types/enum/nationality.hpp"
#include "kcapi/types/enum/ship_id.hpp"
#include "kcapi/types/enum/stype.hpp"

namespace kcv {
namespace eoen {
namespace serialization {
namespace fit_bonus {

struct fit_bonus_data final {
    std::optional<std::vector<kcv::kcapi::stype>> ship_type;
    std::optional<int> level;
    std::optional<int> num;
    std::optional<fit_bonus_value> bonus;
    std::optional<std::vector<kcv::kcapi::ship_id>> ship_id;
    std::optional<fit_bonus_value> air_radar;
    std::optional<std::vector<kcv::kcapi::ship_id>> original_id;
    std::optional<std::vector<kcv::kcapi::equipment_id>> requires_id;
    std::optional<int> requires_level;
    std::optional<int> requires_num;
    std::optional<std::vector<kcv::kcapi::category>> requires_type;
    std::optional<int> requires_num_type;
    std::optional<std::vector<kcv::kcapi::ctype>> ship_class;
    std::optional<fit_bonus_value> surface_radar;
    std::optional<std::vector<kcv::kcapi::nationality>> nationality;
    std::optional<fit_bonus_value> accuracy_radar;
};

}  // namespace fit_bonus
}  // namespace serialization
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_DATA_HPP_INCLUDED
