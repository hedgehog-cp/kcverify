#ifndef KCVERIFY_CORE_CONTEXT_DATA_HPP_INCLUDED
#define KCVERIFY_CORE_CONTEXT_DATA_HPP_INCLUDED

#include <cstdint>
#include <filesystem>
#include <format>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "core/json/read_json.hpp"
#include "models/eoen/destination.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/kc3kai/bonus/bonus.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"

namespace kcv {

class context_data final {
   public:
    context_data() = default;

    void api_mst_ship(const std::filesystem::path& fname) {
        kcv::read_json(this->api_mst_ship_, fname);
    }

    auto api_mst_ship() const noexcept -> decltype(auto) {
        return (this->api_mst_ship_);
    }

    void api_mst_slotitem(const std::filesystem::path& fname) {
        kcv::read_json(this->api_mst_slotitem_, fname);
    }

    auto api_mst_slotitem() const noexcept -> decltype(auto) {
        return (this->api_mst_slotitem_);
    }

    void destination(const std::filesystem::path& fname) {
        kcv::read_json(this->destination_, fname);
    }

    auto destination() const noexcept -> decltype(auto) {
        return (this->destination_);
    }

    void fit_bonuses(const std::filesystem::path& fname) {
        kcv::read_json(this->fit_bonuses_, fname);
    }

    auto fit_bonuses() const noexcept -> decltype(auto) {
        return (this->fit_bonuses_);
    }

    void map_bonus(const std::filesystem::path& fname) {
        // "5-3" <- "PATH/TO/5-3.json"
        auto key = fname.stem().string();

        auto data = kcv::kc3kai::bonus_map_t{};
        kcv::read_json(data, fname);

        this->map_bonuses_[std::move(key)] = std::move(data);
    }

    auto map_bonuse(std::int32_t world, std::int32_t map) const noexcept -> const kcv::kc3kai::bonus_map_t& {
        // is_transparentの設定が面倒なのでstd::stringにフォーマットする.
        // サイズが小さいためstd::stringの動的確保は発生しないと思う.
        // というかあとでキーを文字列でない適切なものに直す.
        const auto key = std::format("{}-{}", world, map);
        return this->map_bonuses_.at(key);
    }

   private:
    /// @brief 艦船マスタ.
    kcv::kcsapi::api_mst_ship api_mst_ship_;

    /// @brief 装備マスタ.
    kcv::kcsapi::api_mst_slotitem api_mst_slotitem_;

    /// @brief cell id <-> node name.
    kcv::eoen::destination destination_;

    /// @brief 装備ボーナスオブジェクト.
    std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment> fit_bonuses_;

    /// @brief 海域ボーナスオブジェクト. キーは"5-3"のような文字列(キーの型をあとで直す).
    std::unordered_map<std::string, kcv::kc3kai::bonus_map_t> map_bonuses_;
};

}  // namespace kcv

#endif  // KCVERIFY_CORE_CONTEXT_DATA_HPP_INCLUDED
