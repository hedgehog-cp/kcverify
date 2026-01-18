#ifndef KCV_EXTERNAL_KCSAPI_TYPES_SVDATA_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_SVDATA_HPP_INCLUDED

#include <cstdint>
#include <string>

namespace kcv {
namespace kcsapi {

template <typename Response>
struct svdata final {
    /// @brief response
    Response api_data;

    /// @brief 1
    std::int32_t api_result;

    /// @brief "成功"
    std::string api_result_msg;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_SVDATA_HPP_INCLUDED
