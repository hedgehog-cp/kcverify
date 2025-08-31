add_library(libkcv STATIC
    ./core/constants/ship.cpp
    ./core/constants/equipment.cpp
    ./core/utility/read_json.cpp
    ./core/utility/kcsapi.cpp
    ./core/sortie/entities/ship.cpp
    ./core/sortie/equipment_bonus.cpp

    ./core/battlelog/generate_battlelog.cpp
    ./core/battlelog/sortie_api.cpp
    ./core/battlelog/equipment_bonus.cpp

    ./extensions/exception.cpp
)
target_include_directories(libkcv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_dependencies(libkcv libkcv_tools)