// std
#include <cassert>

// kcv
#include "constants/equipment.hpp"
#include "kcsapi/types/enum/equipment_id.hpp"
#include "read_json.hpp"

// test
#include "root.hpp"

int main() {
    const auto api_mst_slotitem = []() static -> kcv::kcsapi::api_mst_slotitem {
        auto temp = kcv::kcsapi::api_mst_slotitem{};
        kcv::read_json(temp, kcv::test::root / "assets/api_mst_slotitem/api_mst_slotitem.json");
        if (not std::ranges::is_sorted(temp, {}, &kcv::kcsapi::api_mst_slotitem_value_t::api_id)) {
            std::ranges::sort(temp, {}, &kcv::kcsapi::api_mst_slotitem_value_t::api_id);
        }
        return temp;
    }();

    using namespace kcv::literals::equipment_literals;

    static_assert(kcv::to_equipment_id("流星改(一航戦/熟練)") == kcv::kcsapi::equipment_id{343});
    static_assert("発煙装置改(煙幕)"_id == kcv::kcsapi::equipment_id{501});

    {
        const auto id  = "夜間作戦航空要員+熟練甲板員"_id;
        const auto mst = kcv::get_if(id, api_mst_slotitem);
        assert(mst != nullptr);
        assert(kcv::is_night_operation_aviation_personnel(*mst));
    }

    {
        const auto id  = "Swordfish Mk.III(熟練)"_id;
        const auto mst = kcv::get_if(id, api_mst_slotitem);
        assert(mst != nullptr);
        assert(kcv::is_cb_swordfish(*mst));
    }

    {
        const auto id  = "Swordfish(水上機型)"_id;
        const auto mst = kcv::get_if(id, api_mst_slotitem);
        assert(mst != nullptr);
        assert(not kcv::is_cb_swordfish(*mst));
    }

    {
        const auto id  = "烈風改二戊型(一航戦/熟練)"_id;
        const auto mst = kcv::get_if(id, api_mst_slotitem);
        assert(mst != nullptr);
        assert(kcv::is_night_plane(*mst));
    }

    {
        const auto id  = "天山一二型甲改二(村田隊/電探装備)"_id;
        const auto mst = kcv::get_if(id, api_mst_slotitem);
        assert(mst != nullptr);
        assert(kcv::is_night_plane(*mst));
    }

    {
        const auto id  = "零戦62型(爆戦/岩井隊)"_id;
        const auto mst = kcv::get_if(id, api_mst_slotitem);
        assert(mst != nullptr);
        assert(kcv::is_semi_night_plane(*mst));
    }
}