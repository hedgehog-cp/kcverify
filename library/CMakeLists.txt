add_library(libkcv STATIC
    ./core/constants/ship.cpp
    ./core/constants/equipment.cpp
    ./core/common/kcsapi.cpp
    ./core/common/read_json.cpp
    ./core/common/system.cpp
    ./core/sortie/entities/ship.cpp
    ./core/sortie/equipment_bonus.cpp
)
target_include_directories(libkcv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_dependencies(libkcv libkcv_tools)