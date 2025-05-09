#ifndef KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_VALUE_HPP_INCLUDED
#define KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_VALUE_HPP_INCLUDED

#include <compare>
#include <cstdint>

namespace kcv {
namespace eoen {
namespace serialization {
namespace fit_bonus {

struct fit_bonus_value final {
    /// @brief 火力.
    std::int32_t houg = 0;

    /// @brief 対空.
    std::int32_t tyku = 0;

    /// @brief 回避.
    std::int32_t kaih = 0;

    /// @brief 装甲.
    std::int32_t souk = 0;

    /// @brief 命中.
    std::int32_t houm = 0;

    /// @brief 対潜.
    std::int32_t tais = 0;

    /// @brief 雷撃.
    std::int32_t raig = 0;

    /// @brief 索敵.
    std::int32_t saku = 0;

    /// @brief 射程.
    std::int32_t leng = 0;

    /// @brief 爆装.
    std::int32_t baku = 0;

   private:
    using this_type = fit_bonus_value;

    friend constexpr auto operator<=>(const this_type& lhs, const this_type& rhs) -> std::strong_ordering = default;

    friend constexpr auto operator+=(this_type& lhs, const this_type& rhs) -> this_type& {
        lhs.houg += rhs.houg;
        lhs.tyku += rhs.tyku;
        lhs.kaih += rhs.kaih;
        lhs.souk += rhs.souk;
        lhs.houm += rhs.houm;
        lhs.tais += rhs.tais;
        lhs.raig += rhs.raig;
        lhs.saku += rhs.saku;
        lhs.leng += rhs.leng;
        lhs.baku += rhs.baku;
        return lhs;
    }

    friend constexpr auto operator*(const this_type& lhs, int rhs) -> this_type {
        return this_type{
            .houg = lhs.houg * rhs,
            .tyku = lhs.tyku * rhs,
            .kaih = lhs.kaih * rhs,
            .souk = lhs.souk * rhs,
            .houm = lhs.houm * rhs,
            .tais = lhs.tais * rhs,
            .raig = lhs.raig * rhs,
            .saku = lhs.saku * rhs,
            .leng = lhs.leng * rhs,
            .baku = lhs.baku * rhs,
        };
    }
};

}  // namespace fit_bonus
}  // namespace serialization
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_VALUE_HPP_INCLUDED
