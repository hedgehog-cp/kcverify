#ifndef KCVERIFY_CORE_SORTIE_ENTITIES_SHIP_HPP_INCLUDED
#define KCVERIFY_CORE_SORTIE_ENTITIES_SHIP_HPP_INCLUDED

// std
#include <ranges>
#include <vector>

// kcv
#include "core/sortie/entities/slot.hpp"
#include "extensions/optional.hpp"
#include "extensions/ranges.hpp"
#include "models/eoen/database/sortie/sortie_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/enum/nationality.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"

namespace kcv {
namespace sortie {

/// @brief 艦船.
class ship final {
   public:
    using eoen_type = kcv::eoen::database::sortie::sortie_ship;

    static auto from_eoen(
        const eoen_type& src,                                  //
        const kcv::kcsapi::api_mst_ship& api_mst_ship,         //
        const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem  //
    )                                                          //
        -> ship                                                //
    {
        const auto& mst = kcv::binary_search(api_mst_ship, src.id);
        return ship{
            mst,
            kcv::base_id(api_mst_ship, mst),
            kcv::nationality(mst),
            src.equipment_slots  //
                | std::ranges::views::transform([&api_mst_slotitem](const auto& e) {
                      return kcv::sortie::slot::from_eoen(e, api_mst_slotitem);
                  })
                | std::ranges::to<std::vector>(),
            src.expansion_slot.transform([&api_mst_slotitem](const auto& e) {
                return kcv::sortie::slot::from_eoen(e, api_mst_slotitem);
            }),
        };
    }

    constexpr ship(
        const kcv::kcsapi::api_mst_ship_value_t& mst,  //
        kcv::kcsapi::ship_id base_id,                  //
        kcv::kcsapi::nationality nationality,          //
        std::vector<kcv::sortie::slot> eqslots,        //
        std::optional<kcv::sortie::slot> exslot        //
    ) noexcept
        : mst_{mst}
        , base_id_{base_id}
        , nationality_{nationality}
        , eqslots_{eqslots}
        , exslot_{exslot}
        , slots_{kcv::ranges::views::concat(this->eqslots_, this->exslot_)} {}

    constexpr auto mst() const noexcept -> const kcv::kcsapi::api_mst_ship_value_t& {
        return this->mst_;
    }

    constexpr auto base_id() const noexcept -> kcv::kcsapi::ship_id {
        return this->base_id_;
    }

    constexpr auto nationality() const noexcept -> kcv::kcsapi::nationality {
        return this->nationality_;
    }

    constexpr auto eqslots() const noexcept -> const std::vector<kcv::sortie::slot>& {
        return this->eqslots_;
    }

    constexpr auto exslot() const noexcept -> const kcv::optional<kcv::sortie::slot>& {
        return this->exslot_;
    }

    constexpr auto slots() const noexcept -> const std::ranges::random_access_range auto& {
        return this->slots_;
    }

   private:
    /// @brief 艦船マスタ.
    const kcv::kcsapi::api_mst_ship_value_t& mst_;

    /// @brief 未改造艦船ID
    kcv::kcsapi::ship_id base_id_;

    /// @brief 国籍
    kcv::kcsapi::nationality nationality_;

    /// @brief 装備スロット.
    std::vector<kcv::sortie::slot> eqslots_;

    /// @brief 増設スロット.
    kcv::optional<kcv::sortie::slot> exslot_;

    /// @brief 装備スロット.
    decltype(kcv::ranges::views::concat(eqslots_, exslot_)) slots_;
};

}  // namespace sortie
}  // namespace kcv

// MARK: フリー関数
// shipクラスのメンバ関数として`has_*`関数を定義することを考慮したが, shipクラスが巨大になる.
// コンストラクト時に 全ての`bool has_*_;`メンバ変数を初期化することは高コストであり, sizeof(ship)の値も大きくなる.
// 遅延評価クラス`kcv::lazy<T>`の導入を考慮したが, やはりこれもshipクラスが巨大になる.
// 結論として, `has_*`関数を非ジェネリックなフリー関数で定義する.

namespace kcv {
namespace sortie {

/// @brief 対空電探を搭載しているかを検証する.
bool has_anti_air_radar(const kcv::sortie::ship& ship) noexcept;

/// @brief 水上電探を搭載しているかを検証する.
bool has_surface_radar(const kcv::sortie::ship& ship) noexcept;

/// @brief 命中電探を搭載しているかを検証する.
bool has_accuracy_radar(const kcv::sortie::ship& ship) noexcept;

}  // namespace sortie
}  // namespace kcv

#endif  // KCVERIFY_CORE_SORTIE_ENTITIES_SHIP_HPP_INCLUDED
