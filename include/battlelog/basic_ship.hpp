#ifndef KCVERIFY_BATTLELOG_BASIC_SHIP_HPP_INCLUDED
#define KCVERIFY_BATTLELOG_BASIC_SHIP_HPP_INCLUDED

// std
#include <ranges>
#include <vector>

// kcv
#include "battlelog/slot_iterator.hpp"
#include "battlelog/slotdata.hpp"
#include "csv/field.hpp"
#include "csv/row.hpp"
#include "master/equipment/convert.hpp"
#include "master/equipment/equipment.hpp"
#include "master/ship/convert.hpp"
#include "master/ship/ship.hpp"

namespace kcv {

template <typename Prefix>
class basic_ship final {
    static constexpr auto prefix = Prefix::value;

   public:
    explicit basic_ship(const csv::row& observed)
        : observed_{observed}
        , mst_ship_{to_master(this->id().template optional<ship_t::id_type>().value_or(ship_t::id_type{0}))}
        , mst_slot_{
              this->slot<slotdata::name>()
              | std::ranges::views::transform([](const auto& e) static -> const equipment_t& { return to_master(e); })
              | std::ranges::to<std::vector<equipment_t>>()
          } {
    }

    auto position() const -> csv::field {
        constexpr auto key = prefix + ".編成順";
        return this->observed_[key.c_str()];
    }

    auto name() const -> csv::field {
        constexpr auto key = prefix + ".名前";
        return this->observed_[key.c_str()];
    }

    auto id() const -> csv::field {
        constexpr auto key = prefix + ".ID";
        return this->observed_[key.c_str()];
    }

    auto stype() const -> csv::field {
        constexpr auto key = prefix + ".種別";
        return this->observed_[key.c_str()];
    }

    auto cond() const -> csv::field {
        constexpr auto key = prefix + ".疲労";
        return this->observed_[key.c_str()];
    }

    auto after_cond() const -> csv::field {
        constexpr auto key = prefix + ".戦闘後疲労";
        return this->observed_[key.c_str()];
    }

    auto nowhp() const -> csv::field {
        constexpr auto key = prefix + ".残耐久";
        return this->observed_[key.c_str()];
    }

    auto maxhp() const -> csv::field {
        constexpr auto key = prefix + ".最大耐久";
        return this->observed_[key.c_str()];
    }

    auto damage() const -> csv::field {
        constexpr auto key = prefix + ".損傷";
        return this->observed_[key.c_str()];
    }

    auto fuel() const -> csv::field {
        constexpr auto key = prefix + ".残燃料";
        return this->observed_[key.c_str()];
    }

    auto after_fuel() const -> csv::field {
        constexpr auto key = prefix + ".戦闘後残燃料";
        return this->observed_[key.c_str()];
    }

    auto max_fuel() const -> csv::field {
        constexpr auto key = prefix + ".最大燃料";
        return this->observed_[key.c_str()];
    }

    auto bull() const -> csv::field {
        constexpr auto key = prefix + ".残弾薬";
        return this->observed_[key.c_str()];
    }

    auto after_bull() const -> csv::field {
        constexpr auto key = prefix + ".戦闘後残弾薬";
        return this->observed_[key.c_str()];
    }

    auto max_bull() const -> csv::field {
        constexpr auto key = prefix + ".最大弾薬";
        return this->observed_[key.c_str()];
    }

    auto lv() const -> csv::field {
        constexpr auto key = prefix + ".Lv";
        return this->observed_[key.c_str()];
    }

    auto soku() const -> csv::field {
        constexpr auto key = prefix + ".速力";
        return this->observed_[key.c_str()];
    }

    auto karyoku() const -> csv::field {
        constexpr auto key = prefix + ".火力";
        return this->observed_[key.c_str()];
    }

    auto raisou() const -> csv::field {
        constexpr auto key = prefix + ".雷装";
        return this->observed_[key.c_str()];
    }

    auto taiku() const -> csv::field {
        constexpr auto key = prefix + ".対空";
        return this->observed_[key.c_str()];
    }

    auto soukou() const -> csv::field {
        constexpr auto key = prefix + ".装甲";
        return this->observed_[key.c_str()];
    }

    auto kaihi() const -> csv::field {
        constexpr auto key = prefix + ".回避";
        return this->observed_[key.c_str()];
    }

    auto taisen() const -> csv::field {
        constexpr auto key = prefix + ".対潜";
        return this->observed_[key.c_str()];
    }

    auto sakuteki() const -> csv::field {
        constexpr auto key = prefix + ".索敵";
        return this->observed_[key.c_str()];
    }

    auto lucky() const -> csv::field {
        constexpr auto key = prefix + ".運";
        return this->observed_[key.c_str()];
    }

    auto leng() const -> csv::field {
        constexpr auto key = prefix + ".射程";
        return this->observed_[key.c_str()];
    }

    template <typename Suffix>
    constexpr auto slot() const noexcept -> slot_iterator<Prefix, Suffix> {
        return slot_iterator<Prefix, Suffix>{this->observed_};
    }

    constexpr auto mst_ship() const noexcept -> const ship_t& {
        return this->mst_ship_;
    }

    constexpr auto mst_slot() const noexcept -> const std::vector<equipment_t>& {
        return this->mst_slot_;
    }

   private:
    const csv::row& observed_;
    const ship_t& mst_ship_;

    const std::vector<equipment_t> mst_slot_;
};

}  // namespace kcv

#endif  // KCVERIFY_BATTLELOG_BASIC_SHIP_HPP_INCLUDED
