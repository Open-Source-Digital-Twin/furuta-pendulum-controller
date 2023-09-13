add_library(ControllerLib)

target_sources(ControllerLib
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Controller.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Controller.h
    )

target_include_directories(ControllerLib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )