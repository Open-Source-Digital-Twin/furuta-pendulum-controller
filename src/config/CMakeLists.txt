add_library(ConfigLib)

target_sources(ConfigLib
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Configuration.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Configuration.h
    )

target_include_directories(ConfigLib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )

target_link_libraries(ConfigLib
    PUBLIC 
    nlohmann_json::nlohmann_json
    )
