#ifndef KCVERIFY_KCAPI_TYPES_API_ENEMY_INFO_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_ENEMY_INFO_HPP_INCLUDED

#include <string>

namespace kcv {
namespace kcapi {

/// @brief 敵艦隊情報.
struct api_enemy_info final {
    /// @brief 敵艦隊名.
    std::string api_deck_name;

    std::string api_level;
    std::string api_rank;
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_ENEMY_INFO_HPP_INCLUDED
