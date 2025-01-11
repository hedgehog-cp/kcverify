#include "constants/ship.hpp"

#include "kcsapi/types/enum/ship_id.hpp"

int main() {
    using namespace kcv::literals::ship_literals;

    static_assert(kcv::to_ship_id("金剛改二丙") == kcv::kcsapi::ship_id{591});
    static_assert("Jervis"_id == kcv::kcsapi::ship_id{519});

    // static_assert("宗谷"_id == kcv::kcsapi::ship_id{645});
    // static_assert("宗谷"_id == kcv::kcsapi::ship_id{650});
    // static_assert("宗谷"_id == kcv::kcsapi::ship_id{699});

    static_assert(kcv::is_submarine("伊168"_id));
    static_assert(kcv::is_submarine("伊401改"_id));
    static_assert(not kcv::is_submarine("大鯨"_id));

    static_assert(kcv::is_aircraft_carrier("赤城改二"_id));
    static_assert(not kcv::is_aircraft_carrier("伊勢改二"_id));

    static_assert(kcv::is_night_operation_aircraft_carrier("龍鳳改二戊"_id));
    static_assert(not kcv::is_night_operation_aircraft_carrier("龍鳳改二"_id));

    static_assert(kcv::is_night_shellable_aircraft_carrier("加賀改二護"_id));
    static_assert(not kcv::is_night_shellable_aircraft_carrier("加賀改二"_id));
}