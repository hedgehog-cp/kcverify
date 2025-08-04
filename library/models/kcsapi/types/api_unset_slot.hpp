#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_UNSET_SLOT_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_UNSET_SLOT_HPP_INCLUDED

#include <vector>

namespace kcv {
namespace kcsapi {

struct api_unset_slot final {
    /// @brief 装備IDリスト [].
    std::vector<int> api_slot_list;

    /// @brief 装備カテゴリID.
    int api_type3No;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_UNSET_SLOT_HPP_INCLUDED
