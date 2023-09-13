cmake_minimum_required(VERSION 3.22.0)
project(cpp-template VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)
add_subdirectory(abseil-cpp)
include_directories(${Protobuf_INCLUDE_DIRS})

include_directories(config controller hal)

add_subdirectory(src)

add_subdirectory(test)
include(CTest)

include(CPackConfig.cmake)
include(CPack)
