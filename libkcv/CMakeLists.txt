add_library(kcv STATIC
    ./core/common/kcsapi.cpp
    ./core/common/read_json.cpp
    ./core/common/system.cpp
    ./core/equipment_bonus.cpp
)
target_include_directories(kcv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})