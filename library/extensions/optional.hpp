#ifndef KCVERIFY_EXTENSIONS_OPTIONAL_HPP_INCLUDED
#define KCVERIFY_EXTENSIONS_OPTIONAL_HPP_INCLUDED

/**
 * @file optional.hpp
 * @brief 標準ヘッダ<optional>の拡張.
 * @note C++26まで.
 */
#include <optional>

// std
#include <memory>

namespace kcv {

/// @brief std::optionalをstd::ranges::range対応するための標準公開継承派生クラス.
/// @note kcv::read_jsonで読み取れない.
template <typename T>
class optional final : public std::optional<T> {
   public:
    using iterator       = T*;
    using const_iterator = const T*;

    constexpr auto begin() noexcept -> iterator {
        return this->has_value() ? std::addressof(**this) : nullptr;
    }

    constexpr auto end() noexcept -> iterator {
        return this->has_value() ? std::addressof(**this) + 1 : nullptr;
    }

    constexpr auto begin() const noexcept -> const_iterator {
        return this->has_value() ? std::addressof(**this) : nullptr;
    }

    constexpr auto end() const noexcept -> const_iterator {
        return this->has_value() ? std::addressof(**this) + 1 : nullptr;
    }
};

}  // namespace kcv

#include <ranges>
template <typename T>
constexpr bool std::ranges::enable_view<kcv::optional<T>> = true;

// #include <format>
// template <typename T>
// constexpr auto std::format_kind<kcv::optional<T>> = std::range_format::disabled;

#include <variant>
static_assert(std::ranges::range<kcv::optional<std::monostate>>);
static_assert(std::ranges::view<kcv::optional<std::monostate>>);

#endif  // KCVERIFY_EXTENSIONS_OPTIONAL_HPP_INCLUDED
