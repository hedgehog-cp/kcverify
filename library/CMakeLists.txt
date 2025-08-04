add_library(libkcv STATIC
    ./core/constants/ship.cpp
    ./core/constants/equipment.cpp
    ./core/utility/read_json.cpp
    ./core/utility/kcsapi.cpp
    ./core/sortie/entities/ship.cpp
    ./core/sortie/equipment_bonus.cpp
)
target_include_directories(libkcv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_dependencies(libkcv libkcv_tools)