add_subdirectory(config)
add_subdirectory(controller)
add_subdirectory(hal)
add_subdirectory(proto)

add_executable(Controller main.cpp)

target_link_libraries(Controller 
                    ConfigLib
                    ControllerLib
                    HalLib
                    spdlog::spdlog
                    absl::strings
                    )

if(STRICT_BUILD)
    target_compile_options(Controller PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif(STRICT_BUILD)
