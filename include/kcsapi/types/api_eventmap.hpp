#ifndef KCVERIFY_kcsapi_TYPES_API_EVENTMAP_HPP_INCLUDED
#define KCVERIFY_kcsapi_TYPES_API_EVENTMAP_HPP_INCLUDED

#include <optional>

namespace kcv {
namespace kcsapi {

/// @brief 期間限定海域ゲージ情報.
struct api_eventmap final {
    /// @brief ゲージ最大値. 未設定時は9999.
    std::optional<int> api_max_maphp;

    /// @brief ゲージ現在値. 未設定時は9999.
    std::optional<int> api_now_maphp;

    /// @brief ダメージ倍率?. =6だとHP90の旗艦撃沈で540減少?
    int api_dmg;

    /// @brief 作戦難易度. 0=未設定, 1=丁, 2=丙, 3=乙, 4=甲.
    int api_selected_rank;

    /// @brief 1=未攻略, 2=攻略済み.
    int api_state;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_kcsapi_TYPES_API_EVENTMAP_HPP_INCLUDED
