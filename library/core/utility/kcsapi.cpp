#include "core/utility/kcsapi.hpp"

// std
#include <algorithm>
#include <charconv>
#include <format>
#include <optional>
#include <ranges>
#include <utility>

// kcv
#include "extensions/exception.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"
#include "models/kcsapi/types/enum/equipment_id.hpp"
#include "models/kcsapi/types/enum/nationality.hpp"
#include "models/kcsapi/types/enum/ship_id.hpp"
#include "models/kcsapi/types/number.hpp"

auto kcv::find_mst(const kcv::kcsapi::api_mst_ship& api_mst_ship, kcv::kcsapi::ship_id id)
    -> const kcv::kcsapi::api_mst_ship::value_type& {
    using value_type = kcv::kcsapi::api_mst_ship::value_type;
    const auto itr   = std::ranges::lower_bound(api_mst_ship, id, {}, &value_type::api_id);

    if (itr == std::ranges::end(api_mst_ship) or itr->api_id != id) {
        throw kcv::exception{std::format("ship id not found. [ship id = {}].", std::to_underlying(id))};
    }

    return *itr;
}

auto kcv::find_mst(const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem, kcv::kcsapi::equipment_id id)
    -> const kcv::kcsapi::api_mst_slotitem::value_type& {
    using value_type = kcv::kcsapi::api_mst_slotitem::value_type;
    const auto itr   = std::ranges::lower_bound(api_mst_slotitem, id, {}, &value_type::api_id);

    if (itr == std::ranges::end(api_mst_slotitem) or itr->api_id != id) {
        throw kcv::exception{std::format("equipment id not found. [equipment id = {}].", std::to_underlying(id))};
    }

    return *itr;
}

auto kcv::base_id(const kcv::kcsapi::api_mst_ship& api_mst_ship, const kcv::kcsapi::api_mst_ship::value_type& mst)
    -> kcv::kcsapi::ship_id {
    for (const auto& e : api_mst_ship) {
        if (e.api_yomi == mst.api_yomi and e.api_sort_id % 10 == 1) [[unlikely]] {
            return e.api_id;
        }
    }

    throw kcv::exception{std::format("base id not found in api_mst_ship. [id = {}]", std::to_underlying(mst.api_id))};
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

auto kcv::to_integer(const kcv::kcsapi::number& v) noexcept -> std::optional<std::int32_t> {
    struct visitor final {
        static constexpr auto operator()(std::int32_t i) noexcept -> std::optional<std::int32_t> {
            return std::make_optional<std::int32_t>(i);
        }

        static constexpr auto operator()(const std::string& s) noexcept -> std::optional<std::int32_t> {
            if (std::int32_t i; std::from_chars(s.data(), s.data() + s.size(), i).ec == std::errc{}) [[likely]] {
                return std::make_optional<std::int32_t>(i);
            }
            return std::nullopt;
        }
    };

    return std::visit(visitor{}, v);
}

/// @brief 装備IDにする.
auto kcv::to_equipment_id(const kcv::kcsapi::number& v) noexcept -> kcv::kcsapi::equipment_id {
    struct visitor final {
        static constexpr auto operator()(std::int32_t i) noexcept -> kcv::kcsapi::equipment_id {
            return kcv::kcsapi::equipment_id{i};
        }

        static constexpr auto operator()(const std::string& s) noexcept -> kcv::kcsapi::equipment_id {
            if (std::int32_t i; std::from_chars(s.data(), s.data() + s.size(), i).ec == std::errc{}) [[likely]] {
                return kcv::kcsapi::equipment_id{i};
            }
            return kcv::kcsapi::equipment_id::invalid;
        }
    };

    return std::visit(visitor{}, v);
}