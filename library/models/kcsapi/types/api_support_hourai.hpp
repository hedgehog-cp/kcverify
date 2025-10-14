#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_SUPPORT_HOURAI_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_SUPPORT_HOURAI_HPP_INCLUDED

#include <cstdint>
#include <vector>

namespace kcv {
namespace kcsapi {

/// @brief 砲撃もしくは雷撃の時有効. それ以外はnull.
struct api_support_hourai final {
    /// @brief 支援艦隊の艦隊ID.
    std::int32_t api_deck_id;

    /// @brief 支援艦隊の編成艦ID. [6]. マスターIDではないので注意. 不在スロットは0.
    std::vector<std::int32_t> api_ship_id;

    /// @brief 中破フラグ. [6].
    std::vector<std::int32_t> api_undressing_flag;

    /// @brief クリティカルフラグ. [7]. 0=ミス, 1=命中, 2=クリティカル.
    std::vector<std::int32_t> api_cl_list;

    /// @brief 与ダメージ. [7].
    std::vector<double> api_damage;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_SUPPORT_HOURAI_HPP_INCLUDED
