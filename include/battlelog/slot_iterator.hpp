#ifndef KCVERIFY_BATTLELOG_SLOT_ITERATOR_HPP_INCLUDED
#define KCVERIFY_BATTLELOG_SLOT_ITERATOR_HPP_INCLUDED

// std
#include <array>
#include <cstddef>
#include <format>
#include <iterator>
#include <string>
#include <utility>

// kcv
#include "csv/field.hpp"
#include "csv/row.hpp"

namespace kcv {

inline constexpr auto slot_size = std::size_t{6};

template <typename Prefix, typename T>
class slot_iterator final {
    static constexpr auto prefix = Prefix::value;
    static constexpr auto suffix = T::suffix;

   public:
    using value_type       = csv::field;
    using difference_type  = std::ptrdiff_t;
    using iterator_concept = std::random_access_iterator_tag;
    using size_type        = std::size_t;

    friend constexpr auto begin(const slot_iterator itr) noexcept -> slot_iterator {
        return itr;
    }

    friend constexpr auto end(const slot_iterator) noexcept -> slot_iterator {
        return slot_iterator{};
    }

    friend constexpr bool operator==(const slot_iterator &lhs, const slot_iterator &rhs) noexcept {
        return lhs.i_ == rhs.i_;
    }

    friend constexpr bool operator!=(const slot_iterator &lhs, const slot_iterator &rhs) noexcept {
        return lhs.i_ != rhs.i_;
    }

    friend constexpr auto operator++(slot_iterator &itr) noexcept -> slot_iterator & {
        ++itr.i_;
        return itr;
    }

    friend constexpr auto operator++(slot_iterator &itr, int) noexcept -> slot_iterator {
        auto self = itr;
        itr.i_++;
        return self;
    }

    friend auto operator*(const slot_iterator &itr) -> value_type {
        const auto &key = keys[itr.i_];
        const auto &row = *itr.row_;
        return row[key];
    }

    // forward_iterator

    friend constexpr auto operator--(slot_iterator &itr) noexcept -> slot_iterator & {
        --itr.i_;
        return itr;
    }

    friend constexpr auto operator--(slot_iterator &itr, int) noexcept -> slot_iterator {
        auto self = itr;
        itr.i_--;
        return self;
    }

    // bidirectional_iterator

    // random_access_iterator

    friend constexpr auto operator+(const slot_iterator &itr, difference_type n) noexcept -> slot_iterator {
        return slot_iterator{itr.row_, itr.i_ + n};
    }

    friend constexpr auto operator+(difference_type n, const slot_iterator &itr) noexcept -> slot_iterator {
        return slot_iterator{itr.row_, n + itr.i_};
    }

    friend constexpr auto operator+=(slot_iterator &itr, difference_type n) noexcept -> slot_iterator & {
        itr.i_ += n;
        return itr;
    }

    friend constexpr auto operator-(const slot_iterator &itr, difference_type n) noexcept -> slot_iterator {
        return slot_iterator{itr.row_, itr.i_ - n};
    }

    friend constexpr auto operator-(const slot_iterator &lhs, const slot_iterator &rhs) noexcept -> difference_type {
        return lhs.i_ - rhs.i_;
    }

    friend constexpr auto operator-=(slot_iterator &itr, difference_type n) noexcept -> slot_iterator & {
        itr.i_ -= n;
        return itr;
    }

    friend constexpr auto operator<=>(const slot_iterator &lhs, const slot_iterator &rhs) noexcept {
        return lhs.i_ <=> rhs.i_;
    }

    // end
    constexpr slot_iterator() noexcept
        : row_{nullptr}
        , i_{slot_size} {
    }

    // begin
    constexpr slot_iterator(const csv::row &row) noexcept
        : row_{std::addressof(row)}
        , i_{0} {
    }

    constexpr auto begin() const noexcept -> slot_iterator {
        return *this;
    }

    constexpr auto end() const noexcept -> slot_iterator {
        return slot_iterator{};
    }

    constexpr auto operator[](size_type n) const -> value_type {
        const auto &row = *this->row_;
        const auto &key = keys[n];
        return row[key];
    }

   private:
    static inline const auto keys = []<std::size_t... i>(std::index_sequence<i...>) {
        return std::array<std::string, sizeof...(i)>{
            std::format("{}.装備{}.{}", prefix.c_str(), i + 1, suffix.c_str())...
        };
    }(std::make_index_sequence<slot_size>{});

    constexpr slot_iterator(const csv::row *row, std::size_t i) noexcept
        : row_{row}
        , i_{i} {
    }

   private:
    const csv::row *row_;
    std::size_t i_;
};

}  // namespace kcv

#endif  // KCVERIFY_BATTLELOG_SLOT_ITERATOR_HPP_INCLUDED
