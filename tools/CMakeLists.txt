file(GLOB TOOL_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(tool_src ${TOOL_SOURCES})
    get_filename_component(tool_name ${tool_src} NAME_WE)
    add_executable(${tool_name} ${tool_src})
    target_compile_features(${tool_name} PRIVATE cxx_std_23)
endforeach()

add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/library/core/constants/equipment.hpp.inc
    COMMAND $<TARGET_FILE:gen_equipment>
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    DEPENDS gen_equipment ${CMAKE_SOURCE_DIR}/assets/api_mst_slotitem.json
    COMMENT "Generating equipment.hpp.inc"
    VERBATIM
)

add_custom_command(
    OUTPUT ${CMAKE_SOURCE_DIR}/library/core/constants/ship.hpp.inc
    COMMAND $<TARGET_FILE:gen_ship>
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    DEPENDS gen_ship ${CMAKE_SOURCE_DIR}/assets/api_mst_ship.json
    COMMENT "Generating ship.hpp.inc"
    VERBATIM
)


add_custom_target(libkcv_tools
    DEPENDS
        ${CMAKE_SOURCE_DIR}/library/core/constants/equipment.hpp.inc
        ${CMAKE_SOURCE_DIR}/library/core/constants/ship.hpp.inc
)
