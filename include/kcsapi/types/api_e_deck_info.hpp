#ifndef KCVERIFY_kcsapi_TYPES_API_E_DECK_INFO_HPP_INCLUDED
#define KCVERIFY_kcsapi_TYPES_API_E_DECK_INFO_HPP_INCLUDED

// std
#include <vector>

// kcv
#include "kcsapi/types/enum/ship_id.hpp"

namespace kcv {
namespace kcsapi {

/// @brief 敵艦隊陣容のある程度の確認.
/// 航空戦と空襲戦(第6海域除く)には存在しない. 払暁戦とレーダー射撃戦は不明.
/// @see https://x.com/KanColle_STAFF/status/1650065368633999360
/// @see https://x.com/KanColle_STAFF/status/1650067282788495362
struct api_e_deck_info_value_type final {
    /// @brief 敵艦隊最大枠数の種類, 1=4枠, 2=5枠, 0=以下の艦船数と同じ枠
    int api_kind;

    /// @brief [表示艦船数]. 実際出現する敵艦隊は3隻より多い場合, 空き枠を増やして先頭3隻のみ表示.
    std::vector<ship_id> api_ship_ids;
};

/// @brief 敵艦隊陣容のある程度の確認.
/// 対通常艦隊のとき[1], 対連合艦隊のとき[2].
using api_e_deck_info = std::vector<api_e_deck_info_value_type>;

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_kcsapi_TYPES_API_E_DECK_INFO_HPP_INCLUDED
