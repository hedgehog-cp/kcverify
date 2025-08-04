#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_TORPEDO_TORPEDO_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_TORPEDO_TORPEDO_HPP_INCLUDED

// std
#include <cstdint>
#include <utility>

// kcv
#include "core/damage_formula/function/composition.hpp"
#include "core/damage_formula/function/liner.hpp"
#include "core/damage_formula/function/softcap.hpp"
#include "stdfloat.hpp"

namespace kcv {
namespace damage_formlulae {
namespace torpedo {

/// @brief 基本攻撃力.
struct base_power final {
    /// @brief 最低保証火力.
    std::int32_t base;

    /// @brief 表示値; 攻撃艦.雷装.
    std::int32_t torpedo;

    /// @brief ??? 熟練甲板要員+航空整備員.ボーナス.
    std::int32_t bonus;

    /// @brief 装備改修基本攻撃力補正の総和.
    kcv::float64_t equipment_level_bonus;

    /// @brief 連合艦隊補正.
    std::int32_t combined_bonus;
};

using formula = decltype(
      std::declval<kcv::mod::liner>()         // 第0種補正
    | std::declval<kcv::mod::liner>()         // 交戦形態補正
    | std::declval<kcv::mod::liner>()         // 攻撃側陣形補正
    | std::declval<kcv::mod::liner>()         // 損傷状態補正
    | std::declval<kcv::mod::liner>()         // 第14種補正
    | std::declval<kcv::mod::softcap>()  // ソフトキャップ
    // 切り捨て
    // 艦種補正
    // 海域補正
    // 期間限定海域
    // 8種
    // PT
    // PT装備
    // CL2
);

}  // namespace torpedo
}  // namespace damage_formlulae
}  // namespace kcv

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_TORPEDO_TORPEDO_HPP_INCLUDED
