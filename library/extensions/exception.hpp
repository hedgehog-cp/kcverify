#ifndef KCVERIFY_EXTENSIONS_EXCEPTION_HPP_INCLUDED
#define KCVERIFY_EXTENSIONS_EXCEPTION_HPP_INCLUDED

#include <exception>
#include <source_location>
#include <stacktrace>
#include <string>
#include <utility>

namespace kcv {

/// @brief source_locationとstacktraceつきの例外型.
/// @note GCCでは-lstdc++expをリンクすること.
class exception : public std::exception {
   public:
    exception(std::string what, std::source_location loc = std::source_location::current())
        : what_{std::move(what)}
        , loc_{std::move(loc)}
        , trace_{std::stacktrace::current(1)} {}

    constexpr auto what() const noexcept -> const char* override final {
        return this->what_.c_str();
    }

    constexpr auto source_location() const noexcept -> const std::source_location& {
        return this->loc_;
    }

    constexpr auto stacktrace() const noexcept -> const std::stacktrace& {
        return this->trace_;
    }

   protected:
    /// @note kcv::exceptionを継承する場合は, std::stacktrace構築のため, このコンストラクタを呼び出すこと.
    /// @example
    /// class example_exception : public kcv::exception {
    ///    public:
    ///     example_exception(std::string what, std::source_location loc = std::source_location::current())
    ///         : kcv::exception{std::move(what), std::move(loc), std::stacktrace::current(1)} {}
    /// };
    exception(std::string what, std::source_location loc, std::stacktrace trace)
        : what_{std::move(what)}
        , loc_{std::move(loc)}
        , trace_{std::move(trace)} {}

   private:
    std::string what_;
    std::source_location loc_;
    std::stacktrace trace_;
};

}  // namespace kcv

#endif  // KCVERIFY_EXTENSIONS_EXCEPTION_HPP_INCLUDED
