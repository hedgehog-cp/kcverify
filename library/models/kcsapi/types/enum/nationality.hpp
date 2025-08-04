#ifndef KCVERIFY_MODELS_KCSAPI_TYPES_ENUM_NATIONALITY_HPP_INCLUDED
#define KCVERIFY_MODELS_KCSAPI_TYPES_ENUM_NATIONALITY_HPP_INCLUDED

namespace kcv {
namespace kcsapi {

/// @brief 国籍ID.
enum class nationality {
    unknown    = -1,
    abyssal    = 0,
    japanese   = 1,
    german     = 2,
    italian    = 3,
    american   = 4,
    british    = 5,
    french     = 6,
    russian    = 7,
    swedish    = 8,
    dutch      = 9,
    australian = 10,
};

}  // namespace kcsapi
}  // namespace kcv

#endif  // KCVERIFY_MODELS_KCSAPI_TYPES_ENUM_NATIONALITY_HPP_INCLUDED
