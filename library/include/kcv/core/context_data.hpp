#ifndef KCV_CORE_CONTEXT_DATA_HPP_INCLUDED
#define KCV_CORE_CONTEXT_DATA_HPP_INCLUDED

// std
#include <cstdint>
#include <filesystem>
#include <format>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// kcv
#include "kcv/core/json/read_json.hpp"
#include "kcv/external/eoen/destination.hpp"
#include "kcv/external/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "kcv/external/kc3kai/bonus/bonus.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_ship.hpp"
#include "kcv/external/kcsapi/api_start2/api_mst_slotitem.hpp"

namespace kcv {

class context_data final {
   public:
    context_data() = default;

    void api_mst_ship(const std::filesystem::path& fname) {
        kcv::read_json(this->api_mst_ship_, fname);
    }

    const auto& api_mst_ship() const noexcept {
        return this->api_mst_ship_;
    }

    void api_mst_slotitem(const std::filesystem::path& fname) {
        kcv::read_json(this->api_mst_slotitem_, fname);
    }

    const auto& api_mst_slotitem() const noexcept {
        return this->api_mst_slotitem_;
    }

    void destination(const std::filesystem::path& fname) {
        kcv::read_json(this->destination_, fname);
    }

    const auto& destination() const noexcept {
        return this->destination_;
    }

    void fit_bonuses(const std::filesystem::path& fname) {
        kcv::read_json(this->fit_bonuses_, fname);
    }

    const auto& fit_bonuses() const noexcept {
        return this->fit_bonuses_;
    }

    void map_bonus(const std::filesystem::path& fname) {
        // "5-3" <- "PATH/TO/5-3.json"
        auto key = fname.stem().string();

        auto data = kcv::kc3kai::bonus_map_t{};
        kcv::read_json(data, fname);

        this->map_bonuses_[std::move(key)] = std::move(data);
    }

    const auto& map_bonuse(std::int32_t world, std::int32_t map) const noexcept {
        // is_transparentの設定が面倒なのでstd::stringにフォーマットする.
        // サイズが小さいためstd::stringの動的確保は発生しないと思う.
        // TODO: キーを文字列でない適切なものに直す.
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

#endif  // KCV_CORE_CONTEXT_DATA_HPP_INCLUDED
