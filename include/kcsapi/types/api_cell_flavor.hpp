#ifndef KCVERIFY_kcsapi_TYPES_API_CELL_FLAVOR_HPP_INCLUDED
#define KCVERIFY_kcsapi_TYPES_API_CELL_FLAVOR_HPP_INCLUDED

#include <string>

namespace kcv {
namespace kcsapi {

/// @brief セル到達時のフレーバーテキスト.
struct api_cell_flavor final {
    /// @brief メッセージ.
    std::string api_message;

    /// @brief 0=気のせいだった, 1=静かな海です.
    int api_type;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_kcsapi_TYPES_API_CELL_FLAVOR_HPP_INCLUDED
