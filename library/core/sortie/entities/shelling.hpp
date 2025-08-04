#ifndef KCVERIFY_CORE_SORTIE_ENTITIES_SHELLING_HPP_INCLUDED
#define KCVERIFY_CORE_SORTIE_ENTITIES_SHELLING_HPP_INCLUDED

#include <chrono>
#include <cstdint>
#include <optional>

#include "core/sortie/entities/ship.hpp"
#include "models/kcsapi/types/enum/engagement.hpp"
#include "models/kcsapi/types/enum/formation.hpp"

namespace kcv {
namespace sortie {

struct shelling final {
    /// @brief No.

    /// @brief 日付.
    std::optional<std::chrono::sys_seconds> date;

    /// @brief 海域.
    /// @brief マス.
    /// @brief 出撃.
    /// @brief ランク.
    /// @brief 敵艦隊.
    /// @brief 提督レベル.

    /// @brief 自陣形.
    kcv::kcsapi::formation fformation;

    /// @brief 敵陣形.
    kcv::kcsapi::formation eformation;

    /// @brief 自索敵.
    /// @brief 敵索敵.
    /// @brief 制空権.

    /// @brief 会敵.
    kcv::kcsapi::engagement engagement;

    /// @brief 自触接.
    /// @brief 敵触接.
    /// @brief 自照明弾.
    /// @brief 敵照明弾.
    /// @brief 戦闘種別.
    /// @brief 艦名1.
    /// @brief 艦名2.
    /// @brief 艦名3.
    /// @brief 艦名4.
    /// @brief 艦名5.
    /// @brief 艦名6.
    /// @brief 自艦隊.
    /// @brief 巡目.

    /// @brief 攻撃艦.
    /// 自軍 | 敵軍.

    /// @brief 砲撃種別.
    /// @brief 砲撃回数.
    /// @brief 表示装備1.
    /// @brief 表示装備2.
    /// @brief 表示装備3.
    /// @brief クリティカル.
    std::int32_t critical;

    /// @brief ダメージ.
    std::int32_t damage;

    /// @brief かばう.
    bool protect;

    /// @brief 攻撃艦.
    kcv::sortie::ship attacker;

    /// @brief 攻撃艦.
    kcv::sortie::ship defender;

    /// @brief 艦隊種類.
    /// @brief 敵艦隊種類.
    /// @brief 煙幕レベル.
    /// @brief 阻塞気球マス.
    /// @brief 自気球隻数.
    /// @brief 敵気球隻数.
    /// @brief 装甲破砕.
};

}  // namespace sortie
}  // namespace kcv

#endif  // KCVERIFY_CORE_SORTIE_ENTITIES_SHELLING_HPP_INCLUDED
