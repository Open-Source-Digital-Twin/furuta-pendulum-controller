cmake_minimum_required(VERSION 3.22.0)
project(Controller VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)
find_package(GTest REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)

# Add path for custom modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(Sanitizer)

option(STRICT_BUILD "Enable warnings as errors" ON)

configure_file(CMakeConfig.h.in "${CMAKE_BINARY_DIR}/CMakeConfig.h")
include_directories (${CMAKE_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(benchmark)
add_subdirectory(test)
include(CTest)

include(CPackConfig.cmake)
include(CPack)