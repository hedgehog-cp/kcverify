#include "core/common/kcsapi.hpp"

// std
#include <algorithm>
#include <format>
#include <ranges>
#include <stdexcept>
#include <utility>

// kcv
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/enum/nationality.hpp"

auto kcv::binary_search(const kcv::kcsapi::api_mst_ship& api_mst_ship, kcv::kcsapi::ship_id id)
    -> const kcv::kcsapi::api_mst_ship::value_type&  //
{
    using value_type = kcv::kcsapi::api_mst_ship::value_type;
    const auto itr   = std::ranges::lower_bound(api_mst_ship, id, {}, &value_type::api_id);
    if (itr != std::ranges::end(api_mst_ship) and itr->api_id == id) {
        return *itr;
    }

    /// @todo 専用の例外型を使用する.
    const auto msg = std::format("ship id not found. [ship id = {}].", std::to_underlying(id));
    throw std::invalid_argument{msg};
}

auto kcv::binary_search(const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem, kcv::kcsapi::equipment_id id)
    -> const kcv::kcsapi::api_mst_slotitem::value_type&  //
{
    using value_type = kcv::kcsapi::api_mst_slotitem::value_type;
    const auto itr   = std::ranges::lower_bound(api_mst_slotitem, id, {}, &value_type::api_id);
    if (itr != std::ranges::end(api_mst_slotitem) and itr->api_id == id) {
        return *itr;
    }

    /// @todo 専用の例外型を使用する.
    const auto msg = std::format("equipment id not found. [equipment id = {}].", std::to_underlying(id));
    throw std::invalid_argument{msg};
}

auto kcv::base_id(const kcv::kcsapi::api_mst_ship& api_mst_ship, const kcv::kcsapi::api_mst_ship::value_type& mst)
    -> kcv::kcsapi::ship_id  //
{
    for (const auto& e : api_mst_ship) {
        if (e.api_yomi == mst.api_yomi and e.api_sort_id % 10 == 1) [[unlikely]] {
            return e.api_id;
        }
    }

    /// @todo 専用の例外型を使用する.
    const auto msg = std::format("base id not found in api_mst_ship. [id = {}]", std::to_underlying(mst.api_id));
    throw std::invalid_argument{msg};
}

auto kcv::nationality(const kcv::kcsapi::api_mst_ship::value_type& mst) noexcept -> kcv::kcsapi::nationality {
    const auto sort_id = mst.api_sort_id;

    if (sort_id == 0) return kcv::kcsapi::nationality::abyssal;
    if (sort_id < 1000) return kcv::kcsapi::nationality::unknown;
    if (sort_id < 30000) return kcv::kcsapi::nationality::japanese;
    if (sort_id < 31000) return kcv::kcsapi::nationality::german;
    if (sort_id < 32000) return kcv::kcsapi::nationality::italian;
    if (sort_id < 33000) return kcv::kcsapi::nationality::american;
    if (sort_id < 34000) return kcv::kcsapi::nationality::british;
    if (sort_id < 35000) return kcv::kcsapi::nationality::french;
    if (sort_id < 36000) return kcv::kcsapi::nationality::russian;
    if (sort_id < 37000) return kcv::kcsapi::nationality::swedish;
    if (sort_id < 38000) return kcv::kcsapi::nationality::dutch;
    if (sort_id < 39000) return kcv::kcsapi::nationality::australian;
    return kcv::kcsapi::nationality::unknown;
}