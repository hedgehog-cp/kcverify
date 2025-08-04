#include "core/sortie/entities/ship.hpp"

// std
#include <concepts>

// kcv
#include "core/constants/equipment.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"

namespace {

/// @brief 述語関数を満たす装備を搭載しているかを検証する.
bool is_equipped_with_if(
    const kcv::sortie::ship& ship,
    const std::predicate<const kcv::kcsapi::api_mst_slotitem::value_type&> auto pred
) noexcept {
    // any_of
    for (const auto& slot : ship.slots()) {
        if (const auto& e = slot.equipment(); e.has_value()) {
            if (pred(e->mst())) {
                return true;
            }
        }
    }
    return false;
}

}  // namespace

bool kcv::sortie::has_anti_air_radar(const kcv::sortie::ship& ship) noexcept {
    return is_equipped_with_if(ship, kcv::is_anti_air_radar);
}

bool kcv::sortie::has_surface_radar(const kcv::sortie::ship& ship) noexcept {
    return is_equipped_with_if(ship, kcv::is_surface_radar);
}

bool kcv::sortie::has_accuracy_radar(const kcv::sortie::ship& ship) noexcept {
    return is_equipped_with_if(ship, kcv::is_accuracy_radar);
}