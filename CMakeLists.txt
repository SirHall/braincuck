cmake_minimum_required(VERSION 3.5)

add_compile_options(-Wall -Wextra -Wpedantic -Wno-unknown-pragmas -Wno-unused-parameter -Iinclude -g)

project(out)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)

set(EXECUTABLE_NAME "out")
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SRCS
    "src/*.cpp"
    RELATIVE_PATH
)

add_executable(out ${SRCS})

target_include_directories(out PUBLIC ${INCLUDE_DIR})
