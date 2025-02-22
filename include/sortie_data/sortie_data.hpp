#ifndef KCVERIFY_SORTIE_DATA_SORTIE_DATA_HPP_INCLUDED
#define KCVERIFY_SORTIE_DATA_SORTIE_DATA_HPP_INCLUDED

// std
#include <cstdlib>
#include <variant>
#include <vector>

// glz
#include <glaze/json.hpp>

// kcv
#include "eoen/database/kancolle_api/api_file_type.hpp"
#include "eoen/database/sortie/sortie_record.hpp"
#include "json/read_json.hpp"
#include "kcsapi/api_get_member/ship_deck/response.hpp"
#include "kcsapi/api_req_battle_midnight/battle/response.hpp"
#include "kcsapi/api_req_map/next/response.hpp"
#include "kcsapi/api_req_map/start/request.hpp"
#include "kcsapi/api_req_map/start/response.hpp"
#include "kcsapi/api_req_sortie/battle/response.hpp"
#include "kcsapi/api_req_sortie/battleresult/response.hpp"
#include "kcsapi/api_start2/api_mst_ship.hpp"
#include "kcsapi/api_start2/api_mst_slotitem.hpp"
#include "kcsapi/types/svdata.hpp"
#include "sortie_data/fleet_data.hpp"
#include "sortie_data/map_data.hpp"

namespace kcv {

// clang-format off

/// @brief 出撃API.
using sortie_api = std::variant<
    std::monostate,
    kcv::kcsapi::api_req_map::start::request,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>,
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>
>;

// clang-format on

class sortie_data final {
   public:
    using eoen_type = kcv::eoen::database::sortie::sortie_record;

    static auto from_eoen(
        const eoen_type &src, const kcv::kcsapi::api_mst_ship &api_mst_ship,
        const kcv::kcsapi::api_mst_slotitem &api_mst_slotitem
    ) -> sortie_data {
        constexpr auto parse_api_files
            = [](std::vector<kcv::sortie_api> &dst,
                 const std::vector<kcv::eoen::database::kancolle_api::api_files> &src) static -> void {
            for (const auto &e : src) {
                const auto &type    = e.api_file_type;
                const auto &name    = e.name;
                const auto &content = e.content;

                // std::vectorの要素をapi構造体Tで初期化し(emplace_back),
                // その初期化された領域にTとしてapiを読み込む(read_json).
                using std::literals::string_view_literals::operator""sv;
                using file_type = kcv::eoen::database::kancolle_api::api_file_type;
                if (name == "api_req_map/start"sv and type == file_type::request) {
                    using T = kcv::kcsapi::api_req_map::start::request;
                    kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content, std::format("{}/request", name));
                }
                if (name == "api_req_map/start"sv and type == file_type::response) {
                    using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>;
                    kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content, std::format("{}/response", name));
                }
                if (name == "api_req_sortie/battle"sv and type == file_type::response) {
                    using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>;
                    kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content, std::format("{}/response", name));
                }
                if (name == "api_req_battle_midnight/battle"sv and type == file_type::response) {
                    using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>;
                    kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content, std::format("{}/response", name));
                }
                if (name == "api_req_sortie/battleresult"sv and type == file_type::response) {
                    using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>;
                    kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content, std::format("{}/response", name));
                }
                if (name == "api_get_member/ship_deck"sv and type == file_type::response) {
                    using T = kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>;
                    kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content, std::format("{}/response", name));
                }
                if (name == "api_req_map/next"sv and type == file_type::response) {
                    using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>;
                    kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content, std::format("{}/response", name));
                }
            }
        };

        auto api_files = std::vector<kcv::sortie_api>{};
        parse_api_files(api_files, src.api_files);

        return sortie_data{
            src.world,
            src.map,
            std::move(api_files),
            kcv::fleet_data::from_eoen(src.fleet_data, api_mst_ship, api_mst_slotitem),
            src.fleet_after_sortie_data.transform([&](const auto &e) {
                return kcv::fleet_data::from_eoen(e, api_mst_ship, api_mst_slotitem);
            }),
            kcv::map_data::from_eoen(src.map_data),
        };

        // auto result = sortie_data{
        //     src.world,
        //     src.map,
        //     src.api_files  //
        //         | std::ranges::views::transform([](const auto& e) -> kcv::sortie_api {
        //               const auto& type    = e.api_file_type;
        //               const auto& name    = e.name;
        //               const auto& content = e.content;
        //               using api_file_type = kcv::eoen::database::kancolle_api::api_file_type;

        //               if (type == api_file_type::request and name == "api_req_map/start") {
        //                   auto data = kcv::kcsapi::api_req_map::start::request{};
        //                   kcv::read_json(data, content);
        //                   return data;
        //               }
        //               if (type == api_file_type::response and name == "api_req_map/start") {
        //                   auto data = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>{};
        //                   kcv::read_json(data, content);
        //                   return data;
        //               }
        //               if (type == api_file_type::response and name == "api_req_sortie/battle") {
        //                   auto data = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>{};
        //                   kcv::read_json(data, content);
        //                   return data;
        //               }
        //               if (type == api_file_type::response and name == "api_req_battle_midnight/battle") {
        //                   auto data = kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>{};
        //                   kcv::read_json(data, content);
        //                   return data;
        //               }
        //               if (type == api_file_type::response and name == "api_req_sortie/battleresult") {
        //                   auto data = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>{};
        //                   kcv::read_json(data, content);
        //                   return data;
        //               }
        //               return std::monostate{};
        //           })
        //         | std::ranges::to<std::vector>(),
        //     kcv::fleet_data::from_eoen(src.fleet_data, api_mst_ship, api_mst_slotitem),
        //     src.fleet_after_sortie_data.transform([&](const auto& e) {
        //         return kcv::fleet_data::from_eoen(e, api_mst_ship, api_mst_slotitem);
        //     }),
        //     kcv::map_data::from_eoen(src.map_data),
        // };

        // return result;
    }

    // clang-format off

    constexpr sortie_data(
        std::int32_t world,
        std::int32_t map,
        std::vector<sortie_api> sortie_api,
        kcv::fleet_data fleet_data,
        std::optional<kcv::fleet_data> fleet_after_sortie_data,
        kcv::map_data map_data
    )
        : world_{std::move(world)}
        , map_{std::move(map)}
        , sortie_api_{std::move(sortie_api)}
        , fleet_data_{std::move(fleet_data)}
        , fleet_after_sortie_data_{std::move(fleet_after_sortie_data)}
        , map_data_{std::move(map_data)} {}

    // clang-format on

    constexpr auto world() const noexcept -> decltype(auto) {
        return (this->world_);
    }

    constexpr auto map() const noexcept -> decltype(auto) {
        return (this->map_);
    }

    constexpr auto sortie_api() const noexcept -> decltype(auto) {
        return (this->sortie_api_);
    }

    constexpr auto fleet_data() const noexcept -> decltype(auto) {
        return (this->fleet_data_);
    }

    constexpr auto fleet_after_sortie_data() const noexcept -> decltype(auto) {
        return (this->fleet_after_sortie_data_);
    }

    constexpr auto map_data() const noexcept -> decltype(auto) {
        return (this->map_data_);
    }

   private:
    /// @brief 74式ENの何某かの管理用ID.
    // std::int32_t id_;

    /// @brief 74式ENの何某かの管理用Version.
    // std::int32_t version_;

    /// @brief 海域. #5-3-Pに対する5.
    std::int32_t world_;

    /// @brief 海域. #5-3-Pに対する3.
    std::int32_t map_;

    /// @brief この出撃中に送受信したAPI
    std::vector<kcv::sortie_api> sortie_api_;

    /// @brief 出撃前艦隊データ.
    kcv::fleet_data fleet_data_;

    /// @brief 出撃後艦隊データ.
    std::optional<kcv::fleet_data> fleet_after_sortie_data_;

    /// @brief 海域攻略進捗データ.
    kcv::map_data map_data_;
};

}  // namespace kcv

#endif  // KCVERIFY_SORTIE_DATA_SORTIE_DATA_HPP_INCLUDED
