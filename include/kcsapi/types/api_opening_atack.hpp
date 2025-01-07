#ifndef KCVERIFY_KCSAPI_TYPES_API_OPENING_ATACK_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_API_OPENING_ATACK_HPP_INCLUDED

#include <optional>
#include <vector>

namespace kcv {
namespace kcsapi {

/// @brief 開幕雷撃戦.
struct api_opening_atack final {
    std::vector<double> api_edam;
    std::vector<double> api_fdam;
    std::vector<std::optional<std::vector<int>>> api_frai_list_items;
    std::vector<std::optional<std::vector<int>>> api_fcl_list_items;
    std::vector<std::optional<std::vector<int>>> api_fydam_list_items;
    std::vector<std::optional<std::vector<int>>> api_erai_list_items;
    std::vector<std::optional<std::vector<int>>> api_ecl_list_items;
    std::vector<std::optional<std::vector<int>>> api_eydam_list_items;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_API_OPENING_ATACK_HPP_INCLUDED
