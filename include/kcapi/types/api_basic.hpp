#ifndef KCVERIFY_KCAPI_TYPES_API_BASIC_HPP_INCLUDED
#define KCVERIFY_KCAPI_TYPES_API_BASIC_HPP_INCLUDED

#include <optional>
#include <string>
#include <vector>

namespace kcv {
namespace kcapi {

/// @brief 艦隊司令部情報.
struct api_basic final {
    /// @brief
    int api_active_flag;

    /// @brief 提督コメント.
    std::string api_comment;

    /// @brief
    std::string api_comment_id;

    /// @brief 保有艦隊数.
    int api_count_deck;

    /// @brief 工廠ドック数.
    int api_count_kdock;

    /// @brief 入渠ドック数.
    int api_count_ndock;

    /// @brief 提督経験値.
    int api_experience;

    /// @brief 家具コイン数.
    int api_fcoin;

    /// @brief
    int api_firstflag;

    /// @brief
    std::optional<std::string> api_fleetname;

    /// @brief 設置している家具ID.
    std::vector<int> api_furniture;

    /// @brief 大型艦建造可否.
    int api_large_dock;

    /// @brief 艦隊司令部Lv.
    int api_level;

    /// @brief 最大保有可能艦娘数.
    int api_max_chara;

    /// @brief
    int api_max_kagu;

    /// @brief 最大保有可能装備数.
    int api_max_slotitem;

    /// @brief 甲種勲章保有数.
    int api_medals;

    /// @brief 提督ID.
    std::string api_member_id;

    /// @brief 遠征回数.
    int api_ms_count;

    /// @brief 遠征成功回数.
    int api_ms_success;

    /// @brief 提督名.
    std::string api_nickname;

    /// @brief
    std::string api_nickname_id;

    /// @brief
    int api_playtime;

    /// @brief
    int api_pt_challenged;

    /// @brief
    int api_pt_challenged_win;

    /// @brief 演習敗北回数.
    int api_pt_lose;

    /// @brief 演習勝利回数.
    int api_pt_win;

    /// @brief
    std::vector<int> api_pvp;

    /// @brief 階級 1から 元帥, 大将, 中将, 少将, 大佐, 中佐, 新米中佐, 少佐, 中堅少佐, 新米少佐.
    int api_rank;

    /// @brief 出撃敗北回数.
    int api_st_lose;

    /// @brief 演習勝利回数.
    int api_st_win;

    /// @brief 起動日時(≠着任日時, 今回のログイン時の時間).
    long api_starttime;

    /// @brief
    int api_tutorial;

    /// @brief チュートリアル進捗?.
    int api_tutorial_progress;
};

}  // namespace kcapi
}  // namespace kcv

#endif  // KCVERIFY_KCAPI_TYPES_API_BASIC_HPP_INCLUDED
