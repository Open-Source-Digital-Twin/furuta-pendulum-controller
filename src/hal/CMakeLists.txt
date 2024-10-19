add_library(HalLib)

target_sources(HalLib
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/AngleSensor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DCMotor.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/AngleSensor.h
    ${CMAKE_CURRENT_LIST_DIR}/DCMotor.h
    )

target_include_directories(HalLib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    )

target_link_libraries(HalLib
  PUBLIC 
  spdlog::spdlog
  )