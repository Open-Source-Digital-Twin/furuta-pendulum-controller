add_subdirectory(config)
add_subdirectory(controller)
add_subdirectory(hal)

add_executable(Controller main.cpp)
target_link_libraries(Controller 
                    ConfigLib
                    ControllerLib
                    HalLib)
