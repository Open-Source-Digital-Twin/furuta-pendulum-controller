set(ControllerTestSources 
    ControllerTest.cpp
    )

add_executable(ControllerTest ${ControllerTestSources})

target_link_libraries(ControllerTest 
                    ControllerLib
                    GTest::gmock
                    GTest::gmock_main
                    GTest::gtest
                    GTest::gtest_main
                    )