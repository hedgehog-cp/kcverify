// std
#include <filesystem>

// kcv
#include "kcapi/api_req_sortie/battle/response.hpp"
#include "kcapi/types/svdata.hpp"

// kcv::test
#include "read_and_write_json.hpp"
#include "root.hpp"

int main() {
    using value_type = kcv::kcapi::api_req_sortie::battle::response;
    using svdata     = kcv::kcapi::svdata<value_type>;
    const auto dir   = std::filesystem::path{"test/kcapi/api_req_sortie/battle"};

    const int result = kcv::test::read_and_write_json<svdata>(kcv::test::root / dir / "response.json");

    return result;
}
