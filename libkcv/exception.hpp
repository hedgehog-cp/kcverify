#ifndef KCVERIFY_EXCEPTION_HPP_INCLUDED
#define KCVERIFY_EXCEPTION_HPP_INCLUDED

#include <exception>
#include <source_location>
#include <stacktrace>
#include <string>
#include <utility>

namespace kcv {

/// @brief スタックトレースなどの情報を持つ例外型.
/// @note 派生クラスのためのクラス設計を行っていないため, finalを指定している.
class exception final : public std::exception {
   public:
    exception(std::string msg, std::source_location loc = std::source_location::current())
        : msg_{std::move(msg)}
        , loc_{std::move(loc)}
        , trace_{std::stacktrace::current(1)} {}

    auto what() const noexcept -> const char* override final {
        return this->msg_.c_str();
    }

    auto location() const noexcept -> const std::source_location& {
        return this->loc_;
    }

    auto stacktrace() const noexcept -> const std::stacktrace& {
        return this->trace_;
    }

   private:
    std::string msg_;
    std::source_location loc_;
    std::stacktrace trace_;
};

}  // namespace kcv

#endif  // KCVERIFY_EXCEPTION_HPP_INCLUDED
