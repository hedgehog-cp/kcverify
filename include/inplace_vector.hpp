#ifndef KCVERIFY_INPLACE_VECTOR_HPP_INCLUDED
#define KCVERIFY_INPLACE_VECTOR_HPP_INCLUDED

#include <array>
#include <cstddef>
#include <new>
#include <utility>

namespace kcv {

/// @brief 静的容量の可変長配列.
/// @tparam T 要素型.
/// @tparam N キャパシティ.
/// @note C++26のstd::inplace_vectorの代替.
template <typename T, std::size_t N>
class inplace_vector final {
   public:
    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;
    using difference_type = std::ptrdiff_t;
    using iterator        = T*;
    using const_iterator  = const T*;
    using size_type       = std::size_t;

    static constexpr auto capacity() noexcept -> size_type {
        return N;
    }

    static constexpr auto max_size() noexcept -> size_type {
        return N;
    }

    constexpr auto size() const noexcept -> size_type {
        return this->size_;
    }

    constexpr void reserve(size_type n) {
        if (n > N) throw std::bad_alloc{};
    }

    constexpr auto push_back(const T& v) {
        if (this->size_ >= N) throw std::bad_alloc{};
        this->buffer_[this->size_] = v;
        this->size_++;
    }

    constexpr auto push_back(T&& v) {
        if (this->size_ >= N) throw std::bad_alloc{};
        this->buffer_[this->size_] = std::move(v);
        this->size_++;
    }

    constexpr auto begin() noexcept -> iterator {
        return this->buffer_.begin();
    }

    constexpr auto begin() const noexcept -> const_iterator {
        return this->buffer_.begin();
    }

    constexpr auto end() noexcept -> iterator {
        return this->buffer_.begin() + this->size_;
    }

    constexpr auto end() const noexcept -> const_iterator {
        return this->buffer_.begin() + this->size_;
    }

    std::array<T, N> buffer_ = {};
    size_type size_          = {};
};

}  // namespace kcv

#endif  // KCVERIFY_INPLACE_VECTOR_HPP_INCLUDED
