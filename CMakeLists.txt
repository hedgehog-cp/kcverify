cmake_minimum_required(VERSION 3.22)

project(kcverify CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-std=c++2b)
add_compile_options(-Wall -Wextra --pedantic-errors -Wfloat-equal)
add_compile_options(-O0)
# add_compile_options(-O2 -march=native)
add_compile_options(-fno-builtin-std-forward_like)

add_compile_options(-fsanitize=undefined)
add_link_options(-fsanitize=undefined)
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
# add_compile_options(-fsanitize=bounds)
# add_link_options(-fsanitize=bounds)
# add_compile_options(-fsanitize=leak)
# add_link_options(-fsanitize=leak)
# add_compile_options(-fno-omit-frame-pointer)
# add_link_options(-fno-omit-frame-pointer)
# add_compile_options(-fanalyzer)
# add_link_options(-fanalyzer)
# add_compile_options(-fsanitize=memory)
# add_link_options(-fsanitize=memory)

include_directories(include)

# static lib ###################################################################

add_library(kcv STATIC ./source/common.cpp ./source/read_json.cpp)

# add_library(kcv_common STATIC ./source/common.cpp)

# add_library(kcv_read_json STATIC ./source/read_json.cpp)
# target_link_libraries(kcv_read_json PRIVATE kcv_common)

# main #########################################################################

add_executable(kcverify ./source/main.cpp)
# target_link_libraries(kcverify PRIVATE kcv_common kcv_read_json)
target_link_libraries(kcverify PRIVATE kcv)

# test #########################################################################

enable_testing()
add_subdirectory(test)