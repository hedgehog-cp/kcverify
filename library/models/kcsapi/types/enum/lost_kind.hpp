#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_ENUM_LOST_KIND_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_ENUM_LOST_KIND_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

/// @brief 基地被害状況.
/// @note 各メンバ名は開発者が任意に定めたもので非公式.
enum class lost_kind {
    /// @brief 空襲により備蓄資源に損害を受けました！
    resource = 1,

    /// @brief 空襲により備蓄資源に損害を受け、基地航空隊にも地上撃破の損害が発生しました！
    resource_and_air = 2,

    /// @brief 空襲により基地航空隊に地上撃破の損害が発生しました！
    air = 3,

    /// @brief 空襲による基地の損害はありません。
    none = 4,
};

/// @brief 被害状況をシリアライゼーションする.
constexpr const char* to_string(lost_kind v) noexcept {
    switch (v) {
        case lost_kind::resource:
            return "備蓄資源に損害を受けました!";

        case lost_kind::resource_and_air:
            return "備蓄資源に損害を受け、基地航空隊にも地上撃破の損害が発生しました!";

        case lost_kind::air:
            return "基地航空隊に地上撃破の損害が発生しました!";

        case lost_kind::none:
            return "基地の損害はありません.";
    }

    return "enum kcv::kcsapi::lost_kind has no such member.";
}

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_ENUM_LOST_KIND_HPP_INCLUDED
