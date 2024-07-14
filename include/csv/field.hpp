#ifndef KCVERIFY_CSV_FIELD_HPP_INCLUDED
#define KCVERIFY_CSV_FIELD_HPP_INCLUDED

// std
#include <charconv>
#include <compare>
#include <concepts>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

// kcv
#include "csv/impl.hpp"

namespace kcv {
namespace csv {

class field final {
   public:
    friend constexpr bool operator==(const field& lhs, const field& rhs) noexcept {
        return lhs.field_.get_sv() == rhs.field_.get_sv();
    }

    friend constexpr auto operator<=>(const field& lhs, const field& rhs) noexcept {
        return lhs.field_.get_sv() <=> rhs.field_.get_sv();
    }

    friend constexpr bool operator==(const field& lhs, const std::string_view& rhs) noexcept {
        return lhs.field_.get_sv() == rhs;
    }

    friend constexpr auto operator<=>(const field& lhs, const std::string_view& rhs) noexcept {
        return lhs.field_.get_sv() <=> rhs;
    }

    constexpr operator std::string_view() const noexcept {
        return this->field_.get_sv();
    }

    constexpr field() noexcept
        : field_{""} {
    }

    field(const vincent_csv::field& field)
        : field_{field} {
    }

    constexpr field(vincent_csv::field&& field) noexcept
        : field_{std::move(field)} {
    }

    constexpr auto string() const -> std::string {
        return std::string{this->field_.get_sv()};
    }
    constexpr auto view() const noexcept -> std::string_view {
        return this->field_.get_sv();
    }

    template <typename T>
    constexpr auto optional() const noexcept -> std::optional<T> {
        if constexpr (std::is_arithmetic_v<T>) {
            T n;
            const auto sv = this->field_.get_sv();
            if (const auto& [_, ec] = std::from_chars(sv.begin(), sv.end(), n); ec == std::errc{}) {
                return std::make_optional(n);
            }
            return std::nullopt;
        } else if constexpr (std::is_enum_v<T>) {
            std::underlying_type_t<T> n;
            const auto sv = this->field_.get_sv();
            if (const auto& [_, ec] = std::from_chars(sv.begin(), sv.end(), n); ec == std::errc{}) {
                return std::make_optional(T{n});
            }
            return std::nullopt;
        } else {
            static_assert(false);
        }
    }

   private:
    vincent_csv::field field_;
};

}  // namespace csv
}  // namespace kcv

// kcv::csv::filedとstd::string_viewとで比較をするため.
// std::common_referenceおよびstd::common_reference_withにアダプトする.
// @see https://cpprefjp.github.io/reference/concepts/equality_comparable.html
// @see https://cpprefjp.github.io/reference/type_traits/common_reference.html
namespace std {
template <template <class> class TQual, template <class> class UQual>
struct basic_common_reference<kcv::csv::field, std::string_view, TQual, UQual> {
    using type = const std::string_view&;
};

// 対称性のために引数順を逆にしたものも定義する.
template <template <class> class TQual, template <class> class UQual>
struct basic_common_reference<std::string_view, kcv::csv::field, TQual, UQual> {
    using type = const std::string_view&;
};

}  // namespace std

static_assert(std::equality_comparable_with<kcv::csv::field, std::string_view>);
static_assert(std::totally_ordered_with<kcv::csv::field, std::string_view>);

#endif  // KCVERIFY_CSV_FIELD_HPP_INCLUDED
