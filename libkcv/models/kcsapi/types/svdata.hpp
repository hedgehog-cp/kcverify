#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_SVDATA_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_SVDATA_HPP_INCLUDED

#include <string>

namespace kcv {
namespace kcsapi {

template <typename Response>
struct svdata final {
    /// @brief response
    Response api_data;

    /// @brief 1
    int api_result;

    /// @brief "成功"
    std::string api_result_msg;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_SVDATA_HPP_INCLUDED
