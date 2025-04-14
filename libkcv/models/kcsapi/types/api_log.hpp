#ifndef KCVERIFY_KCSAPI_TYPES_API_LOG_HPP_INCLUDED
#define KCVERIFY_KCSAPI_TYPES_API_LOG_HPP_INCLUDED

#include <string>

namespace kcv {
namespace kcsapi {

/// @brief 母港下の通知欄.
struct api_log final {
    /// @brief メッセージ.
    std::string api_message;

    /// @brief 通し番号.
    int api_no;

    /// @brief
    std::string api_state;

    /// @brief 通知タイプ.
    /// 1から 入渠, 工廠, 遠征, 支給?, 演習, 勲章?, 出撃, 任務?, 申請?, 昇格?, 図鑑, 達成?, 改造?
    std::string api_type;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_KCSAPI_TYPES_API_LOG_HPP_INCLUDED
