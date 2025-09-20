#ifndef KCVERIFY_EXTENSIONS_EXCEPTION_HPP_INCLUDED
#define KCVERIFY_EXTENSIONS_EXCEPTION_HPP_INCLUDED

#include <exception>
#include <source_location>
#include <stacktrace>
#include <string>

namespace kcv {

/// @brief kcvライブラリの背景情報をもつ例外基底型.
/// @note GCCでは-lstdc++expをリンクすること.
class exception : public std::exception {
   public:
    explicit exception(
        std::string msg          = "kcv::exception",
        std::source_location loc = std::source_location::current(),
        std::stacktrace trace    = std::stacktrace::current(1)
    )
        : what_{std::move(msg)}
        , loc_{loc}
        , trace_{trace} {}

    exception(const exception&)            = default;
    exception& operator=(const exception&) = default;
    exception(exception&&)                 = default;
    exception& operator=(exception&&)      = default;
    ~exception() noexcept override         = default;

    auto what() const noexcept -> const char* override {
        return what_.c_str();
    }

    auto stacktrace() const noexcept -> const std::stacktrace& {
        return trace_;
    }

    auto source_location() const noexcept -> const std::source_location& {
        return loc_;
    }

   private:
    std::string what_;
    std::source_location loc_;
    std::stacktrace trace_;
};

/// @brief 補足した標準例外に対して補足箇所からの背景情報を付与する, この意図を表すために用いる.
/// @details 使用例:
/// @code
/// try {
///     throw_exception_maybe();
/// } catch (const kcv::exception&) {
///     throw;
/// } catch (const std::exception&) {
///     std::throw_with_nested(kcv::make_exception_with_context());
/// }
/// @endcode
inline auto make_exception_with_context(
    std::string msg          = "kcv::exception",
    std::source_location loc = std::source_location::current(),
    std::stacktrace trace    = std::stacktrace::current(1)
) -> kcv::exception {
    return kcv::exception{std::move(msg), loc, trace};
}

/// @brief 例外を`stream`に書き出す.
void print_exception(std::FILE* stream, const std::exception& e);

}  // namespace kcv

#endif  // KCVERIFY_EXTENSIONS_EXCEPTION_HPP_INCLUDED
