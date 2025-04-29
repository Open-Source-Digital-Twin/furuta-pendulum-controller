add_library(ControllerLib)

target_sources(ControllerLib
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Controller.cpp
    ${CMAKE_CURRENT_LIST_DIR}/TECSController.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Controller.h
    ${CMAKE_CURRENT_LIST_DIR}/TECSController.h
    )

target_include_directories(ControllerLib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )

target_link_libraries(ControllerLib
    PUBLIC 
    ConfigLib
    spdlog::spdlog
    )