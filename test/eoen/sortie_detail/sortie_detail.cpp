// std
#include <array>
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>

// glz
#include <glaze/json.hpp>

// kcv
#include "eoen/database/kancolle_api/api_file_type.hpp"
#include "eoen/database/sortie/sortie_record.hpp"
#include "kcapi/api_req_battle_midnight/battle/response.hpp"
#include "kcapi/api_req_map/start/request.hpp"
#include "kcapi/api_req_map/start/response.hpp"
#include "kcapi/api_req_sortie/battle/response.hpp"
#include "kcapi/api_req_sortie/battleresult/response.hpp"
#include "kcapi/types/svdata.hpp"

// meta files
#include "eoen/database/kancolle_api/meta/api_files.hpp"
#include "eoen/database/sortie/meta/calculated_sortie_cost.hpp"
#include "eoen/database/sortie/meta/sorite_air_base_squadron.hpp"
#include "eoen/database/sortie/meta/sortie_air_base.hpp"
#include "eoen/database/sortie/meta/sortie_equipment.hpp"
#include "eoen/database/sortie/meta/sortie_equipment_slot.hpp"
#include "eoen/database/sortie/meta/sortie_fleet.hpp"
#include "eoen/database/sortie/meta/sortie_fleet_data.hpp"
#include "eoen/database/sortie/meta/sortie_map_data.hpp"
#include "eoen/database/sortie/meta/sortie_record.hpp"
#include "eoen/database/sortie/meta/sortie_ship.hpp"

// kcv::test
#include "root.hpp"

int main() {
    using sortie_record_t = kcv::eoen::database::sortie::sortie_record_t;
    using sortie_detail_t = std::vector<sortie_record_t>;

    const auto dir   = std::filesystem::path{"test/eoen/sortie_detail/"};
    const auto files = std::to_array<std::filesystem::path>({
        kcv::test::root / dir / "sortie_detail_1.json",
        kcv::test::root / dir / "sortie_detail_2.json",
        kcv::test::root / dir / "sortie_detail_3.json",
    });

    // read_jsonするとpush_backせずにデータが上書きされるので, 更に配列をネストして扱う.
    // イテレーションには, std::ranges::views::joinなどを使ってflatにする.
    auto sortie_details = std::vector<sortie_detail_t>(files.size());

    // read
    for (auto buffer = std::string{}; auto&& [fname, sortie_detail] : std::ranges::views::zip(files, sortie_details)) {
        buffer.resize_and_overwrite(std::filesystem::file_size(fname), [&](char* data, std::size_t size) {
            std::ifstream{fname}.read(data, size);
            return size;
        });

        if (const auto error = glz::read_json(sortie_detail, buffer); error) {
            return EXIT_FAILURE;
        }
    }

    // parse
    for (const auto& sortie_detail : sortie_details) {
        if (sortie_detail.size() != 1) continue;

        for (const auto& api_files = sortie_detail[0].api_files; const auto& api_file : api_files) {
            using file_type     = kcv::eoen::database::kancolle_api::api_file_type;
            const auto& type    = api_file.api_file_type;
            const auto& name    = api_file.name;
            const auto& content = api_file.content;

            constexpr auto parse = [](auto&& dst, const std::string& buffer) static -> void {
                if (const auto error = glz::read_json(dst, buffer); error) {
                    std::exit(EXIT_FAILURE);
                }

                if (const auto result = glz::write_json(dst); not result.has_value()) {
                    std::exit(EXIT_FAILURE);
                }
            };

            if (type == file_type::request and name == "api_req_map/start") {
                using value_type = kcv::kcapi::api_req_map::start::request;
                parse(value_type{}, content);
            }

            if (type == file_type::response and name == "api_req_map/start") {
                using value_type = kcv::kcapi::api_req_map::start::response;
                parse(kcv::kcapi::svdata<value_type>{}, content);
            }

            if (type == file_type::response and name == "api_req_sortie/battle") {
                using value_type = kcv::kcapi::api_req_sortie::battle::response;
                parse(kcv::kcapi::svdata<value_type>{}, content);
            }

            if (type == file_type::response and name == "api_req_battle_midnight/battle") {
                using value_type = kcv::kcapi::api_req_battle_midnight::battle::response;
                parse(kcv::kcapi::svdata<value_type>{}, content);
            }

            if (type == file_type::response and name == "api_req_sortie/battleresult") {
                using value_type = kcv::kcapi::api_req_sortie::battleresult::response;
                parse(kcv::kcapi::svdata<value_type>{}, content);
            }
        }
    }
}