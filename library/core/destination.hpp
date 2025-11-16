#ifndef KCVERIFY_CORE_DESTINATION_HPP_INCLUDED
#define KCVERIFY_CORE_DESTINATION_HPP_INCLUDED

// 未整理

// std
#include <cstdint>
#include <format>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

// glz
#include <glaze/json.hpp>

#include "extensions/ranges.hpp"

namespace kcv {

class world final {
   public:
    /// @brief destinationのworldから返る.
    explicit world(const glz::generic& world) noexcept
        : world_{world} {}

    /// @return ["Start", "A"],  ["A", "B"], ["Start 3", "X1"], etc...
    auto cell(std::int32_t cell) const -> kcv::ranges::range_of<std::string> auto {
        char buf[16]        = {};
        const auto [end, n] = std::format_to_n(buf, sizeof(buf) - sizeof('\0'), "{}", cell);
        const auto key      = std::string_view{buf, end};

        const auto& cells = this->world_.at(key);
        return cells.get<std::vector<glz::generic>>()
             | std::ranges::views::transform([](const auto& e) static -> const std::string& { return e.get_string(); });
    }

   private:
    const glz::generic& world_;
};

class destination final {
    friend struct glz::meta<destination>;

   public:
    // use kcv::read_json
    destination()
        : data_{} {}

    auto version() const -> const std::string& {
        return this->data_.at("version").get_string();
    }

    auto world(std::int32_t world, std::int32_t map) const -> kcv::world {
        char buf[32]        = {};
        const auto [end, n] = std::format_to_n(buf, sizeof(buf) - sizeof('\0'), "World {}-{}", world, map);
        const auto key      = std::string_view{buf, end};

        return kcv::world{this->data_.at(key)};
    }

   private:
    glz::generic data_;
};

}  // namespace kcv

template <>
struct glz::meta<kcv::destination> final {
    using T = kcv::destination;

    static constexpr auto value = &T::data_;
};

#endif  // KCVERIFY_CORE_DESTINATION_HPP_INCLUDED
