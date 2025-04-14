add_executable(test_core_constants_equipment ./libkcv/core/constants/equipment.cpp)
target_link_libraries(test_core_constants_equipment PRIVATE kcv)
add_test(NAME core_constants_equipment COMMAND test_core_constants_equipment WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_core_constants_ship ./libkcv/core/constants/ship.cpp)
target_link_libraries(test_core_constants_ship PRIVATE kcv)
add_test(NAME core_constants_ship COMMAND test_core_constants_ship WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_damage_formula_function_function ./libkcv/core/damage_formula/function/function.cpp)
target_link_libraries(test_damage_formula_function_function PRIVATE kcv)
add_test(NAME damage_formula_function_function COMMAND test_damage_formula_function_function WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_core_equipment_bonus_eoen ./libkcv/core/equipment_bonus/eoen.cpp)
target_link_libraries(test_core_equipment_bonus_eoen PRIVATE kcv)
add_test(NAME equipment_bonus COMMAND test_core_equipment_bonus_eoen WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_get_member_ship_deck_response ./libkcv/models/kcsapi/api_get_member/ship_deck/response.cpp)
target_link_libraries(test_api_get_member_ship_deck_response PRIVATE kcv)
add_test(NAME api_get_member_ship_deck_response COMMAND test_api_get_member_ship_deck_response WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# 生データが手元にないためでテスト不可
# add_executable(test_api_port_port_response ./libkcv/models/kcsapi/api_port/port/response.cpp)
# target_link_libraries(test_api_port_port_response PRIVATE kcv)
# add_test(NAME api_port_port_response COMMAND test_api_port_port_response WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_req_battle_midnight_battle_response ./libkcv/models/kcsapi/api_req_battle_midnight/battle/response.cpp)
target_link_libraries(test_api_req_battle_midnight_battle_response PRIVATE kcv)
add_test(NAME api_req_battle_midnight_battle COMMAND test_api_req_battle_midnight_battle_response WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_req_map_next_response ./libkcv/models/kcsapi/api_req_map/next/response.cpp)
target_link_libraries(test_api_req_map_next_response PRIVATE kcv)
add_test(NAME api_req_map_next_response COMMAND test_api_req_map_next_response WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_req_map_start_request ./libkcv/models/kcsapi/api_req_map/start/request.cpp)
target_link_libraries(test_api_req_map_start_request PRIVATE kcv)
add_test(NAME api_req_map_start_request COMMAND test_api_req_map_start_request WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_req_map_start_response ./libkcv/models/kcsapi/api_req_map/start/response.cpp)
target_link_libraries(test_api_req_map_start_response PRIVATE kcv)
add_test(NAME api_req_map_start_response COMMAND test_api_req_map_start_response WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_req_sortie_battle_response ./libkcv/models/kcsapi/api_req_sortie/battle/response.cpp)
target_link_libraries(test_api_req_sortie_battle_response PRIVATE kcv)
add_test(NAME api_req_sortie_battle_response COMMAND test_api_req_sortie_battle_response WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_req_sortie_battleresult_response ./libkcv/models/kcsapi/api_req_sortie/battleresult/response.cpp)
target_link_libraries(test_api_req_sortie_battleresult_response PRIVATE kcv)
add_test(NAME api_req_sortie_battleresult_response COMMAND test_api_req_sortie_battleresult_response WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_mst_ship ./libkcv/models/kcsapi/api_start2/api_mst_ship.cpp)
target_link_libraries(test_api_mst_ship PRIVATE kcv)
add_test(NAME api_mst_ship COMMAND test_api_mst_ship WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_mst_slotitem ./libkcv/models/kcsapi/api_start2/api_mst_slotitem.cpp)
target_link_libraries(test_api_mst_slotitem PRIVATE kcv)
add_test(NAME api_mst_slotitem COMMAND test_api_mst_slotitem WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
