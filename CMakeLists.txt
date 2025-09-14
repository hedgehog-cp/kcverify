cmake_minimum_required(VERSION 3.22)

project(kcverify CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-std=c++2b)
add_compile_options(-Wall -Wextra --pedantic-errors)
add_compile_options(-O0 -g3)
add_compile_options(-fno-builtin-std-forward_like)
# add_compile_options(-O2 -march=native)

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

# tools ########################################################################

add_subdirectory(tools)

# library ######################################################################

add_subdirectory(library)

# main #########################################################################

add_executable(kcverify ./source/main.cpp)
target_link_libraries(kcverify PRIVATE libkcv -lstdc++exp)
add_dependencies(kcverify libkcv_tools)

# test #########################################################################

enable_testing()
add_subdirectory(test)