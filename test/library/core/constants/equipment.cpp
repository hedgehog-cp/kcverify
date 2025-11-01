#include "core/constants/equipment.hpp"

int main() {
    using kcv::literals::equipment_literals::operator""_id;

    static_assert("烈風改二(一航戦/熟練)"_id == kcv::kcsapi::equipment_id{337});
    static_assert("流星改(一航戦/熟練)"_id == kcv::kcsapi::equipment_id{343});
}