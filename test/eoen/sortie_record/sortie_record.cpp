// std
#include <filesystem>
#include <variant>
#include <vector>

// kcv
#include "eoen/database/kancolle_api/api_file_type.hpp"
#include "eoen/database/kancolle_api/api_files.hpp"
#include "eoen/database/sortie/sortie_record.hpp"
#include "json/read_json.hpp"
#include "kcsapi/api_req_battle_midnight/battle/response.hpp"
#include "kcsapi/api_req_map/start/request.hpp"
#include "kcsapi/api_req_map/start/response.hpp"
#include "kcsapi/api_req_sortie/battle/response.hpp"
#include "kcsapi/api_req_sortie/battleresult/response.hpp"
#include "kcsapi/types/svdata.hpp"

// kcv::test
#include "root.hpp"

namespace {

using api_datum = std::variant<
    std::monostate,                                                               //
    kcv::kcsapi::api_req_map::start::request,                                     //
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>,               //
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>,           //
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>,  //
    kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>      //
    >;

void parse_api(std::vector<api_datum> &dst, const std::vector<kcv::eoen::database::kancolle_api::api_files> &src) {
    for (const auto &e : src) {
        const auto &type    = e.api_file_type;
        const auto &name    = e.name;
        const auto &content = e.content;

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
    }
}

}  // namespace

int main() {
    const auto dir = kcv::test::root / "test/eoen/sortie_record/sortie_record";

    constexpr auto opt = glz::opts{
        .append_arrays = true,
    };

    auto sortie_records = std::vector<kcv::eoen::database::sortie::sortie_record>{};

    for (const auto &f : std::filesystem::directory_iterator{dir}) {
        kcv::read_json<opt>(sortie_records, f.path());
    }

    auto api_data = std::vector<api_datum>{};

    for (const auto &sortie_record : sortie_records) {
        parse_api(api_data, sortie_record.api_files);
    }
}