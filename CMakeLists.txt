cmake_minimum_required(VERSION 3.22.0)
project(cpp-template VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)
find_package(GTest REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(benchmark CONFIG REQUIRED)

option(STRICT_BUILD "Enable warnings as errors" ON)

add_subdirectory(src)
add_subdirectory(benchmark)
add_subdirectory(test)
include(CTest)

include(CPackConfig.cmake)
include(CPack)