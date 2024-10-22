#ifndef KCVERIFY_KCAPI_TYPES_SVDATA_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_SVDATA_HPP_INCLUDED

#include <string>

namespace kcv {
namespace kcapi {

template <typename Response>
struct svdata final {
    /// @brief response
    Response api_data;

    /// @brief 1
    int api_result;

    /// @brief "成功"
    std::string api_result_msg;
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_SVDATA_HPP_INCLUDED
