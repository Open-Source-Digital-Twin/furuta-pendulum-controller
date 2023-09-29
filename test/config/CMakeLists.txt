set(ConfigTestSources 
    ConfigurationTest.cpp
    )

add_executable(ConfigTest ${ConfigTestSources})

target_link_libraries(ConfigTest 
                    ConfigLib
                    GTest::gmock
                    GTest::gmock_main
                    GTest::gtest
                    GTest::gtest_main
                    )