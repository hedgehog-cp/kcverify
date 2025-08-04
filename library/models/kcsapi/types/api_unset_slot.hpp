#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_API_UNSET_SLOT_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_API_UNSET_SLOT_HPP_INCLUDED

#include <cstdint>
#include <vector>

namespace kcv {
namespace kcsapi {

struct api_unset_slot final {
    /// @brief 装備IDリスト [].
    std::vector<std::int32_t> api_slot_list;

    /// @brief 装備カテゴリID.
    std::int32_t api_type3No;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_API_UNSET_SLOT_HPP_INCLUDED
