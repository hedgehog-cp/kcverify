#ifndef KCVERIFY_MODELS_KC3KAI_KANCOLLE_REPLAY_JS_DATA_BONUS_BONUS_HPP_INCLUDED
#define KCVERIFY_MODELS_KC3KAI_KANCOLLE_REPLAY_JS_DATA_BONUS_BONUS_HPP_INCLUDED

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "models/kcsapi/types/enum/ship_id.hpp"
#include "models/kcsapi/types/enum/stype.hpp"

namespace kcv {
namespace kc3kai {

struct bonus_bonus_t final {
    std::optional<double> dmg;
    std::optional<double> acc;
    std::optional<double> eva;
    std::optional<std::vector<kcv::kcsapi::ship_id>> ship_base;
    std::optional<std::vector<kcv::kcsapi::stype>> ship_type;
    std::optional<std::vector<std::int32_t>> ship_class;
    std::optional<std::vector<std::int32_t>> ship_id;
    std::optional<std::int32_t> is_plane;
    std::optional<std::int32_t> not_air_only;
    std::optional<std::int32_t> basewide;
    std::optional<std::vector<std::int32_t>> require_equip_id;
    std::optional<std::vector<std::int32_t>> require_equip_type;
    std::optional<std::int32_t> per_equip;
    std::optional<std::int32_t> require_equip_id_num_x;
    std::optional<std::int32_t> require_equip_id_num;
    std::optional<std::int32_t> require_equip_level;
    std::optional<std::vector<std::int32_t>> require_equip_id_not;
    std::optional<std::int32_t> unconfirmed;
};

struct bonus_bonus_group_t final {
    std::optional<std::vector<std::string>> nodes;
    std::optional<std::vector<std::string>> nodes_exclude;
    std::vector<bonus_bonus_t> bonuses;
};

struct bonus_debuff_t final {
    std::optional<std::vector<std::int32_t>> ship_id;
    std::optional<std::int32_t> amount;
};

struct bonus_debuff_group_t final {
    std::optional<std::vector<std::string>> nodes;
    std::vector<bonus_debuff_t> debuffs;
};

struct bonus_map_t final {
    std::int32_t world;
    std::int32_t mapnum;
    std::optional<std::string> date;
    std::optional<std::string> note;
    std::vector<bonus_bonus_group_t> list_bonus;
    std::optional<std::vector<bonus_bonus_group_t>> list_bonus_lbas;
    std::optional<std::vector<bonus_debuff_group_t>> list_debuff;
};

}  // namespace kc3kai
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KC3KAI_KANCOLLE_REPLAY_JS_DATA_BONUS_BONUS_HPP_INCLUDED
