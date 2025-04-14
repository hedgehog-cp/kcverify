#ifndef KCVERIFY_CORE_INTERVAL_HPP_INCLUDED
#define KCVERIFY_CORE_INTERVAL_HPP_INCLUDED

// std
#include <algorithm>
#include <cfenv>
#include <cmath>
#include <concepts>
#include <limits>
#include <numeric>
#include <utility>

// kcv
#include "stdfloat.hpp"

/// @note constexprを指定できるが, コンパイル時と実行時の浮動小数点数環境が一致しない場合があるため,
/// コンパイル時と実行時とで計算結果が異なる場合がある. このため, constexprを指定しない.
/// @see https://cpprefjp.github.io/lang/cpp11/constexpr.html

namespace kcv {

/// @brief 精度保証なし数値計算のための浮動小数点数環境.
struct fenv_neutral final {
    constexpr fenv_neutral() noexcept {}

    ~fenv_neutral() noexcept {}

    auto decrease(const std::invocable<> auto& f) const noexcept(noexcept(f())) {
        return f();
    }

    auto increase(const std::invocable<> auto& f) const noexcept(noexcept(f())) {
        return f();
    }
};

/// @brief 精度保証付き数値計算のための浮動小数点数環境.
struct fenv_rounding final {
    constexpr fenv_rounding() noexcept {}

    ~fenv_rounding() noexcept {
        std::fesetround(FE_TONEAREST);
    }

    auto decrease(const std::invocable<> auto& f) const noexcept(noexcept(f())) {
        std::fesetround(FE_DOWNWARD);
        return f();
    }

    auto increase(const std::invocable<> auto& f) const noexcept(noexcept(f())) {
        std::fesetround(FE_UPWARD);
        return f();
    }
};

/// @brief 機械閉区間.
/// @tparam T 浮動小数点数型.
/// @tparam Fenv 浮動小数点数環境.
/// @note 空集合を表現できない.
template <std::floating_point T, typename Fenv = fenv_rounding>
class basic_interval final {
   public:
    using base_type = T;
    using fenv_type = Fenv;

    // MARK: operator+

    friend auto operator+(const basic_interval& lhs, const basic_interval& rhs) noexcept -> basic_interval {
        const auto fenv = fenv_type{};
        return basic_interval{
            fenv.decrease([&]() { return lhs.lower_ + rhs.lower_; }),
            fenv.increase([&]() { return lhs.upper_ + rhs.upper_; }),
        };
    }

    friend auto operator+(const basic_interval& lhs, const base_type& rhs) noexcept -> basic_interval {
        const auto fenv = fenv_type{};
        return basic_interval{
            fenv.decrease([&]() { return lhs.lower_ + rhs; }),
            fenv.increase([&]() { return lhs.upper_ + rhs; }),
        };
    }

    friend auto operator+(const base_type& lhs, const basic_interval& rhs) noexcept -> basic_interval {
        const auto fenv = fenv_type{};
        return basic_interval{
            fenv.decrease([&]() { return lhs + rhs.lower_; }),
            fenv.increase([&]() { return lhs + rhs.upper_; }),
        };
    }

    // MARK: operator+=

    // MARK: operator-

    friend auto operator-(const basic_interval& lhs, const basic_interval& rhs) noexcept -> basic_interval {
        const auto fenv = fenv_type{};
        return basic_interval{
            fenv.decrease([&]() { return lhs.lower_ - rhs.upper_; }),
            fenv.increase([&]() { return lhs.upper_ - rhs.lower_; }),
        };
    }

    friend auto operator-(const basic_interval& lhs, const base_type& rhs) noexcept -> basic_interval {
        const auto fenv = fenv_type{};
        return basic_interval{
            fenv.decrease([&]() { return lhs.lower_ - rhs; }),
            fenv.increase([&]() { return lhs.upper_ - rhs; }),
        };
    }

    friend auto operator-(const base_type& lhs, const basic_interval& rhs) noexcept -> basic_interval {
        const auto fenv = fenv_type{};
        return basic_interval{
            fenv.decrease([&]() { return lhs - rhs.upper_; }),
            fenv.increase([&]() { return lhs - rhs.lower_; }),
        };
    }

    // MARK: operator-=

    // MARK: operator*

    friend auto operator*(const basic_interval& lhs, const basic_interval& rhs) noexcept -> basic_interval {
        const auto fenv = fenv_type{};

        if (lhs.upper_ < 0.0) {
            if (rhs.upper_ < 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.upper_ * rhs.upper_; }),
                    fenv.increase([&]() { return lhs.lower_ * rhs.lower_; }),
                };
            }

            if (rhs.lower_ <= 0.0 and rhs.upper_ >= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.lower_ * rhs.upper_; }),
                    fenv.increase([&]() { return lhs.lower_ * rhs.lower_; }),
                };
            }

            if (rhs.lower_ > 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.lower_ * rhs.upper_; }),
                    fenv.increase([&]() { return lhs.upper_ * rhs.lower_; }),
                };
            }
        }

        if (lhs.lower_ <= 0.0 and lhs.upper_ >= 0.0) {
            if (rhs.upper_ < 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.upper_ * rhs.lower_; }),
                    fenv.increase([&]() { return lhs.lower_ * rhs.lower_; }),
                };
            }

            if (rhs.lower_ <= 0.0 and rhs.upper_ >= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return std::min(lhs.lower_ * rhs.upper_, lhs.upper_ * rhs.lower_); }),
                    fenv.increase([&]() { return std::max(lhs.lower_ * rhs.lower_, lhs.upper_ * rhs.upper_); }),
                };
            }

            if (rhs.lower_ > 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.lower_ * rhs.upper_; }),
                    fenv.increase([&]() { return lhs.upper_ * rhs.upper_; }),
                };
            }
        }

        if (lhs.lower_ > 0.0) {
            if (rhs.upper_ < 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.upper_ * rhs.lower_; }),
                    fenv.increase([&]() { return lhs.lower_ * rhs.upper_; }),
                };
            }

            if (rhs.lower_ <= 0.0 and rhs.upper_ >= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.upper_ * rhs.lower_; }),
                    fenv.increase([&]() { return lhs.upper_ * rhs.upper_; }),
                };
            }

            if (rhs.lower_ > 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.lower_ * rhs.lower_; }),
                    fenv.increase([&]() { return lhs.upper_ * rhs.upper_; }),
                };
            }
        }

        std::unreachable();
    }

    friend auto operator*(const basic_interval& lhs, const base_type& rhs) noexcept -> basic_interval {
        const auto fenv = fenv_type{};

        if (lhs.upper_ < 0.0) {
            if (rhs < 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.upper_ * rhs; }),
                    fenv.increase([&]() { return lhs.lower_ * rhs; }),
                };
            }

            if (rhs <= 0.0 and rhs >= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.lower_ * rhs; }),
                    fenv.increase([&]() { return lhs.lower_ * rhs; }),
                };
            }

            if (rhs > 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.lower_ * rhs; }),
                    fenv.increase([&]() { return lhs.upper_ * rhs; }),
                };
            }
        }

        if (lhs.lower_ <= 0.0 and lhs.upper_ >= 0.0) {
            if (rhs < 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.upper_ * rhs; }),
                    fenv.increase([&]() { return lhs.lower_ * rhs; }),
                };
            }

            if (rhs <= 0.0 and rhs >= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return std::min(lhs.lower_ * rhs, lhs.upper_ * rhs); }),
                    fenv.increase([&]() { return std::max(lhs.lower_ * rhs, lhs.upper_ * rhs); }),
                };
            }

            if (rhs > 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.lower_ * rhs; }),
                    fenv.increase([&]() { return lhs.upper_ * rhs; }),
                };
            }
        }

        if (lhs.lower_ > 0.0) {
            if (rhs < 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.upper_ * rhs; }),
                    fenv.increase([&]() { return lhs.lower_ * rhs; }),
                };
            }

            if (rhs <= 0.0 and rhs >= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.upper_ * rhs; }),
                    fenv.increase([&]() { return lhs.upper_ * rhs; }),
                };
            }

            if (rhs > 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.lower_ * rhs; }),
                    fenv.increase([&]() { return lhs.upper_ * rhs; }),
                };
            }
        }

        std::unreachable();
    }

    friend auto operator*(const base_type& lhs, const basic_interval& rhs) noexcept -> basic_interval {
        const auto fenv = fenv_type{};

        if (lhs < 0.0) {
            if (rhs.upper_ < 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs * rhs.upper_; }),
                    fenv.increase([&]() { return lhs * rhs.lower_; }),
                };
            }

            if (rhs.lower_ <= 0.0 and rhs.upper_ >= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs * rhs.upper_; }),
                    fenv.increase([&]() { return lhs * rhs.lower_; }),
                };
            }

            if (rhs.lower_ > 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs * rhs.upper_; }),
                    fenv.increase([&]() { return lhs * rhs.lower_; }),
                };
            }
        }

        if (lhs <= 0.0 and lhs >= 0.0) {
            if (rhs.upper_ < 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs * rhs.lower_; }),
                    fenv.increase([&]() { return lhs * rhs.lower_; }),
                };
            }

            if (rhs.lower_ <= 0.0 and rhs.upper_ >= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return std::min(lhs * rhs.upper_, lhs * rhs.lower_); }),
                    fenv.increase([&]() { return std::max(lhs * rhs.lower_, lhs * rhs.upper_); }),
                };
            }

            if (rhs.lower_ > 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs * rhs.upper_; }),
                    fenv.increase([&]() { return lhs * rhs.upper_; }),
                };
            }
        }

        if (lhs > 0.0) {
            if (rhs.upper_ < 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs * rhs.lower_; }),
                    fenv.increase([&]() { return lhs * rhs.upper_; }),
                };
            }

            if (rhs.lower_ <= 0.0 and rhs.upper_ >= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs * rhs.lower_; }),
                    fenv.increase([&]() { return lhs * rhs.upper_; }),
                };
            }

            if (rhs.lower_ > 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs * rhs.lower_; }),
                    fenv.increase([&]() { return lhs * rhs.upper_; }),
                };
            }
        }

        std::unreachable();
    }

    // MARK: operator*=

    // MARK: operator/

    friend auto operator/(const basic_interval& lhs, const basic_interval& rhs) noexcept -> basic_interval {
        const auto fenv = fenv_type{};

        if (rhs.upper_ > 0.0) {
            if (lhs.lower_ >= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.lower_ / rhs.upper_; }),
                    fenv.increase([&]() { return lhs.upper_ / rhs.lower_; }),
                };
            }

            if (lhs.upper_ <= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.lower_ / rhs.lower_; }),
                    fenv.increase([&]() { return lhs.upper_ / rhs.upper_; }),
                };
            }

            return basic_interval{
                fenv.decrease([&]() { return lhs.lower_ / rhs.lower_; }),
                fenv.increase([&]() { return lhs.upper_ / rhs.lower_; }),
            };
        }

        if (rhs.upper_ < 0.0) {
            if (lhs.lower_ >= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.upper_ / rhs.upper_; }),
                    fenv.increase([&]() { return lhs.lower_ / rhs.lower_; }),
                };
            }

            if (lhs.upper_ <= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.upper_ / rhs.lower_; }),
                    fenv.increase([&]() { return lhs.lower_ / rhs.upper_; }),
                };
            }

            return basic_interval{
                fenv.decrease([&]() { return lhs.upper_ / rhs.upper_; }),
                fenv.increase([&]() { return lhs.lower_ / rhs.upper_; }),
            };
        }

        // 0除算
        return basic_interval::whole();
    }

    friend auto operator/(const basic_interval& lhs, const base_type& rhs) noexcept -> basic_interval {
        const auto fenv = fenv_type{};

        if (rhs > 0.0) {
            if (lhs.lower_ >= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.lower_ / rhs; }),
                    fenv.increase([&]() { return lhs.upper_ / rhs; }),
                };
            }

            if (lhs.upper_ <= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.lower_ / rhs; }),
                    fenv.increase([&]() { return lhs.upper_ / rhs; }),
                };
            }

            return basic_interval{
                fenv.decrease([&]() { return lhs.lower_ / rhs; }),
                fenv.increase([&]() { return lhs.upper_ / rhs; }),
            };
        }

        if (rhs < 0.0) {
            if (lhs.lower_ >= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.upper_ / rhs; }),
                    fenv.increase([&]() { return lhs.lower_ / rhs; }),
                };
            }

            if (lhs.upper_ <= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs.upper_ / rhs; }),
                    fenv.increase([&]() { return lhs.lower_ / rhs; }),
                };
            }

            return basic_interval{
                fenv.decrease([&]() { return lhs.upper_ / rhs; }),
                fenv.increase([&]() { return lhs.lower_ / rhs; }),
            };
        }

        // 0除算
        return basic_interval::whole();
    }

    friend auto operator/(const base_type& lhs, const basic_interval& rhs) noexcept -> basic_interval {
        const auto fenv = fenv_type{};

        if (rhs.upper_ > 0.0) {
            if (lhs >= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs / rhs.upper_; }),
                    fenv.increase([&]() { return lhs / rhs.lower_; }),
                };
            }

            if (lhs <= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs / rhs.lower_; }),
                    fenv.increase([&]() { return lhs / rhs.upper_; }),
                };
            }

            return basic_interval{
                fenv.decrease([&]() { return lhs / rhs.lower_; }),
                fenv.increase([&]() { return lhs / rhs.lower_; }),
            };
        }

        if (rhs.upper_ < 0.0) {
            if (lhs >= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs / rhs.upper_; }),
                    fenv.increase([&]() { return lhs / rhs.lower_; }),
                };
            }

            if (lhs <= 0.0) {
                return basic_interval{
                    fenv.decrease([&]() { return lhs / rhs.lower_; }),
                    fenv.increase([&]() { return lhs / rhs.upper_; }),
                };
            }

            return basic_interval{
                fenv.decrease([&]() { return lhs / rhs.upper_; }),
                fenv.increase([&]() { return lhs / rhs.upper_; }),
            };
        }

        // 0除算
        return basic_interval::whole();
    }

    // MARK: operator/=

    // MARK: operator==

    friend bool operator==(const basic_interval& lhs, const basic_interval& rhs) noexcept {
        return lhs.lower_ == rhs.lower_ and lhs.upper_ == rhs.upper_;
    }

    friend bool operator==(const basic_interval& lhs, const base_type& rhs) noexcept {
        return lhs.lower_ == rhs and lhs.upper_ == rhs;
    }

    friend bool operator==(const base_type& lhs, const basic_interval& rhs) noexcept {
        return lhs == rhs.lower_ and lhs == rhs.upper_;
    }

    // MARK: operator<
    // 完全に<を満たすとき, trueを返す.

    friend bool operator<(const basic_interval& lhs, const basic_interval& rhs) noexcept {
        return lhs.lower_ < lhs.upper_ and lhs.upper_ < rhs.lower_ and rhs.lower_ < rhs.upper_;
    }

    friend bool operator<(const basic_interval& lhs, const base_type& rhs) noexcept {
        return lhs.lower_ < lhs.upper_ and lhs.upper_ < rhs;
    }

    friend bool operator<(const base_type& lhs, const basic_interval& rhs) noexcept {
        return lhs < rhs.lower_ and rhs.lower_ < rhs.upper_;
    }

    // MARK: operator>
    // 完全に>を満たすとき, trueを返す.

    friend bool operator>(const basic_interval& lhs, const basic_interval& rhs) noexcept {
        return lhs.lower_ > lhs.upper_ and lhs.upper_ > rhs.lower_ and rhs.lower_ > rhs.upper_;
    }

    friend bool operator>(const basic_interval& lhs, const base_type& rhs) noexcept {
        return lhs.lower_ > lhs.upper_ and lhs.upper_ > rhs;
    }

    friend bool operator>(const base_type& lhs, const basic_interval& rhs) noexcept {
        return lhs > rhs.lower_ and rhs.lower_ > rhs.upper_;
    }

    static auto whole() noexcept -> basic_interval {
        return basic_interval{
            -std::numeric_limits<base_type>::infinity(),
            +std::numeric_limits<base_type>::infinity(),
        };
    }

    basic_interval() noexcept
        : lower_{}
        , upper_{} {}

    basic_interval(const base_type& x) noexcept
        : lower_{x}
        , upper_{x} {}

    basic_interval(const base_type& lower, const base_type& upper) noexcept
        : lower_{lower}
        , upper_{upper} {}

    auto lower() const noexcept -> base_type {
        return this->lower_;
    }

    auto upper() const noexcept -> base_type {
        return this->upper_;
    }

   private:
    /// @brief 区間の下側.
    T lower_;

    /// @brief 区間の上側.
    T upper_;
};

/// @brief 順算用算術数値型.
using number = basic_interval<kcv::float64_t, fenv_neutral>;

/// @brief 逆算用算術数値型.
using interval = basic_interval<kcv::float64_t, fenv_rounding>;

// MARK: free functions
// 標準ライブラリに合わせてフリー関数化.

/// @brief 区間の中点を返す. 必ずしも真の区間の中点ではない.
template <std::floating_point T, typename Fenv>
auto midpoint(const basic_interval<T, Fenv>& x) noexcept -> T {
    return std::midpoint(x.lower(), x.upper());
}

/// @brief 区間幅を返す.
template <std::floating_point T, typename Fenv>
auto width(const basic_interval<T, Fenv>& x) noexcept -> T {
    const auto fenv = Fenv{};
    return fenv.increase([&]() { return x.upper() - x.lower(); });
}

/// @brief 区間半径を返す.
template <std::floating_point T, typename Fenv>
auto radius(const basic_interval<T, Fenv>& x) noexcept -> T {
    const auto fenv = Fenv{};
    return fenv.increase([&]() { return x.upper() / 2.0 - x.lower() / 2.0; });
}

/// @brief 区間に属するかを検証する.
/// lhs ∊ rhs
template <std::floating_point T, typename Fenv>
bool in(T lhs, const basic_interval<T, Fenv>& rhs) noexcept {
    return rhs.lower() <= lhs and lhs <= rhs.upper();
}

/// @brief 区間に含まれるかを検証する.
/// lhs ⊆ rhs
template <std::floating_point T, typename Fenv>
bool subset(const basic_interval<T, Fenv>& lhs, const basic_interval<T, Fenv>& rhs) noexcept {
    return rhs.lower() <= lhs.lower() and lhs.lower() <= lhs.upper() and lhs.upper() <= rhs.upper();
}

/// @brief 絶対値を返す.
template <std::floating_point T, typename Fenv>
auto abs(const basic_interval<T, Fenv>& x) noexcept -> basic_interval<T, Fenv> {
    const auto lower = std::fabs(x.lower());
    const auto upper = std::fabs(x.upper());
    return basic_interval<T, Fenv>{
        std::min(lower, upper),
        std::max(lower, upper),
    };
}

/// @brief 最大値を返す.
/// @note std::maxは意図しない結果を返す.
template <std::floating_point T, typename Fenv>
auto max(const basic_interval<T, Fenv>& a, const basic_interval<T, Fenv>& b) noexcept -> basic_interval<T, Fenv> {
    return basic_interval<T, Fenv>{
        std::max(a.lower(), b.lower()),
        std::max(a.upper(), b.upper()),
    };
}

/// @brief 最小値を返す.
/// @note std::minは意図しない結果を返す.
template <std::floating_point T, typename Fenv>
auto min(const basic_interval<T, Fenv>& a, const basic_interval<T, Fenv>& b) noexcept -> basic_interval<T, Fenv> {
    return basic_interval<T, Fenv>{
        std::min(a.lower(), b.lower()),
        std::min(a.upper(), b.upper()),
    };
}

/// @brief 平方根を返す.
template <std::floating_point T, typename Fenv>
auto sqrt(const basic_interval<T, Fenv>& x) noexcept -> basic_interval<T, Fenv> {
    const auto fenv = fenv_rounding{};
    return basic_interval<T, Fenv>{
        fenv.decrease([&]() { return std::sqrt(x.lower()); }),
        fenv.increase([&]() { return std::sqrt(x.upper()); }),
    };
}

/// @brief 2乗を返す.
/// @todo 区間幅の最適化をする.
template <std::floating_point T, typename Fenv>
auto square(const kcv::basic_interval<T, Fenv>& x) noexcept -> kcv::basic_interval<T, Fenv> {
    return x * x;
}

/// @brief 数が0であるかを検証する.
template <std::floating_point T, typename Fenv>
bool is_zero(const kcv::basic_interval<T, Fenv>& x) noexcept {
    return x == 0;
}

/// @brief 数が正であるかを検証する.
template <std::floating_point T, typename Fenv>
bool is_positive(const kcv::basic_interval<T, Fenv>& x) noexcept {
    return x.upper() > 0;
}

/// @brief 数が負であるかを検証する.
template <std::floating_point T, typename Fenv>
bool is_negative(const kcv::basic_interval<T, Fenv>& x) noexcept {
    return x.lower() < 0;
}

/// @brief intervalを作成する.
template <typename T>
auto make_interval(const T& x) noexcept -> interval {
    if constexpr (std::floating_point<T>) {
        return interval{x};
    } else if constexpr (std::same_as<T, number>) {
        return interval{x.lower(), x.upper()};
    } else {
        static_assert(false);
    }
}

}  // namespace kcv

#endif  // KCVERIFY_CORE_INTERVAL_HPP_INCLUDED
