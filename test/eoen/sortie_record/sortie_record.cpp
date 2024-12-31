// std
#include <filesystem>

// kcv
#include "eoen/database/sortie/sortie_record.hpp"
#include "json/read_json.hpp"
#include "kcapi/api_req_battle_midnight/battle/response.hpp"
#include "kcapi/api_req_map/start/request.hpp"
#include "kcapi/api_req_map/start/response.hpp"
#include "kcapi/api_req_sortie/battle/response.hpp"
#include "kcapi/api_req_sortie/battleresult/response.hpp"
#include "kcapi/types/svdata.hpp"

// kcv::test
#include "root.hpp"

int main() {
    const auto dir = kcv::test::root / "test/eoen/sortie_record/sortie_record";
    for (const auto& file : std::filesystem::directory_iterator{dir}) {
        auto sortie_records = std::vector<kcv::eoen::database::sortie::sortie_record>{};
        kcv::read_json(sortie_records, file.path());

        for (const auto& sortie_record = sortie_records.at(0); const auto& api_file : sortie_record.api_files) {
            const auto& type    = api_file.api_file_type;
            const auto& name    = api_file.name;
            const auto& content = api_file.content;

            using api_file_type = kcv::eoen::database::kancolle_api::api_file_type;
            if (type == api_file_type::request and name == "api_req_map/start") {
                auto data = kcv::kcapi::api_req_map::start::request{};
                kcv::read_json(data, content);
            }
            if (type == api_file_type::response and name == "api_req_map/start") {
                auto data = kcv::kcapi::svdata<kcv::kcapi::api_req_map::start::response>{};
                kcv::read_json(data, content);
            }
            if (type == api_file_type::response and name == "api_req_sortie/battle") {
                auto data = kcv::kcapi::svdata<kcv::kcapi::api_req_sortie::battle::response>{};
                kcv::read_json(data, content);
            }
            if (type == api_file_type::response and name == "api_req_battle_midnight/battle") {
                auto data = kcv::kcapi::svdata<kcv::kcapi::api_req_battle_midnight::battle::response>{};
                kcv::read_json(data, content);
            }
            if (type == api_file_type::response and name == "api_req_sortie/battleresult") {
                auto data = kcv::kcapi::svdata<kcv::kcapi::api_req_sortie::battleresult::response>{};
                kcv::read_json(data, content);
            }
        }
    }
}