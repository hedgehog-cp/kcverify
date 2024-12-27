#ifndef KCVERIFY_OPTIONAL_OPTIONAL_HPP_INCLUDED
#define KCVERIFY_OPTIONAL_OPTIONAL_HPP_INCLUDED

#include <cstddef>
#include <iterator>
#include <memory>
#include <optional>
#include <ranges>

namespace kcv {

/// @brief std::optionalをstd::ranges::range対応するための標準公開継承派生クラス.
/// @note C++26まで.
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

    constexpr auto cbegin() const noexcept -> const_iterator {
        return this->has_value() ? std::addressof(**this) : nullptr;
    }

    constexpr auto cend() const noexcept -> const_iterator {
        return this->has_value() ? std::addressof(**this) + 1 : nullptr;
    }

    constexpr bool empty() const noexcept {
        return not this->has_value();
    }

    constexpr auto size() const noexcept -> std::size_t {
        return this->has_value() ? 1 : 0;
    }

    static constexpr auto max_size() noexcept -> std::size_t {
        return 1;
    }

    constexpr void clear() noexcept {
        this->reset();
    }
};

}  // namespace kcv

static_assert(std::ranges::range<kcv::optional<int>>);
static_assert(std::random_access_iterator<kcv::optional<int>::iterator>);
static_assert(std::random_access_iterator<kcv::optional<int>::const_iterator>);

#endif  // KCVERIFY_OPTIONAL_OPTIONAL_HPP_INCLUDED
