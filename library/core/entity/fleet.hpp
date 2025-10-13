#ifndef KCVERIFY_CORE_ENTITY_FLEET_HPP_INCLUDED
#define KCVERIFY_CORE_ENTITY_FLEET_HPP_INCLUDED

// std
#include <string>
#include <utility>
#include <vector>

// kcv
#include "core/entity/ship.hpp"

namespace kcv {

class fleet final {
   public:
    fleet(std::string name, std::vector<kcv::ship> ships) noexcept
        : name_{std::move(name)}
        , ships_{std::move(ships)} {}

    auto name() const noexcept -> const std::string& {
        return this->name_;
    }

    /// @todo std::spanを検討する.
    auto ships() noexcept -> std::vector<kcv::ship>& {
        return this->ships_;
    }

    auto ships() const noexcept -> const std::vector<kcv::ship>& {
        return this->ships_;
    }

   private:
    /// @brief 艦隊名.
    std::string name_;

    /// @brief 艦船.
    std::vector<kcv::ship> ships_;
};

}  // namespace kcv

#endif  // KCVERIFY_CORE_ENTITY_FLEET_HPP_INCLUDED
