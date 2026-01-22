#ifndef KCV_STD_EXT_FORMATTER_HPP_INCLUDED
#define KCV_STD_EXT_FORMATTER_HPP_INCLUDED

// std
#include <format>
#include <optional>

/// @brief std::optional<T>に対するformatを提供する.
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

#endif  // KCV_STD_EXT_FORMATTER_HPP_INCLUDED
