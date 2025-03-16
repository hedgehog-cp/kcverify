#ifndef KCVERIFY_SORTIE_SORTIE_API_HPP_INCLUDED
#define KCVERIFY_SORTIE_SORTIE_API_HPP_INCLUDED

#include <variant>
#include <vector>

#include "eoen/database/kancolle_api/api_files.hpp"
#include "json/read_json.hpp"
#include "kcsapi/api_get_member/ship_deck/response.hpp"
#include "kcsapi/api_req_battle_midnight/battle/response.hpp"
#include "kcsapi/api_req_map/next/response.hpp"
#include "kcsapi/api_req_map/start/request.hpp"
#include "kcsapi/api_req_map/start/response.hpp"
#include "kcsapi/api_req_sortie/battle/response.hpp"
#include "kcsapi/api_req_sortie/battleresult/response.hpp"
#include "kcsapi/types/svdata.hpp"

namespace kcv {
namespace sortie {

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

inline void read_json(
    std::vector<kcv::sortie::sortie_api> &dst, const std::vector<kcv::eoen::database::kancolle_api::api_files> &src
) {
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
            kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content);
        }
        if (name == "api_req_map/start"sv and type == file_type::response) {
            using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>;
            kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content);
        }
        if (name == "api_req_sortie/battle"sv and type == file_type::response) {
            using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>;
            kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content);
        }
        if (name == "api_req_battle_midnight/battle"sv and type == file_type::response) {
            using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>;
            kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content);
        }
        if (name == "api_req_sortie/battleresult"sv and type == file_type::response) {
            using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>;
            kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content);
        }
        if (name == "api_get_member/ship_deck"sv and type == file_type::response) {
            using T = kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>;
            kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content);
        }
        if (name == "api_req_map/next"sv and type == file_type::response) {
            using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>;
            kcv::read_json(std::get<T>(dst.emplace_back<T>({})), content);
        }
    }
};

}  // namespace sortie
}  // namespace kcv

#endif  // KCVERIFY_SORTIE_SORTIE_API_HPP_INCLUDED
