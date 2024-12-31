#ifndef KCVERIFY_SORTIE_DATA_SORTIE_DATA_HPP_INCLUDED
#define KCVERIFY_SORTIE_DATA_SORTIE_DATA_HPP_INCLUDED

// std
#include <cstdlib>

// glz
#include <glaze/json.hpp>

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
            std::nullopt,  // src.api_req_battle_midnight_battle_response,
            std::nullopt,  // src.api_req_map_start_request,
            std::nullopt,  // src.api_req_map_start_response,
            std::nullopt,  // src.api_req_sortie_battle_response,
            std::nullopt,  // src.api_req_sortie_battleresult_response,
            fleet_data::from_eoen(src.fleet_data, mst_ship, mst_slotitem),
            src.fleet_after_sortie_data.transform([&](const auto& e) {
                return fleet_data::from_eoen(e, mst_ship, mst_slotitem);
            }),
            map_data::from_eoen(src.map_data),
        };

        // XXX: たとえば, e.api_file_type == request and e.name == "api_req_map/start"を満たすeがfilesに複数あるとき,
        // これをエラーにできない.
        for (const auto& e : src.api_files) {
            // alias
            const auto& type    = e.api_file_type;
            const auto& name    = e.name;
            const auto& content = e.content;

            switch (type) {
                using api_file_type = eoen::database::kancolle_api::api_file_type;

                case api_file_type::request:
                    if (name == "api_req_map/start") kcv::read_json(result.api_req_map_start_request_, content);
                    break;

                case api_file_type::response:
                    if (name == "api_req_map/start") {
                        kcv::read_json(result.api_req_map_start_response_, content);
                    } else if (name == "api_req_sortie/battle") {
                        kcv::read_json(result.api_req_sortie_battle_response_, content);
                    } else if (name == "api_req_battle_midnight/battle") {
                        kcv::read_json(result.api_req_battle_midnight_battle_response_, content);
                    } else if (name == "api_req_sortie/battleresult") {
                        kcv::read_json(result.api_req_sortie_battleresult_response_, content);
                    }
                    break;
            }
        }

        return result;
    }

    constexpr sortie_data() = default;

    constexpr sortie_data(
        std::int32_t id, int version, int world, int map,
        std::optional<kcsapi::svdata<kcsapi::api_req_battle_midnight::battle::response>>
            api_req_battle_midnight_battle_response,
        std::optional<kcsapi::api_req_map::start::request> api_req_map_start_request,
        std::optional<kcsapi::svdata<kcsapi::api_req_map::start::response>> api_req_map_start_response,
        std::optional<kcsapi::svdata<kcsapi::api_req_sortie::battle::response>> api_req_sortie_battle_response,
        std::optional<kcsapi::svdata<kcsapi::api_req_sortie::battleresult::response>>
            api_req_sortie_battleresult_response,
        kcv::fleet_data fleet_data, std::optional<kcv::fleet_data> fleet_after_sortie_data, kcv::map_data map_data
    )
        : id_{id}
        , version_{version}
        , world_{world}
        , map_{map}
        , api_req_battle_midnight_battle_response_{api_req_battle_midnight_battle_response}
        , api_req_map_start_request_{api_req_map_start_request}
        , api_req_map_start_response_{api_req_map_start_response}
        , api_req_sortie_battle_response_{api_req_sortie_battle_response}
        , api_req_sortie_battleresult_response_{api_req_sortie_battleresult_response}
        , fleet_data_{fleet_data}
        , fleet_after_sortie_data_{fleet_after_sortie_data}
        , map_data_{map_data} {
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

    constexpr auto api_req_battle_midnight_battle_response() const noexcept -> decltype(auto) {
        return (this->api_req_battle_midnight_battle_response_);
    }

    constexpr auto api_req_map_start_request() const noexcept -> decltype(auto) {
        return (this->api_req_map_start_request_);
    }

    constexpr auto api_req_map_start_response() const noexcept -> decltype(auto) {
        return (this->api_req_map_start_response_);
    }

    constexpr auto api_req_sortie_battle_response() const noexcept -> decltype(auto) {
        return (this->api_req_sortie_battle_response_);
    }

    constexpr auto api_req_sortie_battleresult_response() const noexcept -> decltype(auto) {
        return (this->api_req_sortie_battleresult_response_);
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
    std::optional<kcsapi::svdata<kcsapi::api_req_battle_midnight::battle::response>>
        api_req_battle_midnight_battle_response_;
    std::optional<kcsapi::api_req_map::start::request> api_req_map_start_request_;
    std::optional<kcsapi::svdata<kcsapi::api_req_map::start::response>> api_req_map_start_response_;
    std::optional<kcsapi::svdata<kcsapi::api_req_sortie::battle::response>> api_req_sortie_battle_response_;
    std::optional<kcsapi::svdata<kcsapi::api_req_sortie::battleresult::response>> api_req_sortie_battleresult_response_;
    kcv::fleet_data fleet_data_;
    std::optional<kcv::fleet_data> fleet_after_sortie_data_;
    kcv::map_data map_data_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_DATA_SORTIE_DATA_HPP_INCLUDED
