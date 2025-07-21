#ifndef KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_INTERVAL_FORMATTER_HPP_INCLUDED
#define KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_INTERVAL_FORMATTER_HPP_INCLUDED

// std
#include <concepts>
#include <format>

// kcv
#include "core/damage_formula/functions/interval.hpp"

/// @brief kcv::basic_interval<T, Fenv>に対するformatを提供する.
/// @todo 半開区間, 開区間にも対応する.
template <std::floating_point T, kcv::floating_environment Fenv>
struct std::formatter<kcv::basic_interval<T, Fenv>, char> {
    std::formatter<double, char> double_fmt;

    constexpr auto parse(std::format_parse_context& ctx) -> decltype(ctx.begin()) {
        return double_fmt.parse(ctx);
    }

    template <typename FormatContext>
    constexpr auto format(const kcv::basic_interval<T, Fenv>& i, FormatContext& ctx) const -> decltype(ctx.out()) {
        auto out = ctx.out();
        out      = std::format_to(out, "[");
        out      = double_fmt.format(i.lower(), ctx);
        out      = std::format_to(out, ", ");
        out      = double_fmt.format(i.upper(), ctx);
        out      = std::format_to(out, "]");
        return out;
    }
};

#endif  // KCVERIFY_CORE_DAMAGE_FORMULA_FUNCTIONS_INTERVAL_FORMATTER_HPP_INCLUDED
