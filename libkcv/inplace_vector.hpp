#ifndef KCVERIFY_INPLACE_VECTOR_HPP_INCLUDED
#define KCVERIFY_INPLACE_VECTOR_HPP_INCLUDED

#include <cstddef>
#include <iterator>
#include <memory>
#include <new>
#include <stdexcept>

namespace kcv {

/// @brief 静的容量の可変長配列.
/// @tparam T 要素型.
/// @tparam N キャパシティ.
/// @note C++26のstd::inplace_vectorの代替.
template <typename T, std::size_t C>
struct inplace_vector final {
    using value_type             = T;
    using size_type              = std::size_t;
    using reference              = T&;
    using const_reference        = const T&;
    using pointer                = T*;
    using const_pointer          = const T*;
    using iterator               = T*;
    using const_iterator         = const T*;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using difference_type        = std::ptrdiff_t;

    constexpr auto at(size_type n) -> reference {
        if (n >= this->size_) {
            throw std::out_of_range{"out of range."};
        }

        return this->storage_[n];
    }

    constexpr auto at(size_type n) const -> const_reference {
        if (n >= this->size_) {
            throw std::out_of_range{"out of range."};
        }

        return this->storage_[n];
    }

    constexpr auto operator[](size_type n) noexcept -> reference {
        return this->storage_[n];
    }

    constexpr auto operator[](size_type n) const noexcept -> const_reference {
        return this->storage_[n];
    }

    constexpr auto front() noexcept -> reference {
        return this->storage_[0];
    }

    constexpr auto front() const noexcept -> const_reference {
        return this->storage_[0];
    }

    constexpr auto data() noexcept -> pointer {
        return std::addressof(this->storage_[0]);
    }

    constexpr auto data() const noexcept -> const_pointer {
        return std::addressof(this->storage_[0]);
    }

    constexpr auto begin() noexcept -> iterator {
        return std::addressof(this->storage_[0]);
    }

    constexpr auto end() noexcept -> iterator {
        return std::addressof(this->storage_[this->size_]);
    }

    constexpr auto begin() const noexcept -> const_iterator {
        return std::addressof(this->storage_[0]);
    }

    constexpr auto end() const noexcept -> const_iterator {
        return std::addressof(this->storage_[this->size_]);
    }

    constexpr auto cbegin() const noexcept -> const_iterator {
        return std::addressof(this->storage_[0]);
    }

    constexpr auto cend() const noexcept -> const_iterator {
        return std::addressof(this->storage_[this->size_]);
    }

    constexpr auto rbegin() noexcept -> reverse_iterator {
        return std::addressof(this->storage_[0]);
    }

    constexpr auto rend() noexcept -> reverse_iterator {
        return std::addressof(this->storage_[this->size_]);
    }

    constexpr auto rbegin() const noexcept -> const_reverse_iterator {
        return std::addressof(this->storage_[0]);
    }

    constexpr auto rend() const noexcept -> const_reverse_iterator {
        return std::addressof(this->storage_[this->size_]);
    }

    constexpr auto crbegin() const noexcept -> const_reverse_iterator {
        return std::addressof(this->storage_[0]);
    }

    constexpr auto crend() const noexcept -> const_reverse_iterator {
        return std::addressof(this->storage_[this->size_]);
    }

    constexpr bool empty() const noexcept {
        return this->size_ == 0;
    }

    constexpr auto size() const noexcept -> size_type {
        return this->size_;
    }

    constexpr auto max_size() const noexcept -> size_type {
        return C;
    }

    constexpr auto capacity() const noexcept -> size_type {
        return C;
    }

    constexpr void push_back(const value_type& v) {
        if (this->size_ >= C) {
            throw std::bad_alloc{};
        }

        this->storage_[this->size_] = v;
    }

    constexpr void push_back(value_type&& v) {
        if (this->size_ >= C) {
            throw std::bad_alloc{};
        }

        this->storage_[this->size_] = std::move(v);
    }

    // constexpr void resize(size_type);
    // constexpr void resize(size_type, const value_type&);
    // constexpr void reserve(size_type n);
    // constexpr void shrink_to_fit();
    // constexpr void fill(const T&);
    // constexpr void swap(inplace_vector&) noexcept(noexcept(swap(declval<T&>(), declval<T&>())));

    // private:
    value_type storage_[C];

    // private:
    size_type size_;
};

}  // namespace kcv

#endif  // KCVERIFY_INPLACE_VECTOR_HPP_INCLUDED
