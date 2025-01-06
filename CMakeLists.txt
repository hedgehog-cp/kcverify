cmake_minimum_required(VERSION 3.22)

project(kcverify CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-std=c++2b)
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

add_executable(test_kcsapi_api_get_member_ship_deck_response ./test/kcsapi/api_get_member/ship_deck/response.cpp)
target_include_directories(test_kcsapi_api_get_member_ship_deck_response PRIVATE test)
add_test(NAME kcsapi_api_get_member_ship_deck_response COMMAND test_kcsapi_api_get_member_ship_deck_response)

add_executable(test_api_req_battle_midnight_battle_response ./test/kcsapi/api_req_battle_midnight/battle/response.cpp)
target_include_directories(test_api_req_battle_midnight_battle_response PRIVATE test)
add_test(NAME kcsapi_api_req_battle_midnight_battle_response COMMAND test_api_req_battle_midnight_battle_response)

add_executable(test_kcsapi_api_req_map_start_request ./test/kcsapi/api_req_map/start/request.cpp)
target_include_directories(test_kcsapi_api_req_map_start_request PRIVATE test)
add_test(NAME kcsapi_api_req_map_start_request COMMAND test_kcsapi_api_req_map_start_request)

add_executable(test_kcsapi_api_req_map_start_response ./test/kcsapi/api_req_map/start/response.cpp)
target_include_directories(test_kcsapi_api_req_map_start_response PRIVATE test)
add_test(NAME kcsapi_api_req_map_start_response COMMAND test_kcsapi_api_req_map_start_response)

add_executable(test_kcsapi_api_req_sortie_battle_response ./test/kcsapi/api_req_sortie/battle/response.cpp)
target_include_directories(test_kcsapi_api_req_sortie_battle_response PRIVATE test)
add_test(NAME kcsapi_api_req_sortie_battle_response COMMAND test_kcsapi_api_req_sortie_battle_response)

add_executable(test_kcsapi_api_req_sortie_battleresult_response ./test/kcsapi/api_req_sortie/battleresult/response.cpp)
target_include_directories(test_kcsapi_api_req_sortie_battleresult_response PRIVATE test)
add_test(NAME kcsapi_api_req_sortie_battleresult_response COMMAND test_kcsapi_api_req_sortie_battleresult_response)

add_executable(test_kcsapi_api_start2_api_mst_ship ./test/kcsapi/api_start2/api_mst_ship.cpp)
target_include_directories(test_kcsapi_api_start2_api_mst_ship PRIVATE test)
add_test(NAME kcsapi_api_start2_api_mst_ship COMMAND test_kcsapi_api_start2_api_mst_ship)

add_executable(test_kcsapi_api_start2_api_mst_slotitem ./test/kcsapi/api_start2/api_mst_slotitem.cpp)
target_include_directories(test_kcsapi_api_start2_api_mst_slotitem PRIVATE test)
add_test(NAME kcsapi_api_start2_api_mst_slotitem COMMAND test_kcsapi_api_start2_api_mst_slotitem)

add_executable(test_eoen_sortie_record ./test/eoen/sortie_record/sortie_record.cpp)
target_include_directories(test_eoen_sortie_record PRIVATE test)
add_test(NAME eoen_sortie_record COMMAND test_eoen_sortie_record)

add_executable(test_sortie_data ./test/sortie_data/sortie_data.cpp)
target_include_directories(test_sortie_data PRIVATE test)
add_test(NAME sortie_data COMMAND test_sortie_data)

add_executable(test_eoen_fit_bonus ./test/eoen/fit_bonus/fit_bonus.cpp)
target_include_directories(test_eoen_fit_bonus PRIVATE test)
add_test(NAME eoen_fit_bonus COMMAND test_eoen_fit_bonus)