#include "core/constants/ship.hpp"

int main() {
    using kcv::literals::ship_literals::operator""_id;

    static_assert("Jervis"_id == kcv::kcsapi::ship_id{519});
    static_assert("金剛改二丙"_id == kcv::kcsapi::ship_id{591});
}