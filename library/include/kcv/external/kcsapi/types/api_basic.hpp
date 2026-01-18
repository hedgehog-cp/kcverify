#ifndef KCV_EXTERNAL_KCSAPI_TYPES_API_BASIC_HPP_INCLUDED
#define KCV_EXTERNAL_KCSAPI_TYPES_API_BASIC_HPP_INCLUDED

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace kcv {
namespace kcsapi {

/// @brief 艦隊司令部情報.
struct api_basic final {
    /// @brief
    std::int32_t api_active_flag;

    /// @brief 提督コメント.
    std::string api_comment;

    /// @brief
    std::string api_comment_id;

    /// @brief 保有艦隊数.
    std::int32_t api_count_deck;

    /// @brief 工廠ドック数.
    std::int32_t api_count_kdock;

    /// @brief 入渠ドック数.
    std::int32_t api_count_ndock;

    /// @brief 提督経験値.
    std::int32_t api_experience;

    /// @brief 家具コイン数.
    std::int32_t api_fcoin;

    /// @brief
    std::int32_t api_firstflag;

    /// @brief
    std::optional<std::string> api_fleetname;

    /// @brief 設置している家具ID.
    std::vector<std::int32_t> api_furniture;

    /// @brief 大型艦建造可否.
    std::int32_t api_large_dock;

    /// @brief 艦隊司令部Lv.
    std::int32_t api_level;

    /// @brief 最大保有可能艦娘数.
    std::int32_t api_max_chara;

    /// @brief
    std::int32_t api_max_kagu;

    /// @brief 最大保有可能装備数.
    std::int32_t api_max_slotitem;

    /// @brief 甲種勲章保有数.
    std::int32_t api_medals;

    /// @brief 提督ID.
    std::string api_member_id;

    /// @brief 遠征回数.
    std::int32_t api_ms_count;

    /// @brief 遠征成功回数.
    std::int32_t api_ms_success;

    /// @brief 提督名.
    std::string api_nickname;

    /// @brief
    std::string api_nickname_id;

    /// @brief
    std::int32_t api_playtime;

    /// @brief
    std::int32_t api_pt_challenged;

    /// @brief
    std::int32_t api_pt_challenged_win;

    /// @brief 演習敗北回数.
    std::int32_t api_pt_lose;

    /// @brief 演習勝利回数.
    std::int32_t api_pt_win;

    /// @brief
    std::vector<std::int32_t> api_pvp;

    /// @brief 階級 1から 元帥, 大将, 中将, 少将, 大佐, 中佐, 新米中佐, 少佐, 中堅少佐, 新米少佐.
    std::int32_t api_rank;

    /// @brief 出撃敗北回数.
    std::int32_t api_st_lose;

    /// @brief 演習勝利回数.
    std::int32_t api_st_win;

    /// @brief 起動日時(≠着任日時, 今回のログイン時の時間).
    std::int64_t api_starttime;

    /// @brief
    std::int32_t api_tutorial;

    /// @brief チュートリアル進捗?.
    std::int32_t api_tutorial_progress;
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCV_EXTERNAL_KCSAPI_TYPES_API_BASIC_HPP_INCLUDED
