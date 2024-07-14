#ifndef KCVERIFY_MASTER_SHIP_SHIP_HPP_INCLUDED
#define KCVERIFY_MASTER_SHIP_SHIP_HPP_INCLUDED

// std
#include <cassert>
#include <string_view>
#include <type_traits>

// kcv
#include "meta/ctype.hpp"
#include "meta/stype.hpp"

namespace kcv {

class ship_t final {
   public:
    enum class id_type {};

    consteval ship_t() noexcept
        : id_{0}
        , name_{""}
        , yomi_{""}
        , stype_{0}
        , ctype_{0}
        , original_id_{0} {
    }

    consteval ship_t(
        std::underlying_type_t<id_type> id,          //
        std::string_view name,                       //
        std::string_view yomi,                       //
        std::underlying_type_t<stype_t> stype,       //
        std::underlying_type_t<ctype_t> ctype,       //
        std::underlying_type_t<id_type> original_id  //
    ) noexcept
        : id_{id}
        , name_{name}
        , yomi_{yomi}
        , stype_{stype}
        , ctype_{ctype}
        , original_id_{original_id} {
    }

    constexpr auto id() const noexcept -> id_type {
        return this->id_;
    }

    constexpr auto name() const noexcept -> std::string_view {
        return this->name_;
    }

    constexpr auto stype() const noexcept -> stype_t {
        return this->stype_;
    }

    constexpr auto ctype() const noexcept -> ctype_t {
        return this->ctype_;
    }

    constexpr auto original_id() const noexcept -> id_type {
        return this->original_id_;
    }

   private:
    id_type id_;
    std::string_view name_;
    std::string_view yomi_;
    stype_t stype_;
    ctype_t ctype_;
    id_type original_id_;
};

}  // namespace kcv

#endif  // KCVERIFY_MASTER_SHIP_SHIP_HPP_INCLUDED
