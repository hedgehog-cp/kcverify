#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_CELL_FLAVOR_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_CELL_FLAVOR_HPP_INCLUDED

#include <cstdint>
#include <string>

namespace kcv {
namespace kcsapi {

/// @brief セル到達時のフレーバーテキスト.
struct api_cell_flavor final {
    /// @brief メッセージ.
    std::string api_message;

    /// @brief 0=気のせいだった, 1=静かな海です.
    std::int32_t api_type;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_CELL_FLAVOR_HPP_INCLUDED
