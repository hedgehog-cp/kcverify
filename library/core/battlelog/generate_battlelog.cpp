#include "core/battlelog/generate_battlelog.hpp"

// std
#include <fstream>
#include <utility>
#include <variant>
#include <vector>

// kcv
#include "core/battlelog/battlelog.hpp"
#include "core/battlelog/process_api.hpp"
#include "core/entity/adapter/from_eoen.hpp"
#include "core/utility/read_json.hpp"
#include "extensions/exception.hpp"
#include "extensions/formatter.hpp"
#include "models/eoen/database/kancolle_api/api_files.hpp"
#include "models/eoen/database/sortie/sortie_record.hpp"
#include "models/eoen/serialization/fit_bonus/fit_bonus_per_equipment.hpp"
#include "models/kcsapi/api_get_member/ship_deck/response.hpp"
#include "models/kcsapi/api_req_battle_midnight/battle/response.hpp"
#include "models/kcsapi/api_req_battle_midnight/sp_midnight/response.hpp"
#include "models/kcsapi/api_req_combined_battle/battle_water/response.hpp"
#include "models/kcsapi/api_req_combined_battle/battleresult/response.hpp"
#include "models/kcsapi/api_req_combined_battle/ec_battle/response.hpp"
#include "models/kcsapi/api_req_combined_battle/ec_midnight_battle/response.hpp"
#include "models/kcsapi/api_req_combined_battle/midnight_battle/response.hpp"
#include "models/kcsapi/api_req_map/next/response.hpp"
#include "models/kcsapi/api_req_map/start/request.hpp"
#include "models/kcsapi/api_req_map/start/response.hpp"
#include "models/kcsapi/api_req_map/start_air_base/request.hpp"
#include "models/kcsapi/api_req_map/start_air_base/response.hpp"
#include "models/kcsapi/api_req_sortie/battle/response.hpp"
#include "models/kcsapi/api_req_sortie/battleresult/response.hpp"
#include "models/kcsapi/api_req_sortie/ld_airbattle/response.hpp"
#include "models/kcsapi/api_start2/api_mst_ship.hpp"
#include "models/kcsapi/api_start2/api_mst_slotitem.hpp"

namespace {

/// @brief 74式ENのAPIファイルを出撃APIに解析する.
/// @param dst 出力先の出撃API.
/// @param src 入力元の74式ENAPIファイル.
/// @details 候補型のいずれかの型でデフォルト初期化してから出撃APIを読み込むため, 呼び出し側の初期化に注意.
void parse_api_file(kcv::sortie_api& dst, const kcv::eoen::database::kancolle_api::api_files& src) {
    const auto& name    = src.name;
    const auto& type    = src.api_file_type;
    const auto& content = src.content;

    using std::literals::string_view_literals::operator""sv;
    using file_type = kcv::eoen::database::kancolle_api::api_file_type;

    if (name == "api_get_member/ship_deck"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_get_member::ship_deck::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_battle_midnight/battle"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::battle::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_battle_midnight/sp_midnight"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_battle_midnight::sp_midnight::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_combined_battle/battle_water"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::battle_water::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_combined_battle/battleresult"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::battleresult::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_combined_battle/ec_battle"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ec_battle::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_combined_battle/ec_midnight_battle"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::ec_midnight_battle::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_combined_battle/midnight_battle"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_combined_battle::midnight_battle::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_map/next"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::next::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_map/start"sv and type == file_type::request) {
        using T = kcv::kcsapi::api_req_map::start::request;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_map/start"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_map/start_air_base"sv and type == file_type::request) {
        using T = kcv::kcsapi::api_req_map::start_air_base::request;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_map/start_air_base"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_map::start_air_base::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_sortie/battle"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battle::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_sortie/battleresult"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::battleresult::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_sortie/goback_port"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::goback_port::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    if (name == "api_req_sortie/ld_airbattle"sv and type == file_type::response) {
        using T = kcv::kcsapi::svdata<kcv::kcsapi::api_req_sortie::ld_airbattle::response>;
        kcv::read_json(dst.emplace<T>(), content);
        return;
    }

    std::ofstream{"execlog.json"} << content << std::endl;
    throw kcv::exception{
        std::format(
            "failed to parse api file."
            "[id = {}, api_file_type = {}, name = {}, time_stamp = {}, version = {}, sortie_record_id = {}], "
            "see execlog.json.",
            src.id, std::to_underlying(src.api_file_type), src.name, src.time_stamp, src.version, src.sortie_record_id
        ),
    };
}

}  // namespace

auto kcv::generate_battlelog(
    const kcv::kcsapi::api_mst_ship& api_mst_ship,
    const kcv::kcsapi::api_mst_slotitem& api_mst_slotitem,
    const std::vector<kcv::eoen::serialization::fit_bonus::fit_bonus_per_equipment>& fit_bonuses,
    const kcv::eoen::database::sortie::sortie_record& sortie_record
) -> std::vector<kcv::battlelog> {
    auto battlelogs = std::vector<kcv::battlelog>{};

    /// @brief `battlelogs`に書き込む基礎となる現在値あるいはキャッシュ値.
    /// 各`kcv::process_api`にて更新しながら`battlelogs`の末尾にコピー追加する.
    auto current             = kcv::battlelog{};
    current.girls_fleet_data = kcv::fleet_data_from_eoen(sortie_record.fleet_data, api_mst_ship, api_mst_slotitem);

    for (auto api = kcv::sortie_api{}; const auto& api_file : sortie_record.api_files) {
        parse_api_file(api, api_file);

        /// @brief 出撃APIにF5やその他何らかのエラーがある場合にtrueを設定して返る.
        bool error = false;

        std::visit(
            [&](const auto& api) {
                kcv::process_api(battlelogs, current, api, api_mst_ship, api_mst_slotitem, fit_bonuses, error);
            },
            api
        );

        if (error) {
            break;
        }
    }

    return battlelogs;
}