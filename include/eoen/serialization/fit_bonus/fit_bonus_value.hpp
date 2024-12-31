#ifndef KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_VALUE_HPP_INCLUDED
#define KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_VALUE_HPP_INCLUDED

namespace kcv {
namespace eoen {
namespace serialization {
namespace fit_bonus {

struct fit_bonus_value final {
    int houg = 0;
    int tyku = 0;
    int kaih = 0;
    int souk = 0;
    int houm = 0;
    int tais = 0;
    int raig = 0;
    int saku = 0;
    int leng = 0;
    int baku = 0;

   private:
    using this_type = fit_bonus_value;

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

    friend constexpr auto operator*(int lhs, const this_type& rhs) -> this_type {
        return this_type{
            .houg = lhs * rhs.houg,
            .tyku = lhs * rhs.tyku,
            .kaih = lhs * rhs.kaih,
            .souk = lhs * rhs.souk,
            .houm = lhs * rhs.houm,
            .tais = lhs * rhs.tais,
            .raig = lhs * rhs.raig,
            .saku = lhs * rhs.saku,
            .leng = lhs * rhs.leng,
            .baku = lhs * rhs.baku,
        };
    }
};

}  // namespace fit_bonus
}  // namespace serialization
}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_VALUE_HPP_INCLUDED
