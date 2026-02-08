#ifndef KCV_DOMAIN_VERIFICATION_LOGIC_LOGIC_HPP_INCLUDED
#define KCV_DOMAIN_VERIFICATION_LOGIC_LOGIC_HPP_INCLUDED

// 基本的に, 以下のような広範囲に使える型を引数とする, 汎用的な関数を提供する.
//  - `kcv::kcsapi::api_mst_ship_value_t`
//  - `kcv::kcsapi::api_mst_slotitem_value_t`
//  - `kcv::battlelog`
//  - `kcv::ship`
// 引数の個数は一つまたは二つ程度にとどめる. ただし, 静的な可変長引数の場合はこの限りではない.

// std
#include <algorithm>
#include <concepts>
#include <functional>
#include <ranges>
#include <utility>
#include <variant>

// kcv
#include "kcv/core/constants/ship_attributes.hpp"
#include "kcv/domain/verification/battlelog/battlelog.hpp"
#include "kcv/domain/verification/battlelog/battlelog_accessor.hpp"
#include "kcv/domain/verification/entity/ship.hpp"
#include "kcv/domain/verification/entity/slot.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcv/external/kcsapi/types/enum/air_hit_type.hpp"
#include "kcv/external/kcsapi/types/enum/equipment_id.hpp"
#include "kcv/std_ext/utility.hpp"

namespace kcv {

namespace ranges {
namespace views {

/// @brief 装備を搭載しているスロットにフィルタリングする.
inline constexpr auto with_equipment = std::ranges::views::filter([](const kcv::slot& slot) static noexcept -> bool {
    return slot.equipment().has_value();
});

}  // namespace views
}  // namespace ranges

namespace views = ranges::views;

/// @brief 艦船が述語を満たす装備を搭載しているならばtrueを返す.
/// @tparam Pred 装備マスタを引数にとる単項述語関数.
/// @param ship 艦船.
/// @param pred 装備マスタを引数にとる単項述語関数.
template <typename Pred>
    requires std::predicate<Pred, const kcv::kcsapi::api_mst_slotitem_value_t&>
bool has_equipment(const kcv::ship& ship, Pred&& pred) noexcept {
    for (const auto& slot : ship.slots() | kcv::ranges::views::with_equipment) {
        if (std::invoke(std::forward<Pred>(pred), slot.equipment()->mst())) {
            return true;
        }
    }
    return false;
}

/// @brief 艦船が装備IDに一致する装備を搭載しているならばtrueを返す.
/// @param ship 艦船.
/// @param id 装備ID.
inline bool has_equipment(const kcv::ship& ship, kcv::kcsapi::equipment_id id) noexcept {
    for (const auto& slot : ship.slots() | kcv::ranges::views::with_equipment) {
        if (slot.equipment()->mst().api_id == id) {
            return true;
        }
    }
    return false;
}

/// @brief 艦船がカテゴリIDに一致する装備を搭載しているならばtrueを返す.
/// @param ship 艦船.
/// @param category カテゴリID.
inline bool has_equipment(const kcv::ship& ship, kcv::kcsapi::category category) noexcept {
    for (const auto& slot : ship.slots() | kcv::ranges::views::with_equipment) {
        if (std::get<kcv::kcsapi::category>(slot.equipment()->mst().api_type) == category) {
            return true;
        }
    }
    return false;
}

/// @brief 艦船がカテゴリIDに一致する装備を搭載しているならばtrueを返す.
/// @param ship 艦船.
/// @param categories カテゴリID.
inline bool has_equipment(const kcv::ship& ship, std::initializer_list<kcv::kcsapi::category> categories) noexcept {
    for (const auto& slot : ship.slots() | kcv::ranges::views::with_equipment) {
        if (std::ranges::contains(categories, std::get<kcv::kcsapi::category>(slot.equipment()->mst().api_type))) {
            return true;
        }
    }
    return false;
}

/// @brief 艦船がアイコンIDに一致する装備を搭載しているならばtrueを返す.
/// @param ship 艦船.
/// @param アイコンID.
inline bool has_equipment(const kcv::ship& ship, kcv::kcsapi::icon icon) noexcept {
    for (const auto& slot : ship.slots() | kcv::ranges::views::with_equipment) {
        if (std::get<kcv::kcsapi::icon>(slot.equipment()->mst().api_type) == icon) {
            return true;
        }
    }
    return false;
}

/// @brief 艦船が, 機数>0かつ述語を満たす装備を搭載しているならばtrueを返す.
/// @tparam Pred 装備マスタを引数にとる単項述語関数.
/// @param ship 艦船.
/// @param pred 装備マスタを引数にとる単項述語関数.
template <typename Pred>
    requires std::predicate<Pred, const kcv::kcsapi::api_mst_slotitem_value_t&>
bool has_available_plane(const kcv::ship& ship, Pred&& pred) noexcept {
    for (const auto& slot : ship.slots() | kcv::ranges::views::with_equipment) {
        if (slot.aircraft_current() > 0 and std::invoke(std::forward<Pred>(pred), slot.equipment()->mst())) {
            return true;
        }
    }
    return false;
}

/// @brief 艦船が搭載している装備のうち, 述語を満たす装備の搭載数を数え上げる.
/// @tparam Pred 装備マスタを引数にとる単項述語関数.
/// @param ship 艦船.
/// @param pred 装備マスタを引数にとる単項述語関数.
template <typename Pred>
    requires std::predicate<Pred, const kcv::kcsapi::api_mst_slotitem_value_t&>
int count_equipment(const kcv::ship& ship, Pred&& pred) noexcept {
    int count = 0;

    for (const auto& slot : ship.slots() | kcv::ranges::views::with_equipment) {
        if (std::invoke(std::forward<Pred>(pred), slot.equipment()->mst())) {
            count++;
        }
    }

    return count;
}

/// @brief 艦船が搭載している装備のうち, 装備IDが一致する装備の搭載数を数え上げる.
/// @param ship 艦船.
/// @param id 装備ID.
inline int count_equipment(const kcv::ship& ship, kcv::kcsapi::equipment_id id) noexcept {
    int count = 0;

    for (const auto& slot : ship.slots() | kcv::ranges::views::with_equipment) {
        if (slot.equipment()->mst().api_id == id) {
            count++;
        }
    }

    return count;
}

/// @brief 艦船が搭載している装備のうち, カテゴリIDが一致する装備の搭載数を数え上げる.
/// @param ship 艦船.
/// @param category カテゴリID.
inline int count_equipment(const kcv::ship& ship, kcv::kcsapi::category category) noexcept {
    int count = 0;

    for (const auto& slot : ship.slots() | kcv::ranges::views::with_equipment) {
        if (std::get<kcv::kcsapi::category>(slot.equipment()->mst().api_type) == category) {
            count++;
        }
    }

    return count;
}

/// @brief 急所弾であるかを検証する.
inline bool is_critical(const kcv::battlelog& data) noexcept {
    return std::visit(
        kcv::overloaded{
            [](std::int32_t v) static noexcept -> bool { return v == 2; },
            [](kcv::kcsapi::air_hit_type v) static noexcept -> bool {
                return v == kcv::kcsapi::air_hit_type::cLitical;
            },
        },
        data.clitical
    );
}

/// @brief 対潜戦闘の攻撃方法を分類する.
/// @return 爆雷攻撃ならば13, 航空攻撃ならば8, その他対潜戦闘でないなどであれば0を返す.
/// HACK: 局所的なenumの定義を回避するためint型を返す. この値は最低保証火力に直接使える.
int classify_asw_operation(const kcv::battlelog& data);

/// @brief 夜間航空攻撃であるかを検証する.
/// @details 以下の条件を全て満たすとき, trueを返す.
/// - 夜間戦闘である.
/// - 対潜戦闘でない.
/// - 攻撃艦が夜間作戦可能な空母である.
/// - 攻撃艦が装甲空母であるまたは攻撃艦の損傷が小破以下である.
/// - 夜間機が残存している.
bool is_night_air_attack(const kcv::battlelog& data);

}  // namespace kcv

#endif  // KCV_DOMAIN_VERIFICATION_LOGIC_LOGIC_HPP_INCLUDED
