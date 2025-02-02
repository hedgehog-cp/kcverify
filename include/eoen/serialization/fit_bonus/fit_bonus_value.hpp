#ifndef KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_VALUE_HPP_INCLUDED
#define KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_VALUE_HPP_INCLUDED

#include <compare>

namespace kcv {
namespace eoen {
namespace serialization {
namespace fit_bonus {

struct fit_bonus_value final {
    /// @brief 火力
    int houg = 0;

    /// @brief 対空
    int tyku = 0;

    /// @brief 回避
    int kaih = 0;

    /// @brief 装甲
    int souk = 0;

    /// @brief 命中
    int houm = 0;

    /// @brief 対潜
    int tais = 0;

    /// @brief 雷撃
    int raig = 0;

    /// @brief 索敵
    int saku = 0;

    /// @brief 射程
    int leng = 0;

    /// @brief 爆装
    int baku = 0;

   private:
    using this_type = fit_bonus_value;

    friend constexpr auto operator<=>(const this_type& lhs, const this_type& rhs) -> std::strong_ordering = default;

    friend constexpr auto operator+(const this_type& lhs, const this_type& rhs) -> this_type {
        return this_type{
            .houg = lhs.houg + rhs.houg,
            .tyku = lhs.tyku + rhs.tyku,
            .kaih = lhs.kaih + rhs.kaih,
            .souk = lhs.souk + rhs.souk,
            .houm = lhs.houm + rhs.houm,
            .tais = lhs.tais + rhs.tais,
            .raig = lhs.raig + rhs.raig,
            .saku = lhs.saku + rhs.saku,
            .leng = lhs.leng + rhs.leng,
            .baku = lhs.baku + rhs.baku,
        };
    }

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
