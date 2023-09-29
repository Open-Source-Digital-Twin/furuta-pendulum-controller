set(HalTestSources 
    AngleSensorTest.cpp
    DCMotorTest.cpp
    )

add_executable(HalTest ${HalTestSources})

target_link_libraries(HalTest 
                    HalLib
                    GTest::gmock
                    GTest::gmock_main
                    GTest::gtest
                    GTest::gtest_main
                    )