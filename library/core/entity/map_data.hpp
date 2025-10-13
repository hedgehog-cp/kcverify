#ifndef KCVERIFY_CORE_ENTITY_MAP_DATA_HPP_INCLUDED
#define KCVERIFY_CORE_ENTITY_MAP_DATA_HPP_INCLUDED

#include <cstdint>

namespace kcv {

class map_data final {
   public:
    map_data(std::int32_t required_defeat_count, std::int32_t map_hp_current, std::int32_t map_hp_max) noexcept
        : required_defeat_count_{required_defeat_count}
        , map_hp_current_{map_hp_current}
        , map_hp_max_{map_hp_max} {}

    auto required_defeat_count() const noexcept -> std::int32_t {
        return this->required_defeat_count_;
    }

    auto map_hp_current() const noexcept -> std::int32_t {
        return this->map_hp_current_;
    }

    auto map_hp_max() const noexcept -> std::int32_t {
        return this->map_hp_max_;
    }

   private:
    /// @brief 攻略に必要な撃破回数.
    std::int32_t required_defeat_count_;

    /// @brief 海域HPの現在値.
    std::int32_t map_hp_current_;

    /// @brief 海域HPの最大値.
    std::int32_t map_hp_max_;
};

}  // namespace kcv

#endif  // KCVERIFY_CORE_ENTITY_MAP_DATA_HPP_INCLUDED
