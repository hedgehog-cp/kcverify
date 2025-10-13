#ifndef KCVERIFY_CORE_BATTLELOG_PROCESS_API_COMMON_HPP_INCLUDED
#define KCVERIFY_CORE_BATTLELOG_PROCESS_API_COMMON_HPP_INCLUDED

// std
#include <cmath>
#include <cstdint>
#include <string_view>

// kcv
#include "models/kcsapi/types/svdata.hpp"

namespace kcv {

/// @brief responseのsvdataが成功であるかを検証する.
/// @return 成功であればtrueを返す.
template <typename T>
bool success(const kcv::kcsapi::svdata<T>& svdata) noexcept {
    return svdata.api_result == 1 and svdata.api_result_msg == std::string_view{"成功"};
}

/// @brief かばうのために+0.1されているフラグを下ろし, 実際のダメージを返す.
inline auto unprotected_damage(double damage) noexcept -> std::int32_t {
    [[assume(damage >= 0.0)]];
    return std::floor(damage);
}

/// @brief かばったかを検証する.
inline bool is_protected(double damage) noexcept {
    return damage != unprotected_damage(damage);
}

inline constexpr auto uninitialized_enemy_fleet_name_tag = "uninit";

}  // namespace kcv

#endif  // KCVERIFY_CORE_BATTLELOG_PROCESS_API_COMMON_HPP_INCLUDED
