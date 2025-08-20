add_executable(test_extensions_inplace_vector ./library/extensions/inplace_vector.cpp)
target_link_libraries(test_extensions_inplace_vector PRIVATE libkcv -lstdc++exp)
add_test(NAME extensions_inplace_vector COMMAND test_extensions_inplace_vector WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_extensions_interval ./library/extensions/interval.cpp)
target_link_libraries(test_extensions_interval PRIVATE libkcv -lstdc++exp)
add_test(NAME extensions_interval COMMAND test_extensions_interval WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_core_constants_equipment ./library/core/constants/equipment.cpp)
target_link_libraries(test_core_constants_equipment PRIVATE libkcv -lstdc++exp)
add_test(NAME core_constants_equipment COMMAND test_core_constants_equipment WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_core_constants_ship ./library/core/constants/ship.cpp)
target_link_libraries(test_core_constants_ship PRIVATE libkcv -lstdc++exp)
add_test(NAME core_constants_ship COMMAND test_core_constants_ship WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_damage_formula_functions_functions ./library/core/damage_formula/functions/functions.cpp)
target_link_libraries(test_damage_formula_functions_functions PRIVATE libkcv -lstdc++exp)
add_test(NAME damage_formula_functions_functions COMMAND test_damage_formula_functions_functions WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_damage_formula_functions_inverse ./library/core/damage_formula/functions/inverse.cpp)
target_link_libraries(test_damage_formula_functions_inverse PRIVATE libkcv -lstdc++exp)
add_test(NAME damage_formula_functions_inverse COMMAND test_damage_formula_functions_inverse WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_core_sortie_equipment_bonus_eoen ./library/core/sortie/equipment_bonus/eoen.cpp)
target_link_libraries(test_core_sortie_equipment_bonus_eoen PRIVATE libkcv -lstdc++exp)
add_test(NAME core_sortie_equipment_bonus_eoen COMMAND test_core_sortie_equipment_bonus_eoen WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_core_sortie_equipment_bonus_kc3kai ./library/core/sortie/equipment_bonus/kc3kai.cpp)
target_link_libraries(test_core_sortie_equipment_bonus_kc3kai PRIVATE libkcv -lstdc++exp)
add_test(NAME core_sortie_equipment_bonus_kc3kai COMMAND test_core_sortie_equipment_bonus_kc3kai WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_eoen_fit_bonus ./library/models/eoen/fit_bonus.cpp)
target_link_libraries(test_eoen_fit_bonus PRIVATE libkcv -lstdc++exp)
add_test(NAME eoen_fit_bonus COMMAND test_eoen_fit_bonus WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_eoen_sortie_record ./library/models/eoen/sortie_record.cpp)
target_link_libraries(test_eoen_sortie_record PRIVATE libkcv -lstdc++exp)
add_test(NAME eoen_sortie_record COMMAND test_eoen_sortie_record WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_get_member_ship_deck_response ./library/models/kcsapi/api_get_member/ship_deck/response.cpp)
target_link_libraries(test_api_get_member_ship_deck_response PRIVATE libkcv -lstdc++exp)
add_test(NAME api_get_member_ship_deck_response COMMAND test_api_get_member_ship_deck_response WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# 生データが手元にないためでテスト不可
# add_executable(test_api_port_port_response ./library/models/kcsapi/api_port/port/response.cpp)
# target_link_libraries(test_api_port_port_response PRIVATE libkcv -lstdc++exp)
# add_test(NAME api_port_port_response COMMAND test_api_port_port_response WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_req_battle_midnight_battle_response ./library/models/kcsapi/api_req_battle_midnight/battle/response.cpp)
target_link_libraries(test_api_req_battle_midnight_battle_response PRIVATE libkcv -lstdc++exp)
add_test(NAME api_req_battle_midnight_battle COMMAND test_api_req_battle_midnight_battle_response WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_req_map_next_response ./library/models/kcsapi/api_req_map/next/response.cpp)
target_link_libraries(test_api_req_map_next_response PRIVATE libkcv -lstdc++exp)
add_test(NAME api_req_map_next_response COMMAND test_api_req_map_next_response WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_req_map_start_request ./library/models/kcsapi/api_req_map/start/request.cpp)
target_link_libraries(test_api_req_map_start_request PRIVATE libkcv -lstdc++exp)
add_test(NAME api_req_map_start_request COMMAND test_api_req_map_start_request WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_req_map_start_response ./library/models/kcsapi/api_req_map/start/response.cpp)
target_link_libraries(test_api_req_map_start_response PRIVATE libkcv -lstdc++exp)
add_test(NAME api_req_map_start_response COMMAND test_api_req_map_start_response WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_req_sortie_battle_response ./library/models/kcsapi/api_req_sortie/battle/response.cpp)
target_link_libraries(test_api_req_sortie_battle_response PRIVATE libkcv -lstdc++exp)
add_test(NAME api_req_sortie_battle_response COMMAND test_api_req_sortie_battle_response WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_req_sortie_battleresult_response ./library/models/kcsapi/api_req_sortie/battleresult/response.cpp)
target_link_libraries(test_api_req_sortie_battleresult_response PRIVATE libkcv -lstdc++exp)
add_test(NAME api_req_sortie_battleresult_response COMMAND test_api_req_sortie_battleresult_response WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_mst_ship ./library/models/kcsapi/api_start2/api_mst_ship.cpp)
target_link_libraries(test_api_mst_ship PRIVATE libkcv -lstdc++exp)
add_test(NAME api_mst_ship COMMAND test_api_mst_ship WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_api_mst_slotitem ./library/models/kcsapi/api_start2/api_mst_slotitem.cpp)
target_link_libraries(test_api_mst_slotitem PRIVATE libkcv -lstdc++exp)
add_test(NAME api_mst_slotitem COMMAND test_api_mst_slotitem WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
