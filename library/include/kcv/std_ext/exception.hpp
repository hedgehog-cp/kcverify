#ifndef KCV_STD_EXT_EXCEPTION_HPP_INCLUDED
#define KCV_STD_EXT_EXCEPTION_HPP_INCLUDED

#include <exception>
#include <format>
#include <print>
#include <source_location>
#include <stacktrace>
#include <string>
#include <string_view>
#include <utility>

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
        , loc_{std::move(loc)}
        , trace_{std::move(trace)} {}

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
    return kcv::exception{std::move(msg), std::move(loc), std::move(trace)};
}

#define KCV_TRY try

#define KCV_CATCH_AND_RETHROW_WITH_CONTEXT                          \
    catch (const kcv::exception&) {                                 \
        throw;                                                      \
    }                                                               \
    catch (const std::exception&) {                                 \
        std::throw_with_nested(kcv::make_exception_with_context()); \
    }

/// @brief 到達エラー送出する.
/// この関数は, 参照型を返すenum switch関数での利用を意図している.
/// @code
/// const auto& f(Enum e) {
///     switch(e) { /* ... */}
///     kcv::throw_unrachable(e);
/// }
/// @endcode
template <typename T>
    requires std::is_enum_v<T>
[[noreturn]] inline void throw_unrachable(T value) {
    /// TODO: 動的メモリ確保しないように修正する.
    throw kcv::exception{std::format("unexpected enum value: {}", std::to_underlying(value))};
}

/// @brief 例外を`stream`に書き出す. 書き出される文字列は着色される.
inline void print_exception(std::FILE* stream, const std::exception& e) {
    constexpr auto red    = std::string_view{"\033[31m"};
    constexpr auto blue   = std::string_view{"\033[34m"};
    constexpr auto gray   = std::string_view{"\033[90m"};
    constexpr auto yellow = std::string_view{"\033[33m"};
    constexpr auto reset  = std::string_view{"\033[0m"};

    if (const auto kcv_exception = dynamic_cast<const kcv::exception*>(&e)) {
        const auto& loc = kcv_exception->source_location();
        std::print(
            stream,
            "{}{}:{}:{}{}: {}error{}: {}\n"
            "{}{}{}",
            blue, loc.file_name(), loc.line(), loc.function_name(), reset, red, reset,  //
            kcv_exception->what(), gray, kcv_exception->stacktrace(), reset
        );
    } else {
        std::print(stream, "{}\n", e.what());
    }

    try {
        std::rethrow_if_nested(e);
    } catch (const std::exception& nested) {
        std::print(stream, "{}caused by:{} ", yellow, reset);
        print_exception(stream, nested);
    } catch (...) {
        std::print(stream, "{}caused by:{} <non-standard exception>\n", yellow, reset);
    }
}

/// @brief 例外を`stream`に書き出す.
inline void print_exception(std::ostream& stream, const std::exception& e) {
    if (const auto kcv_exception = dynamic_cast<const kcv::exception*>(&e)) {
        const auto& loc = kcv_exception->source_location();
        std::print(
            stream,
            "{}:{}:{}: error: {}\n"
            "{}",
            loc.file_name(), loc.line(), loc.function_name(), kcv_exception->what(), kcv_exception->stacktrace()
        );
    } else {
        std::print(stream, "{}\n", e.what());
    }

    try {
        std::rethrow_if_nested(e);
    } catch (const std::exception& nested) {
        std::print(stream, "caused by: ");
        kcv::print_exception(stream, nested);
    } catch (...) {
        std::print(stream, "caused by: <non-standard exception>\n");
    }
}

}  // namespace kcv

#endif  // KCV_STD_EXT_EXCEPTION_HPP_INCLUDED
