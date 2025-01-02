#ifndef KCVERIFY_kcsapi_API_REQ_MAP_START_REQUEST_HPP_INCLUDED
#define KCVERIFY_kcsapi_API_REQ_MAP_START_REQUEST_HPP_INCLUDED

#include <string>

namespace kcv {
namespace kcsapi {
namespace api_req_map {
namespace start {

/// @brief api_req_map/start.json
struct request final {
    /// @brief 出撃艦隊ID.
    std::string api_deck_id;

    /// @brief 海域カテゴリID.
    std::string api_maparea_id;

    /// @brief 海域カテゴリ内番号
    std::string api_mapinfo_no;

    std::string api_serial_cid;
    std::string api_verno;
};

}  // namespace start
}  // namespace api_req_map
}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_kcsapi_API_REQ_MAP_START_REQUEST_HPP_INCLUDED
