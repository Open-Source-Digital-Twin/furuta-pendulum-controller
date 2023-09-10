set(ConfigTestSources 
    ConfigurationTest.cpp
    )

add_executable(ConfigTest ${ConfigTestSources})

target_link_libraries(ConfigTest 
                    ConfigLib
                    GTest::gtest_main
                    )