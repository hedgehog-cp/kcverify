#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_NUMBER_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_NUMBER_HPP_INCLUDED

#include <charconv>
#include <cstdint>
#include <optional>
#include <string>
#include <system_error>
#include <variant>

namespace kcv {
namespace kcsapi {

/// @brief 数値または文字列で表された数. なぜか型が混合しているAPIが存在するため.
using number = std::variant<std::int32_t, std::string>;

/// @brief 数値にする.
/// @todo modelsにロジックを書きたくないので整理を検討する.
constexpr auto to_integer(const number& v) noexcept -> std::optional<std::int32_t> {
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

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_NUMBER_HPP_INCLUDED
