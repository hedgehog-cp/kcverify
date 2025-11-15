add_library(libkcv STATIC
    ./core/attributes/equipment.cpp
    ./core/attributes/ship.cpp
    
    ./core/battlelog/generate_battlelog/process_kcsapi/api_get_member/ship_deck/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_battle_midnight/battle/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_battle_midnight/sp_midnight/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_combined_battle/battle_water/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_combined_battle/battleresult/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_combined_battle/each_battle_water/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_combined_battle/ec_battle/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_combined_battle/ec_midnight_battle/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_combined_battle/ld_airbattle/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_combined_battle/midnight_battle/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_map/next/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_map/start/request.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_map/start/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_map/start_air_base/request.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_map/start_air_base/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_sortie/battle/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_sortie/battleresult/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_sortie/goback_port/response.cpp
    ./core/battlelog/generate_battlelog/process_kcsapi/api_req_sortie/ld_airbattle/response.cpp
    ./core/battlelog/generate_battlelog/generate_battlelog.cpp
    ./core/battlelog/equipment_bonus.cpp
    
    ./core/entity/adapter/from_eoen.cpp

    ./core/json/read_json.cpp

    ./core/utility/kcsapi.cpp

    ./extensions/exception.cpp
)
target_include_directories(libkcv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_dependencies(libkcv libkcv_tools)