#ifndef KCV_CORE_NUMERIC_INTERVAL_FORMATTER_HPP_INCLUDED
#define KCV_CORE_NUMERIC_INTERVAL_FORMATTER_HPP_INCLUDED

// std
#include <format>

// kcv
#include "kcv/core/numeric/interval/basic_interval.hpp"

/// @brief kcv::basic_interval<T, Fenv>に対するformatを提供する.
/// @todo 半開区間, 開区間にも対応する.
template <std::floating_point T, kcv::floating_environment Fenv>
struct std::formatter<kcv::basic_interval<T, Fenv>, char> {
    std::formatter<T, char> float_fmt;

    constexpr auto parse(std::format_parse_context& ctx) -> decltype(ctx.begin()) {
        return float_fmt.parse(ctx);
    }

    template <typename FormatContext>
    constexpr auto format(const kcv::basic_interval<T, Fenv>& i, FormatContext& ctx) const -> decltype(ctx.out()) {
        auto out = ctx.out();
        out      = std::format_to(out, "[");
        out      = float_fmt.format(i.lower(), ctx);
        out      = std::format_to(out, ", ");
        out      = float_fmt.format(i.upper(), ctx);
        out      = std::format_to(out, "]");
        return out;
    }
};

#endif  // KCV_CORE_NUMERIC_INTERVAL_FORMATTER_HPP_INCLUDED
