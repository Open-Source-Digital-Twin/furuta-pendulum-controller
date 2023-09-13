# find_library(Protobuf_LIBRARIES NAMES protobuf libprotobuf)
# find_path(Protobuf_INCLUDE_DIRS google/protobuf/stubs/common.h) 

# if(Protobuf_LIBRARIES AND Protobuf_INCLUDE_DIRS)
#   set(Protobuf_FOUND TRUE)
# endif()


include_directories(${CMAKE_CURRENT_BINARY_DIR})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS proto/actuators.proto proto/sensors.proto)
add_subdirectory(config)
add_subdirectory(controller)
add_subdirectory(hal)

add_executable(Controller main.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(Controller 
                    ConfigLib
                    ControllerLib
                    HalLib
                    ${Protobuf_LIBRARIES})
