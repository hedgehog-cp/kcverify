#ifndef KCVERIFY_CORE_COMMON_FORMATTER_HPP_INCLUDED
#define KCVERIFY_CORE_COMMON_FORMATTER_HPP_INCLUDED

// std
#include <format>
#include <optional>

// kcv
#include "models/eoen/serialization/fit_bonus/fit_bonus_value.hpp"
#include "models/kc3kai/mst_slotitem_bonus.hpp"

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
struct std::formatter<kcv::eoen::serialization::fit_bonus::fit_bonus_value> {
    std::formatter<std::int32_t> int32_t_formatter;

    constexpr auto parse(std::format_parse_context& ctx) {
        return int32_t_formatter.parse(ctx);
    }

    template <typename FormatContext>
    constexpr auto format(const kcv::eoen::serialization::fit_bonus::fit_bonus_value& bonus, FormatContext& ctx) const {
        auto out = ctx.out();
        out      = std::format_to(out, "houg: ");
        out      = int32_t_formatter.format(bonus.houg, ctx);
        out      = std::format_to(out, ", tyku: ");
        out      = int32_t_formatter.format(bonus.tyku, ctx);
        out      = std::format_to(out, ", kaih: ");
        out      = int32_t_formatter.format(bonus.kaih, ctx);
        out      = std::format_to(out, ", souk: ");
        out      = int32_t_formatter.format(bonus.souk, ctx);
        out      = std::format_to(out, ", houm: ");
        out      = int32_t_formatter.format(bonus.houm, ctx);
        out      = std::format_to(out, ", tais: ");
        out      = int32_t_formatter.format(bonus.tais, ctx);
        out      = std::format_to(out, ", raig: ");
        out      = int32_t_formatter.format(bonus.raig, ctx);
        out      = std::format_to(out, ", saku: ");
        out      = int32_t_formatter.format(bonus.saku, ctx);
        out      = std::format_to(out, ", leng: ");
        out      = int32_t_formatter.format(bonus.leng, ctx);
        out      = std::format_to(out, ", baku: ");
        out      = int32_t_formatter.format(bonus.baku, ctx);
        return out;
    }
};

template <>
struct std::formatter<kcv::kc3kai::bonus_value> {
    std::formatter<std::int32_t> int32_t_formatter;

    constexpr auto parse(std::format_parse_context& ctx) {
        return int32_t_formatter.parse(ctx);
    }

    template <typename FormatContext>
    constexpr auto format(const kcv::kc3kai::bonus_value& bonus, FormatContext& ctx) const {
        auto out = ctx.out();
        out      = std::format_to(out, "houg: ");
        out      = int32_t_formatter.format(bonus.houg, ctx);
        out      = std::format_to(out, ", tyku: ");
        out      = int32_t_formatter.format(bonus.tyku, ctx);
        out      = std::format_to(out, ", kaih: ");
        out      = int32_t_formatter.format(bonus.kaih, ctx);
        out      = std::format_to(out, ", souk: ");
        out      = int32_t_formatter.format(bonus.souk, ctx);
        out      = std::format_to(out, ", houm: ");
        out      = int32_t_formatter.format(bonus.houm, ctx);
        out      = std::format_to(out, ", tais: ");
        out      = int32_t_formatter.format(bonus.tais, ctx);
        out      = std::format_to(out, ", raig: ");
        out      = int32_t_formatter.format(bonus.raig, ctx);
        out      = std::format_to(out, ", saku: ");
        out      = int32_t_formatter.format(bonus.saku, ctx);
        out      = std::format_to(out, ", leng: ");
        out      = int32_t_formatter.format(bonus.leng, ctx);
        out      = std::format_to(out, ", baku: ");
        out      = int32_t_formatter.format(bonus.baku, ctx);
        return out;
    }
};

#endif  // KCVERIFY_CORE_COMMON_FORMATTER_HPP_INCLUDED
