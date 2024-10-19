# Module for enabling/disabling sanitizers for all targets.

option(ENABLE_SANITIZERS "Enable sanitizers" ON)

if(ENABLE_SANITIZERS AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=address,undefined,leak -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined,leak -fno-omit-frame-pointer)
endif(ENABLE_SANITIZERS AND CMAKE_BUILD_TYPE STREQUAL "Debug")
