// std
#include <cassert>

// kcv
#include "constants/ship.hpp"
#include "json/read_json.hpp"
#include "kcsapi/types/enum/ship_id.hpp"

// test
#include "root.hpp"

int main() {
    const auto api_mst_ship = []() static -> kcv::kcsapi::api_mst_ship {
        auto temp = kcv::kcsapi::api_mst_ship{};
        kcv::read_json(temp, kcv::test::root / "assets/api_mst_ship/api_mst_ship.json");
        if (not std::ranges::is_sorted(temp, {}, &kcv::kcsapi::api_mst_ship_value_t::api_id)) {
            std::ranges::sort(temp, {}, &kcv::kcsapi::api_mst_ship_value_t::api_id);
        }
        return temp;
    }();

    using namespace kcv::literals::ship_literals;

    static_assert(kcv::to_ship_id("金剛改二丙") == kcv::kcsapi::ship_id{591});
    static_assert("Jervis"_id == kcv::kcsapi::ship_id{519});

    // static_assert("宗谷"_id == kcv::kcsapi::ship_id{645});
    // static_assert("宗谷"_id == kcv::kcsapi::ship_id{650});
    // static_assert("宗谷"_id == kcv::kcsapi::ship_id{699});

    {
        const auto id  = "伊168"_id;
        const auto mst = kcv::get_if(id, api_mst_ship);
        assert(mst != nullptr);
        assert(kcv::is_submarine(*mst));
    }

    {
        const auto id  = "伊401改"_id;
        const auto mst = kcv::get_if(id, api_mst_ship);
        assert(mst != nullptr);
        assert(kcv::is_submarine(*mst));
    }

    {
        const auto id  = "大鯨"_id;
        const auto mst = kcv::get_if(id, api_mst_ship);
        assert(mst != nullptr);
        assert(not kcv::is_submarine(*mst));
    }

    {
        const auto id  = "赤城改二"_id;
        const auto mst = kcv::get_if(id, api_mst_ship);
        assert(mst != nullptr);
        assert(kcv::is_aircraft_carrier(*mst));
    }

    {
        const auto id  = "伊勢改二"_id;
        const auto mst = kcv::get_if(id, api_mst_ship);
        assert(mst != nullptr);
        assert(not kcv::is_aircraft_carrier(*mst));
    }

    {
        const auto id  = "龍鳳改二戊"_id;
        const auto mst = kcv::get_if(id, api_mst_ship);
        assert(mst != nullptr);
        assert(kcv::is_night_operation_aircraft_carrier(*mst));
    }

    {
        const auto id  = "龍鳳改二"_id;
        const auto mst = kcv::get_if(id, api_mst_ship);
        assert(mst != nullptr);
        assert(not kcv::is_night_operation_aircraft_carrier(*mst));
    }

    {
        const auto id  = "加賀改二護"_id;
        const auto mst = kcv::get_if(id, api_mst_ship);
        assert(mst != nullptr);
        assert(kcv::is_night_shellable_aircraft_carrier(*mst));
    }

    {
        const auto id  = "加賀改二"_id;
        const auto mst = kcv::get_if(id, api_mst_ship);
        assert(mst != nullptr);
        assert(not kcv::is_night_shellable_aircraft_carrier(*mst));
    }
}