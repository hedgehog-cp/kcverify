#ifndef KCVERIFY_BATTLELOG_BATTLELOG_HPP_INCLUDED
#define KCVERIFY_BATTLELOG_BATTLELOG_HPP_INCLUDED

// std
#include <cstddef>
#include <string>

// kcv
#include "battlelog/basic_ship.hpp"
#include "battlelog/ship_prefix.hpp"
#include "csv/field.hpp"
#include "csv/row.hpp"

namespace kcv {

class battlelog final {
   public:
    using attacker_t = basic_ship<attacker_prefix>;
    using defender_t = basic_ship<defender_prefix>;

    explicit battlelog(const csv::row& observed)
        : observed_{observed}
        , attacker_{observed}
        , defender_{observed} {
    }

    auto operator[](std::size_t index) const -> csv::field {
        return this->observed_[index];
    }
    auto operator[](const std::string& key) const -> csv::field {
        return this->observed_[key];
    }

    constexpr auto attacker() const noexcept -> const attacker_t& {
        return this->attacker_;
    }
    constexpr auto defender() const noexcept -> const defender_t& {
        return this->defender_;
    }

   private:
    const csv::row& observed_;
    const attacker_t attacker_;
    const defender_t defender_;

    // using value_type = csv::field;
    // auto number() const -> value_type { return this->battlelog_["No."]; }
    // auto date() const -> value_type { return this->battlelog_["日付"]; }
    // auto area() const -> value_type { return this->battlelog_["海域"]; }
    // auto map_cell() const -> value_type { return this->battlelog_["マス"]; }
    // auto sortie() const -> value_type { return this->battlelog_["出撃"]; }
    // auto rank() const -> value_type { return this->battlelog_["ランク"]; }
    // auto abyssal_fleet() const -> value_type { return this->battlelog_["敵艦隊"]; }
    // auto hq_level() const -> value_type { return this->battlelog_["提督レベル"]; }
    // auto girls_formation() const -> value_type { return this->battlelog_["自陣形"]; }
    // auto abyssal_formation() const -> value_type { return this->battlelog_["敵陣形"]; }
    // auto girls_los() const -> value_type { return this->battlelog_["自索敵"]; }
    // auto abyssal_los() const -> value_type { return this->battlelog_["敵索敵"]; }
};

}  // namespace kcv

#endif  // KCVERIFY_BATTLELOG_BATTLELOG_HPP_INCLUDED
