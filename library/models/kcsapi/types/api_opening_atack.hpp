#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_OPENING_ATACK_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_OPENING_ATACK_HPP_INCLUDED

#include <cstdint>
#include <optional>
#include <vector>

namespace kcv {
namespace kcsapi {

/// @brief 開幕雷撃戦.
struct api_opening_atack final {
    std::vector<double> api_edam;
    std::vector<double> api_fdam;
    std::vector<std::optional<std::vector<std::int32_t>>> api_frai_list_items;
    std::vector<std::optional<std::vector<std::int32_t>>> api_fcl_list_items;
    std::vector<std::optional<std::vector<std::int32_t>>> api_fydam_list_items;
    std::vector<std::optional<std::vector<std::int32_t>>> api_erai_list_items;
    std::vector<std::optional<std::vector<std::int32_t>>> api_ecl_list_items;
    std::vector<std::optional<std::vector<std::int32_t>>> api_eydam_list_items;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_OPENING_ATACK_HPP_INCLUDED
