#include "kcv/core/json/read_json.hpp"

// std
#include <exception>
#include <fstream>
#include <string>

// glz
#include <glaze/glaze.hpp>

// kcv
#include "kcv/std_ext/exception.hpp"

namespace kcv {
namespace detail {

template <glz::opts Opts, typename T>
void read_json_impl(T& dst, const std::string& buffer) try {
    if (const auto error = glz::read<Opts>(dst, buffer); error) {
        std::ofstream{"read_json_error.json"} << buffer;
        throw kcv::exception{glz::format_error(error, buffer)};
    }
} catch (const kcv::exception&) {
    throw;
} catch (const std::exception&) {
    std::throw_with_nested(kcv::make_exception_with_context());
}

template <glz::opts Opts, typename T>
void read_json_impl(T& dst, const std::filesystem::path& fname) try {
    auto buffer = std::string{};
    buffer.resize_and_overwrite(
        std::filesystem::file_size(fname), [&fname](char* data, std::size_t size) -> std::size_t {
            std::ifstream{fname}.read(data, size);
            return size;
        }
    );
    kcv::detail::read_json_impl<Opts>(dst, std::as_const(buffer));
} catch (const kcv::exception&) {
    throw;
} catch (const std::exception&) {
    // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2024/p2319r0.html
    // https://onihusube.hatenablog.com/#P2319R0-Prevent-path-presentation-problems
    // [[deprecated("P2319: std::filesystem::string")]]
    auto msg = std::format("could not read file. [file = {}].", fname.string());
    std::throw_with_nested(kcv::make_exception_with_context(std::move(msg)));
}

}  // namespace detail
}  // namespace kcv

template <typename T>
void kcv::read_json(T& dst, const std::string& buffer) {
    constexpr auto opts = glz::opts{
        // svdataにapi_dataが存在しない場合があり, このときmissing_keyエラーが出てしまうため, エラーとしない.
        // .error_on_missing_keys = true,
    };
    kcv::detail::read_json_impl<opts>(dst, buffer);
}

template <typename T>
void kcv::read_json(T& dst, const std::filesystem::path& fname) {
    constexpr auto opts = glz::opts{
        // svdataにapi_dataが存在しない場合があり, このときmissing_keyエラーが出てしまうため, エラーとしない.
        // .error_on_missing_keys = true,
    };
    kcv::detail::read_json_impl<opts>(dst, fname);
}
