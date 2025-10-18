#ifndef KCVERIFY_EXTENSIONS_INPLACE_VECTOR_HPP_INCLUDED
#define KCVERIFY_EXTENSIONS_INPLACE_VECTOR_HPP_INCLUDED

#include <cstddef>
#include <iterator>
#include <new>
#include <type_traits>

namespace kcv {

/// @brief 静的容量の可変長配列. C++26のstd::inplace_vectorの代替.
/// @tparam T 要素型.
/// @tparam N キャパシティ.
/// XXX: 標準と異なり, 空のときnullptrを返さない.
template <typename T, std::size_t N>
class inplace_vector final {
    static_assert(std::is_trivially_default_constructible_v<T>);
    static_assert(std::is_trivially_destructible_v<T>);

   public:
    using size_type       = std::size_t;
    using value_type      = T;
    using reference       = T&;
    using const_reference = const T&;
    using pointer         = T*;
    using const_pointer   = const T*;
    using iterator        = T*;
    using const_iterator  = const T*;

    constexpr inplace_vector() noexcept = default;

    constexpr inplace_vector(std::initializer_list<T> il) {
        if (il.size() > N) {
            throw std::bad_alloc{};
        }

        for (auto i = 0uz; const auto& e : il) {
            this->data_[i++] = e;
        }
        this->size_ = il.size();
    }

    constexpr auto size() const noexcept -> size_type {
        return this->size_;
    }

    constexpr auto operator[](size_type n) noexcept -> reference {
        return this->data_[n];
    }

    constexpr auto operator[](size_type n) const noexcept -> const_reference {
        return this->data_[n];
    }

    constexpr auto data() noexcept -> pointer {
        return this->data_;
    }

    constexpr auto data() const noexcept -> const_pointer {
        return this->data_;
    }

    constexpr auto begin() noexcept -> iterator {
        return this->data_;
    }

    constexpr auto begin() const noexcept -> const_iterator {
        return this->data_;
    }

    constexpr auto end() noexcept -> iterator {
        return this->data_ + this->size_;
    }

    constexpr auto end() const noexcept -> const_iterator {
        return this->data_ + this->size_;
    }

    constexpr void push_back(const value_type& v) {
        if (this->size_ == N) {
            throw std::bad_alloc{};
        }

        this->data_[this->size_] = v;
        this->size_++;
    }

    constexpr void push_back(value_type&& v) {
        if (this->size_ == N) {
            throw std::bad_alloc{};
        }

        this->data_[this->size_] = std::move(v);
        this->size_++;
    }

    constexpr bool empty() const noexcept {
        return this->size_ == 0;
    }

   private:
    size_type size_     = {};
    value_type data_[N] = {};
};

}  // namespace kcv

#endif  // KCVERIFY_EXTENSIONS_INPLACE_VECTOR_HPP_INCLUDED
