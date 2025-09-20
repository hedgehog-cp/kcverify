add_library(libkcv STATIC
    ./core/constants/equipment.cpp
    ./core/constants/ship.cpp

    ./core/utility/kcsapi.cpp
    ./core/utility/read_json.cpp

    ./core/battlelog/equipment_bonus.cpp
    ./core/battlelog/generate_battlelog.cpp

    ./core/entity/adapter/from_eoen.cpp

    ./extensions/exception.cpp
)
target_include_directories(libkcv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_dependencies(libkcv libkcv_tools)