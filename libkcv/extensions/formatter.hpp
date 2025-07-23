#ifndef KCVERIFY_EXTENSIONS_FORMATTER_HPP_INCLUDED
#define KCVERIFY_EXTENSIONS_FORMATTER_HPP_INCLUDED

// std
#include <format>
#include <optional>

// kcv
#include "extensions/exception.hpp"
#include "extensions/interval.hpp"

template <typename T>
struct std::formatter<std::optional<T>> : std::formatter<T> {
    template <typename FormatContext>
    constexpr auto format(const std::optional<T>& opt, FormatContext& ctx) const {
        if (opt.has_value()) {
            return std::formatter<T>::format(*opt, ctx);
        } else {
            return std::format_to(ctx.out(), "(null)");
        }
    }
};

template <>
struct std::formatter<kcv::exception, char> {
    constexpr auto parse(std::format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();  // 形式指定なし
    }

    template <typename FormatContext>
    constexpr auto format(const kcv::exception& e, FormatContext& ctx) const {
        const auto& loc = e.source_location();
        return std::format_to(
            ctx.out(),
            "{}:{}:{}: error: {}\n"
            "{}",
            loc.file_name(), loc.line(), loc.function_name(), e.what(), e.stacktrace()
        );
    }
};

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

#endif  // KCVERIFY_EXTENSIONS_FORMATTER_HPP_INCLUDED
