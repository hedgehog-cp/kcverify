#ifndef KCVERIFY_MODELS_EOEN_DESTINATION_HPP_INCLUDED
#define KCVERIFY_MODELS_EOEN_DESTINATION_HPP_INCLUDED

#include <charconv>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <regex>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <vector>

// namespace kcv {
// namespace eoen {

// class world_t final {
//    public:
//     /// @todo 例えば<chaconv>を使った実装に変更する.
//     explicit world_t(std::string_view destination_key) {
//         static const auto regex = std::regex{"World (\\d+)-(\\d+)"};
//         if (auto m = std::cmatch{}; std::regex_search(destination_key.begin(), destination_key.end(), m, regex)) {
//             const auto world = m.str(1);
//             std::from_chars(world.data(), world.data() + world.size(), this->world_);

//             const auto map = m.str(2);
//             std::from_chars(map.data(), map.data() + map.size(), this->map_);
//         }
//     }

//     constexpr auto world() const noexcept -> std::int32_t {
//         return this->world_;
//     }

//     constexpr auto map() const noexcept -> std::int32_t {
//         return this->map_;
//     }

//    private:
//     std::int32_t world_;
//     std::int32_t map_;
// };

// }  // namespace eoen
// }  // namespace kcv

// template <>
// struct std::hash<kcv::eoen::world_t> final {
//     auto operator()(const kcv::eoen::world_t& v) const noexcept -> std::size_t {
//         // とりあえず64bitにしてhashをとる.
//         return std::hash<std::int64_t>{}(static_cast<std::int64_t>(v.world() << 31) | v.map());
//     }
// };

namespace kcv {
namespace eoen {

struct destination final {
    std::int32_t version;
    std::unordered_map<std::string, std::unordered_map<std::int32_t, std::tuple<std::string, std::string>>> worlds;
};

}  // namespace eoen
}  // namespace kcv

#endif  // KCVERIFY_MODELS_EOEN_DESTINATION_HPP_INCLUDED
