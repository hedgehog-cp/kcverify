#include "extensions/exception.hpp"

#include <exception>
#include <print>

void kcv::print_exception(std::FILE* stream, const std::exception& e) {
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
