set(ControllerTestSources 
    ControllerTest.cpp
    )

add_executable(ControllerTest ${ControllerTestSources})

target_link_libraries(ControllerTest 
                    ControllerLib
                    GTest::gtest_main
                    )