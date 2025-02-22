#ifndef KCVERIFY_SORTIE_MAP_DATA_HPP_INCLUDED
#define KCVERIFY_SORTIE_MAP_DATA_HPP_INCLUDED

// std
#include <cstdint>
#include <utility>

// kcv
#include "eoen/database/sortie/sortie_map_data.hpp"

namespace kcv {

class map_data final {
   public:
    using eoen_type = kcv::eoen::database::sortie::sortie_map_data;

    static constexpr auto from_eoen(const eoen_type& src) noexcept -> map_data {
        return map_data{
            src.required_defeat_count,
            src.map_hp_current,
            src.map_hp_max,
        };
    }

    // clang-format off

    constexpr map_data(
        std::int32_t required_defeated_count,
        std::int32_t map_hp_current,
        std::int32_t map_hp_max
    ) noexcept
        : required_defeated_count_{std::move(required_defeated_count)}
        , map_hp_current_{std::move(map_hp_current)}
        , map_hp_max_{std::move(map_hp_max)} {}

    // clang-format on

    constexpr auto required_defeated_count() const noexcept -> decltype(auto) {
        return this->required_defeated_count_;
    }

    constexpr auto map_hp_current() const noexcept -> decltype(auto) {
        return this->map_hp_current_;
    }

    constexpr auto map_hp_max() const noexcept -> decltype(auto) {
        return this->map_hp_max_;
    }

   private:
    /// @brief 攻略に必要な撃破回数.
    std::int32_t required_defeated_count_;

    /// @brief 海域HPの現在値.
    std::int32_t map_hp_current_;

    /// @brief 海域HPの最大値.
    std::int32_t map_hp_max_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_MAP_DATA_HPP_INCLUDED
