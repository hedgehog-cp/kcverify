#ifndef KCVERIFY_MODELS_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_DATA_HPP_INCLUDED
#define KCVERIFY_MODELS_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_DATA_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "models/eoen/serialization/fit_bonus/fit_bonus_value.hpp"
#include "models/kcsapi/types/enum/category.hpp"
#include "models/kcsapi/types/enum/ctype.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"
#include "models/kcsapi/types/enum/nationality.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"
#include "models/kcsapi/types/enum/stype.hpp"

namespace kcv {
namespace eoen {
namespace serialization {
namespace fit_bonus {

struct fit_bonus_data final {
    /// @brief 艦船条件. 未改造ID.
    std::optional<std::vector<kcv::kcsapi::ship_id>> original_id;

    /// @brief 艦船条件. 艦型.
    std::optional<std::vector<kcv::kcsapi::ctype>> ship_class;

    /// @brief 艦船条件. 艦籍.
    std::optional<std::vector<kcv::kcsapi::nationality>> nationality;

    /// @brief 艦船条件. 艦種.
    std::optional<std::vector<kcv::kcsapi::stype>> ship_type;

    /// @brief 艦船条件. 艦船ID.
    std::optional<std::vector<kcv::kcsapi::ship_id>> ship_id;

    /// @brief 装備ID条件. 装備ID.
    std::optional<std::vector<kcv::kcsapi::equipment_id>> requires_id;

    /// @brief 装備ID条件. 改修値.
    std::optional<std::int32_t> requires_level;

    /// @brief 装備ID条件. 搭載数.
    std::optional<std::int32_t> requires_num;

    /// @brief 装備カテゴリ条件. カテゴリID.
    std::optional<std::vector<kcv::kcsapi::category>> requires_type;

    /// @brief 装備カテゴリ条件. 搭載数.
    std::optional<std::int32_t> requires_num_type;

    /// @brief 装備条件. 改修値
    std::optional<std::int32_t> level;

    /// @brief 装備条件. 搭載数.
    std::optional<std::int32_t> num;

    /// @brief ボーナス.
    std::optional<kcv::eoen::serialization::fit_bonus::fit_bonus_value> bonus;

    /// @brief 対空電探が要求されるボーナス.
    std::optional<kcv::eoen::serialization::fit_bonus::fit_bonus_value> bonus_if_anti_air_radar;

    /// @brief 命中電探が要求されるボーナス.
    std::optional<kcv::eoen::serialization::fit_bonus::fit_bonus_value> bonus_if_accuracy_radar;

    /// @brief 水上電探が要求されるボーナス.
    std::optional<kcv::eoen::serialization::fit_bonus::fit_bonus_value> bonus_if_surface_radar;
};

}  // namespace fit_bonus
}  // namespace serialization
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_MODELS_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_DATA_HPP_INCLUDED
