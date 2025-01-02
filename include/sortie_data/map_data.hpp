#ifndef KCVERIFY_SORTIE_MAP_DATA_HPP_INCLUDED
#define KCVERIFY_SORTIE_MAP_DATA_HPP_INCLUDED

// kcv
#include "eoen/database/sortie/sortie_map_data.hpp"

namespace kcv {

class map_data final {
   public:
    using eoen_type = eoen::database::sortie::sortie_map_data;

    static constexpr auto from_eoen(const eoen_type& src) noexcept -> map_data {
        return map_data{src.required_defeated_count, src.map_hp_current, src.map_hp_max};
    }

    constexpr map_data() = default;

    constexpr map_data(int required_defeated_count, int map_hp_current, int map_hp_max) noexcept
        : required_defeated_count_{required_defeated_count}
        , map_hp_current_{map_hp_current}
        , map_hp_max_{map_hp_max} {
    }

    constexpr int required_defeated_count() const noexcept {
        return this->required_defeated_count_;
    }

    constexpr int map_hp_current() const noexcept {
        return this->map_hp_current_;
    }

    constexpr int map_hp_max() const noexcept {
        return this->map_hp_max_;
    }

   private:
    int required_defeated_count_;
    int map_hp_current_;
    int map_hp_max_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_MAP_DATA_HPP_INCLUDED
