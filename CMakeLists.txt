cmake_minimum_required(VERSION 3.22)

project(kcverify CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-std=c++23)
add_compile_options(-Wall -Wextra --pedantic-errors -Wfloat-equal)
add_compile_options(-O2 -march=native)

add_compile_options(-fsanitize=undefined)
add_link_options(-fsanitize=undefined)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
# add_compile_options(-fsanitize=bounds)
# add_link_options(-fsanitize=bounds)
# add_compile_options(-fsanitize=leak)
# add_link_options(-fsanitize=leak)
# add_compile_options(-fno-omit-frame-pointer)
# add_link_options(-fno-omit-frame-pointer)
# add_compile_options(-fanalyzer)
# add_link_options(-fanalyzer)
# add_compile_options(-fsanitize=memory)
# add_link_options(-fsanitize=memory)

include_directories(include)

# main #########################################################################
add_executable(kcverify ./source/main.cpp)

# test #########################################################################
enable_testing()

include_directories(test)

add_executable(test_api_req_battle_midnight_battle_response ./test/kcapi/api_req_battle_midnight/battle/response.cpp)
add_test(NAME kcapi_api_req_battle_midnight_battle_response COMMAND test_api_req_battle_midnight_battle_response)

add_executable(test_kcapi_api_req_map_start_request ./test/kcapi/api_req_map/start/request.cpp)
add_test(NAME kcapi_api_req_map_start_request COMMAND test_kcapi_api_req_map_start_request)

add_executable(test_kcapi_api_req_map_start_response ./test/kcapi/api_req_map/start/response.cpp)
add_test(NAME kcapi_api_req_map_start_response COMMAND test_kcapi_api_req_map_start_response)

add_executable(test_kcapi_api_req_sortie_battle_response ./test/kcapi/api_req_sortie/battle/response.cpp)
add_test(NAME kcapi_api_req_sortie_battle_response COMMAND test_kcapi_api_req_sortie_battle_response)

add_executable(test_kcapi_api_req_sortie_battleresult_response ./test/kcapi/api_req_sortie/battleresult/response.cpp)
add_test(NAME kcapi_api_req_sortie_battleresult_response COMMAND test_kcapi_api_req_sortie_battleresult_response)

add_executable(test_kcapi_api_start2_api_mst_ship ./test/kcapi/api_start2/api_mst_ship.cpp)
add_test(NAME kcapi_api_start2_api_mst_ship COMMAND test_kcapi_api_start2_api_mst_ship)

add_executable(test_kcapi_api_start2_api_mst_slotitem ./test/kcapi/api_start2/api_mst_slotitem.cpp)
add_test(NAME kcapi_api_start2_api_mst_slotitem COMMAND test_kcapi_api_start2_api_mst_slotitem)

add_executable(test_eoen_sortie_detail ./test/eoen/sortie_detail/sortie_detail.cpp)
add_test(NAME eoen_sortie_detail COMMAND test_eoen_sortie_detail)

add_executable(test_eoen_fit_bonus ./test/eoen/fit_bonus/fit_bonus.cpp)
add_test(NAME eoen_fit_bonus COMMAND test_eoen_fit_bonus)