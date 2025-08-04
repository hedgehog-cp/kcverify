#ifndef KCVERIFY_MODELS_KCSAPI_API_PORT_PORT_RESPONSE_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_API_PORT_PORT_RESPONSE_HPP_INCLUDED

// std
#include <cstdint>
#include <optional>
#include <vector>

// kcv
#include "models/kcsapi/types/api_basic.hpp"
#include "models/kcsapi/types/api_deck_port.hpp"
#include "models/kcsapi/types/api_event_object.hpp"
#include "models/kcsapi/types/api_log.hpp"
#include "models/kcsapi/types/api_material.hpp"
#include "models/kcsapi/types/api_ndock.hpp"
#include "models/kcsapi/types/api_plane_info.hpp"
#include "models/kcsapi/types/api_ship.hpp"

namespace kcv {
namespace kcsapi {
namespace api_port {
namespace port {

/// @brief api_port/port.json
struct response final {
    /// @brief 艦隊司令部情報.
    kcv::kcsapi::api_basic api_basic;

    /// @brief ギミック達成フラグ.
    std::optional<std::int32_t> api_c_flag;

    /// @brief 連合艦隊フラグ 0=未結成, 1=機動部隊, 2=水上部隊, 3=輸送部隊,
    /// -x=強制解隊(-1=機動部隊解隊, -2=水上部隊解隊, ... 解体等で編成が変わった時に発生).
    std::optional<std::int32_t> api_combind_flag;

    /// @brief 艦隊情報.
    kcv::kcsapi::api_deck_port api_deck_port;

    /// @brief 解体時の装備廃棄フラグ. 0=保管, 1=廃棄.
    std::int32_t api_dest_ship_slot;

    /// @brief
    std::optional<kcv::kcsapi::api_event_object> api_event_object;

    /// @brief 母港下の通知欄.
    std::vector<kcv::kcsapi::api_log> api_log;

    /// @brief 資源情報.
    std::vector<kcv::kcsapi::api_material> api_material;

    /// @brief 入渠ドック.
    std::vector<kcv::kcsapi::api_ndock> api_ndock;

    /// @brief 母港BGMのID.
    std::int32_t api_p_bgm_id;

    /// @brief 最大受領可能任務数.
    std::int32_t api_parallel_quest_count;

    /// @brief 基地航空隊関連データ. 要素があるときのみ存在(メンバも然り).
    std::optional<kcv::kcsapi::api_plane_info> api_plane_info;

    /// @brief 所属艦船情報.
    std::vector<kcv::kcsapi::api_ship> api_ship;
};

}  // namespace port
}  // namespace api_port
}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_API_PORT_PORT_RESPONSE_HPP_INCLUDED
