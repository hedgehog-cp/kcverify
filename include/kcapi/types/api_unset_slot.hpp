#ifndef KCVERIFY_KCAPI_TYPES_API_UNSET_SLOT_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_UNSET_SLOT_HPP_INCLUDED

#include <vector>

namespace kcv {
namespace kcapi {

struct api_unset_slot final {
    /// @brief 装備IDリスト [].
    std::vector<int> api_slot_list;

    /// @brief 装備カテゴリID.
    int api_type3No;
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_UNSET_SLOT_HPP_INCLUDED