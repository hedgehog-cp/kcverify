#include "constants/equipment.hpp"

#include "kcsapi/types/enum/equipment_id.hpp"

int main() {
    using namespace kcv::literals::equipment_literals;

    static_assert(kcv::to_equipment_id("流星改(一航戦/熟練)") == kcv::kcsapi::equipment_id{343});
    static_assert("発煙装置改(煙幕)"_id == kcv::kcsapi::equipment_id{501});

    static_assert(kcv::is_night_operation_aviation_personnel("夜間作戦航空要員+熟練甲板員"_id));

    static_assert(kcv::is_cb_swordfish("Swordfish Mk.III(熟練)"_id));
    static_assert(not kcv::is_cb_swordfish("Swordfish(水上機型)"_id));

    static_assert(kcv::is_night_plane("烈風改二戊型(一航戦/熟練)"_id));
    static_assert(kcv::is_night_plane("天山一二型甲改二(村田隊/電探装備)"_id));

    static_assert(kcv::is_semi_night_plane("零戦62型(爆戦/岩井隊)"_id));
}