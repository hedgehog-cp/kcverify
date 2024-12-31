#ifndef KCVERIFY_kcsapi_TYPES_API_FLAVOR_INFO_HPP_INCLUDED
#define KCVERIFY_kcsapi_TYPES_API_FLAVOR_INFO_HPP_INCLUDED

#include <string>

namespace kcv {
namespace kcsapi {

/// @brief 敵ボス艦の情報とフレーバーテキスト. [1].
struct api_flavor_info final {
    /// @brief 艦固有ID.
    std::string api_boss_ship_id;

    /// @brief 艦型名.
    std::string api_class_name;

    /// @brief グラフィック状態文字列. ""=一般状態. "d"=装甲破砕状態.
    std::string api_data;

    /// @brief 登場時のセリフのテキスト.
    std::string api_message;

    /// @brief グラフィック表示X座標.
    std::string api_pos_x;

    /// @brief グラフィック表示Y座標.
    std::string api_pos_y;

    /// @brief 艦名.
    std::string api_ship_name;

    /// @brief 艦種ID. stype.
    std::string api_type;

    /// @brief 再生されるvoiceファイル名.
    std::string api_voice_id;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_kcsapi_TYPES_API_FLAVOR_INFO_HPP_INCLUDED
