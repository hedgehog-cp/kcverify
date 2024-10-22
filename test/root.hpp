#ifndef KCVERIFY_ROOT_HPP_INCLUDED
#define KCVERIFY_ROOT_HPP_INCLUDED

#include <filesystem>

namespace kcv::test {

/// @brief buildディレクトリから見たroot. buildディレクトリからctestを実行するため.
inline const auto root = std::filesystem::path{"../"};

}  // namespace kcv::test

#endif  // KCVERIFY_ROOT_HPP_INCLUDED
