#ifndef KCVERIFY_SORTIE_DATA_SORTIE_DATA_HPP_INCLUDED
#define KCVERIFY_SORTIE_DATA_SORTIE_DATA_HPP_INCLUDED

// std
#include <cstdlib>

// glz
#include <glaze/json.hpp>
#include <variant>

// kcv
#include "eoen/database/kancolle_api/api_file_type.hpp"
#include "eoen/database/sortie/sortie_record.hpp"
#include "json/read_json.hpp"
#include "kcsapi/api_req_battle_midnight/battle/response.hpp"
#include "kcsapi/api_req_map/start/request.hpp"
#include "kcsapi/api_req_map/start/response.hpp"
#include "kcsapi/api_req_sortie/battle/response.hpp"
#include "kcsapi/api_req_sortie/battleresult/response.hpp"
#include "kcsapi/types/svdata.hpp"
#include "sortie_data/fleet_data.hpp"
#include "sortie_data/map_data.hpp"

namespace kcv {

using sortie_api = std::variant<
    std::monostate,

    // [出撃選択]
    // api_get_member/mapinfo

    // [出撃]
    // api_req_map/start
    kcsapi::api_req_map::start::request,  //
    kcsapi::svdata<kcsapi::api_req_map::start::response>,

    // [戦闘-昼戦]
    // api_req_sortie/battle
    kcsapi::svdata<kcsapi::api_req_sortie::battle::response>,

    // [夜戦]
    // api_req_battle_midnight/battle
    kcsapi::svdata<kcsapi::api_req_battle_midnight::battle::response>,

    // [戦闘終了]
    // api_req_sortie/battleresult
    kcsapi::svdata<kcsapi::api_req_sortie::battleresult::response>

    // [進撃]
    // api_get_member/ship_deck
    // api_req_map/next

    // [超重爆迎撃戦闘開始]
    // api_req_map/air_raid

    // [緊急泊地修理承諾]
    // api_req_map/anchorage_repair

    // [帰投]
    // api_port/port
    // api_get_member/slot_item
    // api_get_member/unsetslot
    // api_get_member/useitem
    >;

class sortie_data final {
   public:
    using eoen_type = eoen::database::sortie::sortie_record;

    static auto from_eoen(
        const eoen_type& src, const kcsapi::api_mst_ship& mst_ship, const kcsapi::api_mst_slotitem& mst_slotitem
    ) -> sortie_data {
        auto result = sortie_data{
            src.id,
            src.version,
            src.world,
            src.map,
            src.api_files  //
                | std::ranges::views::transform([](const auto& e) -> kcv::sortie_api {
                      const auto& type    = e.api_file_type;
                      const auto& name    = e.name;
                      const auto& content = e.content;
                      using api_file_type = kcv::eoen::database::kancolle_api::api_file_type;

                      if (type == api_file_type::request and name == "api_req_map/start") {
                          auto data = kcv::kcsapi::api_req_map::start::request{};
                          kcv::read_json(data, content);
                          return data;
                      }
                      if (type == api_file_type::response and name == "api_req_map/start") {
                          auto data = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>{};
                          kcv::read_json(data, content);
                          return data;
                      }
                      if (type == api_file_type::response and name == "api_req_sortie/battle") {
                          auto data = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>{};
                          kcv::read_json(data, content);
                          return data;
                      }
                      if (type == api_file_type::response and name == "api_req_battle_midnight/battle") {
                          auto data = kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>{};
                          kcv::read_json(data, content);
                          return data;
                      }
                      if (type == api_file_type::response and name == "api_req_sortie/battleresult") {
                          auto data = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>{};
                          kcv::read_json(data, content);
                          return data;
                      }
                      return std::monostate{};
                  })
                | std::ranges::to<std::vector>(),
            fleet_data::from_eoen(src.fleet_data, mst_ship, mst_slotitem),
            src.fleet_after_sortie_data.transform([&](const auto& e) {
                return fleet_data::from_eoen(e, mst_ship, mst_slotitem);
            }),
            map_data::from_eoen(src.map_data),
        };

        return result;
    }

    constexpr sortie_data() = default;

    constexpr sortie_data(
        std::int32_t id, int version, int world, int map, std::vector<sortie_api> sortie_api,
        kcv::fleet_data fleet_data, std::optional<kcv::fleet_data> fleet_after_sortie_data, kcv::map_data map_data
    )
        : id_{id}
        , version_{version}
        , world_{world}
        , map_{map}
        , sortie_api_{std::move(sortie_api)}
        , fleet_data_{std::move(fleet_data)}
        , fleet_after_sortie_data_{std::move(fleet_after_sortie_data)}
        , map_data_{std::move(map_data)} {
    }

    constexpr auto id() const noexcept -> std::int32_t {
        return this->id_;
    }

    constexpr int version() const noexcept {
        return this->version_;
    }

    constexpr int world() const noexcept {
        return this->world_;
    }

    constexpr int map() const noexcept {
        return this->map_;
    }

    constexpr auto sortie_api() const noexcept -> const std::vector<sortie_api>& {
        return this->sortie_api_;
    }

    constexpr auto fleet_data() const noexcept -> const fleet_data& {
        return this->fleet_data_;
    }

    constexpr auto fleet_after_sortie_data() const noexcept -> const std::optional<kcv::fleet_data>& {
        return this->fleet_after_sortie_data_;
    }

    constexpr auto map_data() const noexcept -> const map_data& {
        return this->map_data_;
    }

   private:
    std::int32_t id_;
    int version_;
    int world_;
    int map_;
    std::vector<kcv::sortie_api> sortie_api_;
    kcv::fleet_data fleet_data_;
    std::optional<kcv::fleet_data> fleet_after_sortie_data_;
    kcv::map_data map_data_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_DATA_SORTIE_DATA_HPP_INCLUDED
