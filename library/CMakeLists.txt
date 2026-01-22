file(GLOB_RECURSE KCV_SOURCES 
    CONFIGURE_DEPENDS 
    "source/*.cpp"
    "source/*.ipp"
)

add_library(kcv ${KCV_SOURCES})

target_include_directories(kcv
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/source
)

target_link_libraries(kcv
    PRIVATE
        project_options
        project_warnings
        stdc++exp
    PUBLIC
)

if(TARGET project_sanitizers)
    target_link_libraries(kcv PRIVATE project_sanitizers)
endif()

add_dependencies(kcv kcvtools)