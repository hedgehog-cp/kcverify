#ifndef KCV_EXTERNAL_KCSAPI_API_REQ_MAP_START_AIR_BASE_REQUEST_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_API_REQ_MAP_START_AIR_BASE_REQUEST_HPP_INCLUDED

#include <optional>
#include <string>

namespace kcv {
namespace kcsapi {
namespace api_req_map {
namespace start_air_base {

/// @brief api_req_map/start_air_base.json
struct request final {
    /// @brief 第一航空隊の攻撃対象のセルIDのコンマ区切りの配列. 出撃札の場合に存在する. "13,13"のような値.
    std::optional<std::string> api_strike_point_1;

    /// @brief 第二航空隊の攻撃対象のセルIDのコンマ区切りの配列. 出撃札の場合に存在する. "13,13"のような値.
    std::optional<std::string> api_strike_point_2;

    /// @brief 第三航空隊の攻撃対象のセルIDのコンマ区切りの配列. 出撃札の場合に存在する. "13,13"のような値.
    std::optional<std::string> api_strike_point_3;

    std::string api_verno;
};

}  // namespace start_air_base
}  // namespace api_req_map
}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_API_REQ_MAP_START_AIR_BASE_REQUEST_HPP_INCLUDED
