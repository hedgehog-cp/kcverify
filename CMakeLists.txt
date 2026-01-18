cmake_minimum_required(VERSION 3.22)
project(kcverify LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_23)

add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
    -Wall -Wextra -pedantic-errors
    -fno-builtin-std-forward_like
    $<$<CONFIG:Debug>:-O0 -g3>
    $<$<CONFIG:Release>:-O2 -march=native>
)

# サニタイザー設定 (ON/OFFを切り替えやすく)
option(ENABLE_SANITIZERS "Enable ASan and UBSan" ON)
if(ENABLE_SANITIZERS)
    add_library(project_sanitizers INTERFACE)
    target_compile_options(project_sanitizers INTERFACE 
        -fsanitize=address,undefined -fno-omit-frame-pointer
    )
    target_link_options(project_sanitizers INTERFACE 
        -fsanitize=address,undefined
    )
endif()

# 先に library を定義しておくと他から参照しやすい
add_subdirectory(library)
add_subdirectory(tools)

add_executable(kcverify source/main.cpp)

target_link_libraries(kcverify 
    PRIVATE 
        kcv
        project_options
        project_warnings
        stdc++exp
)

if(TARGET project_sanitizers)
    target_link_libraries(kcverify PRIVATE project_sanitizers)
endif()

add_dependencies(kcverify kcvtools)

# enable_testing()
# add_subdirectory(test)