#include "extensions/exception.hpp"

#include <exception>
#include <print>
#include <string_view>

void kcv::print_exception(std::FILE* stream, const std::exception& e) {
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

void kcv::print_exception(std::ostream& stream, const std::exception& e) {
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
