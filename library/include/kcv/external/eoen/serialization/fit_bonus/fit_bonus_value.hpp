#ifndef KCV_EXTERNAL_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_VALUE_HPP_INCLUDED
#define KCV_EXTERNAL_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_VALUE_HPP_INCLUDED

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
};

}  // namespace fit_bonus
}  // namespace serialization
}  // namespace eoen
}  // namespace kcv

#endif  // KCV_EXTERNAL_EOEN_SERIALIZATION_FIT_BONUS_FIT_BONUS_VALUE_HPP_INCLUDED
