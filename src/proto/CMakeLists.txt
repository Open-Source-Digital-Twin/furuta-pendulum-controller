add_library(ProtoLib)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS actuators.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS sensors.proto)

target_sources(ProtoLib
  PRIVATE
    ${PROTO_SRCS}
  PUBLIC
    ${PROTO_HDRS}
    )

target_link_libraries(ProtoLib 
                      protobuf::libprotobuf)