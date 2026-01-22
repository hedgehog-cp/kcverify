#ifndef KCV_CORE_JSON_GLZ_META_KC3KAI_MST_SLOTITEM_BONUS_HPP_INCLUDED
#define KCV_CORE_JSON_GLZ_META_KC3KAI_MST_SLOTITEM_BONUS_HPP_INCLUDED

// std
#include <optional>
#include <string_view>
#include <vector>

// glz
#include <glaze/json.hpp>

// kcv
#include "kcv/external/kc3kai/mst_slotitem_bonus.hpp"
#include "kcv/external/kcsapi/types/enum/nationality.hpp"

template <>
struct glz::meta<kcv::kc3kai::bonus_data> final {
    using T = kcv::kc3kai::bonus_data;

   private:
    static constexpr auto to_nationality(std::string_view country) noexcept -> kcv::kcsapi::nationality {
        if (country == "JP") return kcv::kcsapi::nationality::japanese;
        if (country == "DE") return kcv::kcsapi::nationality::german;
        if (country == "IT") return kcv::kcsapi::nationality::italian;
        if (country == "US") return kcv::kcsapi::nationality::american;
        if (country == "GB") return kcv::kcsapi::nationality::british;
        if (country == "FR") return kcv::kcsapi::nationality::french;
        if (country == "RU") return kcv::kcsapi::nationality::russian;
        if (country == "SE") return kcv::kcsapi::nationality::swedish;
        if (country == "AU") return kcv::kcsapi::nationality::australian;
        if (country == "NL") return kcv::kcsapi::nationality::dutch;
        return kcv::kcsapi::nationality::unknown;
    }

    // operator()をstaticにするとコンパイルできない.
    static constexpr auto read_nationality = [](T& dst, const std::optional<std::vector<std::string_view>>& src) {
        if (not src.has_value()) {
            dst.ship_country = std::nullopt;
            return;
        }

        dst.ship_country = std::vector<kcv::kcsapi::nationality>{};
        dst.ship_country->reserve(src->size());
        for (const auto& country : *src) {
            dst.ship_country->push_back(to_nationality(country));
        }
    };

   public:
    static constexpr auto value = glz::object(
        // clang-format off
 
        "requiresAR",      &T::requires_anti_air_radar,
        "requiresSR",      &T::requires_surface_radar,
        "requiresAccR",    &T::requires_accuracy_radar,
        "shipClass",       &T::ship_class,
        "shipCountry",     glz::custom<read_nationality, &T::ship_country>,
        "shipId",          &T::ship_id,
        "shipBase",        &T::ship_base,
        "shipType",        &T::ship_type,
        "requiresId",      &T::requires_id,
        "requiresIdLevel", &T::requires_id_level,
        "requiresIdNum",   &T::requires_id_num,
        "requiresType",    &T::requires_type,
        "requiresTypeNum", &T::requires_type_num,
                           &T::level,
                           &T::num,
                           &T::bonus

        // clang-format on
    );
};

#endif  // KCV_CORE_JSON_GLZ_META_KC3KAI_MST_SLOTITEM_BONUS_HPP_INCLUDED
