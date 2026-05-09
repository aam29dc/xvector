cmake_minimum_required(VERSION 3.16)
project(Xvector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

list(FILTER SOURCES EXCLUDE REGEX ".*/build/.*")

if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in src/")
endif()

add_executable(app ${SOURCES})

target_include_directories(app PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(app PRIVATE
    -Wall -Wextra -Werror 
)
