#ifndef KCVERIFY_MASTER_EQUIPMENT_HPP_INCLUDED
#define KCVERIFY_MASTER_EQUIPMENT_HPP_INCLUDED

// std
#include <cassert>
#include <string_view>
#include <type_traits>

// kcv
#include "meta/category.hpp"
#include "meta/icon.hpp"

namespace kcv {

class equipment_t final {
   public:
    enum class id_type {};

    consteval equipment_t() noexcept
        : id_{0}
        , name_{""}
        , category_{0}
        , icon_{0}
        , houg_{0}
        , raig_{0}
        , baku_{0} {
    }

    constexpr equipment_t(
        std::underlying_type_t<id_type> id,           //
        std::string_view name,                        //
        std::underlying_type_t<category_t> category,  //
        std::underlying_type_t<icon_t> icon,          //
        int houg,                                     //
        int raig,                                     //
        int baku                                      //
    ) noexcept
        : id_{id}
        , name_{name}
        , category_{category}
        , icon_{icon}
        , houg_{houg}
        , raig_{raig}
        , baku_{baku} {
    }

    constexpr auto id() const noexcept -> id_type {
        return this->id_;
    }

    constexpr auto name() const noexcept -> std::string_view {
        return this->name_;
    }

    constexpr auto category() const noexcept -> category_t {
        return this->category_;
    }

    constexpr auto icon() const noexcept -> icon_t {
        return this->icon_;
    }

    constexpr int houg() const noexcept {
        return this->houg_;
    }

    constexpr int raig() const noexcept {
        return this->raig_;
    }

    constexpr int baku() const noexcept {
        return this->baku_;
    }

   private:
    id_type id_;
    std::string_view name_;
    category_t category_;
    icon_t icon_;
    int houg_;
    int raig_;
    int baku_;
};

}  // namespace kcv

#endif  // KCVERIFY_MASTER_EQUIPMENT_HPP_INCLUDED
