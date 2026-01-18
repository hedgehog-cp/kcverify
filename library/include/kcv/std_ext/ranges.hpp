#ifndef KCV_STD_EXT_RANGES_HPP_INCLUDED
#define KCV_STD_EXT_RANGES_HPP_INCLUDED

// std
#include <compare>
#include <cstddef>
#include <iterator>
#include <limits>
#include <optional>
#include <ranges>
#include <vector>

namespace kcv {
namespace ranges {

/// @brief 型Rが範囲であり, その要素型がTである.
template <typename R, typename T>
concept range_of = std::ranges::range<R> and std::same_as<std::ranges::range_value_t<R>, T>;

/// @brief 装備スロットの範囲結合に特化したconcat_view.
/// 標準のconcatとは型引数のとりかたが異なるため移植に注意.
/// @tparam T 装備スロット.
template <typename T>
class slots_view final : public std::ranges::view_interface<slots_view<T>> {
   public:
    using size_type       = std::size_t;
    using value_type      = std::remove_const_t<T>;
    using reference       = T&;
    using const_reference = const T&;

    using eqslots_t = std::conditional_t<std::is_const_v<T>, const std::vector<value_type>, std::vector<value_type>>;
    using exslot_t = std::conditional_t<std::is_const_v<T>, const std::optional<value_type>, std::optional<value_type>>;

    /// @brief 装備スロットおよび増設スロットの反復子.
    class iterator final {
       public:
        using iterator_concept = std::random_access_iterator_tag;
        using difference_type  = std::ptrdiff_t;
        using value_type       = T;

        friend constexpr bool operator==(const iterator& lhs, const iterator& rhs) noexcept {
            return lhs.view_ == rhs.view_ and lhs.index_ == rhs.index_;
        }

        friend constexpr bool operator!=(const iterator& lhs, const iterator& rhs) noexcept {
            return lhs.view_ != rhs.view_ or lhs.index_ != rhs.index_;
        }

        friend constexpr auto operator<=>(const iterator&, const iterator&) noexcept -> std::strong_ordering = default;

        friend constexpr auto operator++(iterator& itr) noexcept -> iterator& {
            ++itr.index_;
            return itr;
        }

        friend constexpr auto operator++(iterator& itr, int) noexcept -> iterator {
            auto temp = itr;
            itr.index_++;
            return temp;
        }

        friend constexpr auto operator+=(iterator& itr, difference_type n) noexcept -> iterator& {
            itr.index_ += n;
            return itr;
        }

        friend constexpr auto operator+(const iterator& itr, difference_type n) noexcept -> iterator {
            auto temp   = itr;
            temp.index_ = temp.index_ + n;
            return temp;
        }

        friend constexpr auto operator+(difference_type n, const iterator& itr) noexcept -> iterator {
            auto temp   = itr;
            temp.index_ = n + temp.index_;
            return temp;
        }

        friend constexpr auto operator--(iterator& itr) noexcept -> iterator& {
            --itr.index_;
            return itr;
        }

        friend constexpr auto operator--(iterator& itr, int) noexcept -> iterator {
            auto temp = itr;
            itr.index_--;
            return temp;
        }

        friend constexpr auto operator-=(iterator& itr, difference_type n) noexcept -> iterator& {
            itr.index_ -= n;
            return itr;
        }

        friend constexpr auto operator-(const iterator& itr, difference_type n) noexcept -> iterator {
            auto temp   = itr;
            temp.index_ = temp.index_ - n;
            return temp;
        }

        friend constexpr auto operator-(const iterator& lhs, const iterator& rhs) noexcept -> difference_type {
            return lhs.index_ - rhs.index_;
        }

        friend constexpr auto operator*(const iterator& itr) -> value_type& {
            return (*itr.view_)[itr.index_];
        }

        [[deprecated("正確に終端を指さないため, operator!=などにおいて期待されない動作を示す.")]]
        constexpr iterator() noexcept
            : view_{nullptr}
            , index_{std::numeric_limits<size_type>::max()} {}

        constexpr iterator(slots_view& view, size_type index) noexcept
            : view_{&view}
            , index_{index} {}

        constexpr auto operator[](size_type n) const noexcept -> value_type& {
            return this->view_->operator[](this->index_ + n);
        }

       private:
        slots_view* view_;
        size_type index_;
    };

    /// @brief 装備スロットおよび増設スロットの反復子.
    class const_iterator final {
       public:
        using iterator_concept = std::random_access_iterator_tag;
        using difference_type  = std::ptrdiff_t;
        using value_type       = T;

        friend constexpr bool operator==(const const_iterator& lhs, const const_iterator& rhs) noexcept {
            return lhs.view_ == rhs.view_ and lhs.index_ == rhs.index_;
        }

        friend constexpr bool operator!=(const const_iterator& lhs, const const_iterator& rhs) noexcept {
            return lhs.view_ != rhs.view_ or lhs.index_ != rhs.index_;
        }

        friend constexpr auto operator<=>(const const_iterator&, const const_iterator&) noexcept = default;

        friend constexpr auto operator++(const_iterator& itr) noexcept -> const_iterator& {
            ++itr.index_;
            return itr;
        }

        friend constexpr auto operator++(const_iterator& itr, int) noexcept -> const_iterator {
            auto temp = itr;
            itr.index_++;
            return temp;
        }

        friend constexpr auto operator+=(const_iterator& itr, difference_type n) noexcept -> const_iterator& {
            itr.index_ += n;
            return itr;
        }

        friend constexpr auto operator+(const const_iterator& itr, difference_type n) noexcept -> const_iterator {
            auto temp   = itr;
            temp.index_ = temp.index_ + n;
            return temp;
        }

        friend constexpr auto operator+(difference_type n, const const_iterator& itr) noexcept -> const_iterator {
            auto temp   = itr;
            temp.index_ = n + temp.index_;
            return temp;
        }

        friend constexpr auto operator--(const_iterator& itr) noexcept -> const_iterator& {
            --itr.index_;
            return itr;
        }

        friend constexpr auto operator--(const_iterator& itr, int) noexcept -> const_iterator {
            auto temp = itr;
            itr.index_--;
            return temp;
        }

        friend constexpr auto operator-=(const_iterator& itr, difference_type n) noexcept -> const_iterator& {
            itr.index_ -= n;
            return itr;
        }

        friend constexpr auto operator-(const const_iterator& itr, difference_type n) noexcept -> const_iterator {
            auto temp   = itr;
            temp.index_ = temp.index_ - n;
            return temp;
        }

        friend constexpr auto operator-(const const_iterator& lhs, const const_iterator& rhs) noexcept
            -> difference_type {
            return lhs.index_ - rhs.index_;
        }

        friend constexpr auto operator*(const const_iterator& itr) -> const value_type& {
            return itr.view_->operator[](itr.index_);
        }

        [[deprecated("正確に終端を指さないため, operator!=などにおいて期待されない動作を示す.")]]
        constexpr const_iterator() noexcept
            : view_{nullptr}
            , index_{std::numeric_limits<size_type>::max()} {}

        constexpr const_iterator(const slots_view& view, size_type index) noexcept
            : view_{&view}
            , index_{index} {}

        constexpr auto operator[](size_type n) const noexcept -> const value_type& {
            return this->view_->operator[](this->index_ + n);
        }

       private:
        const slots_view* view_;
        size_type index_;
    };

    constexpr slots_view() noexcept = default;

    constexpr slots_view(eqslots_t& eqslots, exslot_t& exslot) noexcept
        : eqslots_{std::addressof(eqslots)}
        , exslot_{std::addressof(exslot)} {}

    constexpr auto size() const noexcept -> size_type {
        const auto eqsize = this->eqslots_ ? this->eqslots_->size() : 0uz;
        const auto exsize = this->exslot_ and this->exslot_->has_value() ? 1uz : 0uz;
        return eqsize + exsize;
    }

    constexpr auto operator[](size_type n) noexcept -> reference {
        if (n < this->eqslots_->size()) {
            return this->eqslots_->operator[](n);
        } else {
            return **this->exslot_;
        }
    }

    constexpr auto operator[](size_type n) const noexcept -> const_reference {
        if (n < this->eqslots_->size()) [[likely]] {
            return this->eqslots_->operator[](n);
        } else {
            return **this->exslot_;
        }
    }

    constexpr auto begin() noexcept -> iterator {
        return iterator{*this, 0};
    }

    constexpr auto end() noexcept -> iterator {
        return iterator{*this, this->size()};
    }

    constexpr auto begin() const noexcept -> const_iterator {
        return const_iterator{*this, 0};
    }

    constexpr auto end() const noexcept -> const_iterator {
        return const_iterator{*this, this->size()};
    }

   private:
    eqslots_t* eqslots_;
    exslot_t* exslot_;
};

namespace views {

/// @brief concatのCPOの型.
struct concat_fn final {
    template <typename T>
    static constexpr auto operator()(std::vector<T>& eqslots, std::optional<T>& exslot) noexcept -> slots_view<T> {
        return slots_view<T>{eqslots, exslot};
    }

    template <typename T>
    static constexpr auto operator()(const std::vector<T>& eqslots, const std::optional<T>& exslot) noexcept
        -> slots_view<const T> {
        return slots_view<const T>{eqslots, exslot};
    }
};

/// @brief concatのCPO.
inline constexpr auto concat = concat_fn{};

}  // namespace views
}  // namespace ranges

namespace views = ranges::views;

}  // namespace kcv

#endif  // KCV_STD_EXT_RANGES_HPP_INCLUDED
